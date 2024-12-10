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
simple Source
{
     parameters:
         double sendIaTime @unit(ms) = default(10 ms);
        double MAX_Sim @unit(ms) = default(10000 ms);
        double networkLoad = default(0.1);
        int packetsPerUser = default(4);
        int usersCount = default(3);
        int channels = default(10);
        @display("i=block/source");
    gates:
        output txPackets;
}
