//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Scheduler.h"
#include <algorithm>

Define_Module(Scheduler);



Scheduler::Scheduler()
{
    selfMsg = nullptr;
}

Scheduler::~Scheduler()
{
    cancelAndDelete(selfMsg);
}


void Scheduler::initialize()
{
    NrUsers = 10;
    NrOfChannels = 30;//read from omnetpp.ini
    selfMsg = new cMessage("selfMsg");
    for(int user = 0; user < NrUsers; ++user)
    {
        users.push_back((User(user, 1)));
    }
    scheduleAt(simTime(), selfMsg);
}

void Scheduler::handleMessage(cMessage *msg)
{
    int NrBlocks[NrUsers];

    for(int j=0;j<NrUsers; j++){
        NrBlocks[j] = 0;
    }


    for(int i =0; i < NrUsers;i++){
    if (msg->arrivedOn("rxInfo", i)){
          users[i].addQueueLength();
        delete(msg);
        // TO DO: update the info for each user gathered from rxInfo, queueLength
    }
    }
        if (msg == selfMsg){
          double currentSimulationTime = simTime().dbl();
          for(int i = 0; i < NrOfChannels; i++)
          {
          std::sort(users.begin(), users.end(),[this, currentSimulationTime, i](User user1, User user2)
                  {
                      return user1.getCurrentPriority(currentSimulationTime, i) > user2.getCurrentPriority(currentSimulationTime, i);
                  });

            for(auto user : users)
            {
                int userQueueLength = user.getQueueLength();
                int userIndex = user.getUserIndex();
                if(userQueueLength > 0)
                {
                    EV << "Scheduler: channel "<< i <<" allocated to highest priority user ["<< userIndex <<"]"<< endl;
                    NrBlocks[userIndex]++;
                    EV << "Scheduler: decrease queue len of user["<< userIndex <<"] old value: "<< userQueueLength << " new value = " << user.decrementQueueLength(1) << endl;
                    break;
                }
            }
//         TO DO:   IF NO USER HAS MESAGES LEFT STOP SCHEDEULING
          }
          std::sort(users.begin(), users.end(),[this](User user1, User user2)
                                        {
                                            return user1.getUserIndex() < user2.getUserIndex();
                                        });
            // we iterate trough the users
            for(int i = 0; i < NrUsers; i++){
            EV << "!!!!Scheduler:Allocated for user "<< i << " NrBlocks: " << NrBlocks[i] << endl;
                // we check if the user i has any allocated RB's and we send the corresponding message
                if(NrBlocks[i]>0)
                {
                    cMessage *cmd = new cMessage("cmd");
                    cmd->addPar("nrBlocks");
                    cmd->addPar("userPriority");
                    cmd->addPar("userIndex");
                    cmd->par("nrBlocks").setLongValue(NrBlocks[i]);
                    cmd->par("userPriority").setLongValue(users[i].getUserWeight());
                    cmd->par("userIndex").setLongValue(i);
//                    EV << "In SCHEDULER : userPriority on msg is: " << (long)cmd->par("userPriority") << endl;
                    users[i].updateLastTimeServed(simTime().dbl());
                    //set parameter value, e.g., nr of blocks to be sent from the queue by user i
                    send(cmd,"txScheduling",i);
                }
          //  double xtime = simTime().dbl();
            }
        scheduleAt(simTime()+par("schedulingPeriod").doubleValue(), selfMsg);
    }
}
