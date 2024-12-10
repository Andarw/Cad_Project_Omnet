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

#include "myQ.h"

Define_Module(MyQ);

void MyQ::initialize()
{
    queue.setName("queue");
    radioLinkQuality = getParentModule() -> par("radioLinkQuality").doubleValue();
}

void MyQ::handleMessage(cMessage *msg)

{

    int queueLength = queue.getLength();

    if (msg->arrivedOn("rxPackets")){
        queue.insert(msg);
    } else if (msg->arrivedOn("rxScheduling")){
        //read parameters from msg
        int nrOfAllocatedRadioBlocks = (int)msg->par("nrBlocks");
        long userPriority = (long)msg->par("userPriority");
        long userIndex = (long)msg->par("userIndex");
        delete msg;

     for(int j = 0; j < nrOfAllocatedRadioBlocks && !queue.isEmpty(); j++ )
     {
        msg = (cMessage *)queue.pop();
        msg->addPar("userPriority");
        msg->addPar("userIndex");
        msg->par("userPriority").setLongValue(userPriority);
        msg->par("userIndex").setLongValue(userIndex);
        send(msg, "txPackets");
     }
   }

    //after sending the messages we report back to Scheduler
    queueLength = queue.getLength();
    cMessage *queueInfo = new cMessage("queueInfo");
    queueInfo->addPar("queueLength_info");
    queueInfo->addPar("radioLinkQuality_info");
    queueInfo->par("queueLength_info").setLongValue(queueLength);
    queueInfo->par("radioLinkQuality_info").setDoubleValue(radioLinkQuality);

    //only for test
    int i =  getParentModule()->getIndex();

    long queueLength_info_tst = queueInfo->par("queueLength_info");
    double radioLinkQuality_info_tst = queueInfo->par("radioLinkQuality_info");
//    EV << "MyQ: queueLength[" << i<<"] = " << queueLength << " radioLinkQuality =" << radioLinkQuality << " queueLength_info_tst = " << queueLength_info_tst << " radioLinkQuality_info_tst = " << radioLinkQuality_info_tst << endl;
    send(queueInfo, "txInfo");

    /* Communication between modules using parameters
    queueLength = queue.getLength();
    cPar&  queueLengthpar = par("queueLengthp");
    queueLengthpar.setIntValue(queueLength);
    //next 2 statements only for debug
    int qt = par("queueLengthp").intValue();
    EV << "qt= "<<qt <<endl;
    */

}
