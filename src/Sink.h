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

#ifndef __SCHED_TST_SINK_H_
#define __SCHED_TST_SINK_H_

#include <omnetpp.h>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Sink : public cSimpleModule
{
private:
    simsignal_t lifetimeSignal;
    simsignal_t delaySignalHighPriority;
    simsignal_t delaySignalMediumPriority;
    simsignal_t delaySignalLowPriority;

    double avgPerUser[10] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    double numMsgForEachUser[10] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    double avgHighPriority = 0.0f;
    double avgMediumPriority = 0.0f;
    double avgLowPriority = 0.0f;

    double lenHighPriority = 0.0f;
    double lenMediumPriority = 0.0f;
    double lenLowPriority = 0.0f;

   std::vector<double> delayHighPriority;
   std::vector<double> delayMediumPriority;
   std::vector<double> delayLowPriority;
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
//    void recordDelay(simtime_t delay, long priority);
    virtual void finish() override;
};

#endif
