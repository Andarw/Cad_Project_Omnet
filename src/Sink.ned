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

//
// TODO auto-generated module
//
package cad_project;
simple Sink
{
 parameters:
        int gateSize;
        @display("i=block/sink");
        @signal[lifetime](type="simtime_t");
        @signal[delayHighPriority](type="simtime_t");
        @signal[delayMediumPriority](type="simtime_t");
        @signal[delayLowPriority](type="simtime_t");
        @statistic[lifetime](title="lifetime of arrived jobs"; unit=s; record=vector,mean,max; interpolationmode=none);
        @statistic[delayHighPriority](title="High Priority Delay"; record=vector,mean,max,timeavg,histogram);
        @statistic[delayMediumPriority](title="Medium Priority Delay"; record=vector,mean,max,timeavg,histogram);
        @statistic[delayLowPriority](title="Low Priority Delay"; record=vector,mean,max,timeavg,histogram);
    gates:
        input rxPackets[gateSize];

}
