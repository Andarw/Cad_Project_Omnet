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

#include "Sink.h"
#include <numeric>

Define_Module(Sink);

void Sink::initialize()
{
    lifetimeSignal = registerSignal("lifetime");
    delaySignalHighPriority = registerSignal("delayHighPriority");
    delaySignalMediumPriority = registerSignal("delayMediumPriority");
    delaySignalLowPriority = registerSignal("delayLowPriority");
    delayHighPriority.push_back(delaySignalHighPriority);
    delayMediumPriority.push_back(delaySignalMediumPriority);
    delayLowPriority.push_back(delaySignalLowPriority);
    int numberOfUsers = par("gateSize");
}

void Sink::handleMessage(cMessage *msg)
{
    simtime_t lifetime = simTime() - msg->getCreationTime();
    emit(lifetimeSignal, lifetime);
        if (msg->arrivedOn("rxPackets")) {
            long userPriority = (long)msg->par("userPriority");
            long userIndex = (long)msg->par("userIndex");
            double lifetimeDbl = lifetime.dbl();
            avgPerUser[userIndex] += lifetimeDbl;
            numMsgForEachUser[userIndex] += 1.0f;
            EV << "\n IN SINK userPriority: " << userPriority << endl;
            switch(userPriority){
                        case 9:
                            lenHighPriority += 1.0f;
                            avgHighPriority  += lifetimeDbl ;
                            emit(delaySignalHighPriority, lifetimeDbl);
                            EV << "Priority 9 packet delay: " << lifetime << "s" << endl;
                            break;
                        case 4:
                            lenMediumPriority += 1.0f;
                            avgMediumPriority  += lifetimeDbl ;
                            emit(delaySignalMediumPriority, lifetimeDbl);
                            EV << "Priority 4 packet delay: " << lifetime << "s" << endl;
                            break;
                        case 1:
                            lenLowPriority += 1.0f;
                            avgLowPriority  += lifetimeDbl;
                            emit(delaySignalLowPriority, lifetimeDbl);
                            EV << "Priority 1 packet delay: " << lifetime << "s" << endl;
                            break;
                    }
        }
      EV << "Sink: Received " << msg->getName() << ", lifetime: " << lifetime << "s" << endl;

      delete msg;
}

void Sink::finish()
{

//    if (!delayHighPriority.empty()) {
//        EV << "High Priority values " << delayHighPriority.size() << "s\n";
//        for(double value : delayHighPriority)
//        {
////          EV << "High Priority value " << value << "s\n";
//          avgHighPriority = avgHighPriority + value;
//        }
//        EV << "High Priority total value " << avgHighPriority << "s\n";
//        avgHighPriority = (double)avgHighPriority / (double)delayHighPriority.size();
////        recordScalar("avgHighPriority", avgHighPriority);
//    }
//
//    if (!delayMediumPriority.empty()) {
//        EV << "Medium Priority values " << delayMediumPriority[4] << "s\n";
//        for(double value : delayMediumPriority)
//        {
//          avgMediumPriority = avgMediumPriority + value;
//        }
//        EV << "Medium Priority total value " << avgMediumPriority << "s\n";
//        avgMediumPriority = (double)avgMediumPriority / (double)delayHighPriority.size();
////        recordScalar("avgMediumPriority", avgMediumPriority);
//    }
//
//    if (!delayLowPriority.empty()) {
//        EV << "Low Priority values " << delayLowPriority[4] << "s\n";
//        for(double value : delayLowPriority)
//         {
//           avgLowPriority = avgLowPriority + value;
//         }
//        EV << "Low Priority total value " << avgLowPriority << "s\n";
//        avgLowPriority = (double)avgLowPriority / (double)delayHighPriority.size();
////        recordScalar("avgLowPriority", avgLowPriority);
//    }

    // Log final statistics
    EV << "\nFinal Delay Statistics:\n";
    EV << "High Priority avg delay: " << avgHighPriority/lenHighPriority << "s\n";
    EV << "Medium Priority avg delay: " << avgMediumPriority/lenMediumPriority  << "s\n";
    EV << "Low Priority avg delay: " << avgLowPriority/lenLowPriority  << "s\n\n\n";

    for(int i = 0; i < 10; i++)
    {
        EV << "User "<< i << " avg delay: " << avgPerUser[i]/numMsgForEachUser[i]  << "s\n";
//        EV << avgPerUser[i] << "  " << numMsgForEachUser[i] << endl;
    }
}
