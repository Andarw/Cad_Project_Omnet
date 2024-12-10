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

#include "Source.h"

Define_Module(Source);

Source::Source()
{
    sendMessageEvent = nullptr;
}

Source::~Source()
{
    cancelAndDelete(sendMessageEvent);
}

void Source::initialize()
{
    sendMessageEvent = new cMessage("sendMessageEvent");
    scheduleAt(simTime(), sendMessageEvent);
    int nrUsers = par("usersCount");
        int nrPackets = par("packetsPerUser");
        int PacketLength = 1;
        double schedulingCycle = 1.0;
        double netwload = par("networkLoad");
        int nrChannels = par("channels");
}


void Source::handleMessage(cMessage* msg)
{

    int nrUsers = par("usersCount");
    int nrPackets = par("packetsPerUser");
    int PacketLength = 1;
    double schedulingCycle = 1.0;
    double netwload = par("networkLoad");
    int nrChannels = par("channels");

    for(int i=0;i<nrPackets;i++){
        ASSERT(msg == sendMessageEvent);
        cMessage* job = new cMessage("job");
        send(job, "txPackets");
    }


    //double sendingTime;
    //sendingTime = par("sendIaTime").doubleValue();

    if(simTime() >= par("MAX_Sim").doubleValue()){
        endSimulation();
    }

    //MAX_SiM se pune in ini si citeste de acolo si trebuie sa fie de cel putin 1000 de ori mai mare
    // decat sendingTime pt netwload 80% (ideal de 10 mii de ori mai mare)


    //scheduleAt(simTime()+ exponential(sendingTime));

    // sendingTime = function(network load)

    /*netwload = data_generated / transfer_rate
     *

data_generated = nrUsers* nrPackets *PacketLength / sendingTime
PacketLength = 1*
transfer_rate = nr_of_channels/schedulingCycle;
schedulingCycle = 1 ms*
netwload = (nrUsersnrPacketsPacketLengthschedulingCycle)/(sendingTimenr_of_channels)*sendingTime =  (nrUsersnrPacketsPacketLengthschedulingCycle)/(netwload*nr_of_channels)*
*/

    // Parameters to calculate sending time



    //Calculate sending time based on the network load
    double sendingTime = (nrUsers * nrPackets * PacketLength * schedulingCycle) / (netwload * nrChannels);

    // Output the calculated sending time for debugging
    EV << "Calculated Sending Time: " << sendingTime << " ms" << endl;

    scheduleAt(simTime() + exponential(sendingTime), sendMessageEvent);
}

//void Source::handleMessage(cMessage *msg)
//
//
//{
//    ASSERT(msg == sendMessageEvent);
////for(j=0;j<nrPackets;j++){
//    cMessage *job = new cMessage("job");
//    //the "job" message can have a parameter PacketLength !
//    send(job, "txPackets");
//
////}
//    //end for
//
//    double sendingTime;
//    sendingTime = par("sendIaTime").doubleValue();
//
//   // if(simTime() >= MAX_SiM) endSimulation();
//    //MAX_SiM se pune in ini si citeste de acolo si trebuie sa fie de cel putin 1000 de ori mai mare
//    // decat sendingTime pt netwload 80% (ideal de 10 mii de ori mai mare)
//
//
//    //scheduleAt(simTime()+ exponential(sendingTime));
//
//    // sendingTime = function(network load)
//
//    /*netwload = data_generated/ transfer_rate
//     *
//     * data_generated = nrUsers(e)* nrPackets(1) *PacketLength(1) / sendingTime
//     * PacketLength = 1
//     *
//     * transfer_rate = nr_of_channels/schedulingCycle ;
//     * schedulingCycle = 1 ms
//     *= >
//     * netwload = (nrUsers*nrPackets*PacketLength*schedulingCycle)/(sendingTime*nr_of_channels)
//     *
//     *sendingTime =  (nrUsers*nrPackets*PacketLength*schedulingCycle)/(netwload*nr_of_channels)
//     *
//     * */
//
//
//
//    scheduleAt(simTime()+ exponential(sendingTime), sendMessageEvent);
//
//    //scheduleAt(simTime()+par("sendIaTime").doubleValue(), sendMessageEvent);
//}


/*
void Source::initialize()
{
    // TODO - Generated method body
}

void Source::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}
*/
