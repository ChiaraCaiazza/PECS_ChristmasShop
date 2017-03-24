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

package caiaginillo;

//
// TODO auto-generated module
//
simple Exit
{
    parameters:
        int nTill;
        @signal[qt](type=simtime_t);
        @signal[rt](type=simtime_t);
        @signal[qt_notWrapped](type=simtime_t);
        @signal[qt_wrapped](type=simtime_t);
        @signal[rt_notWrapped](type=simtime_t);
        @signal[rt_wrapped](type=simtime_t);
        @statistic[qt](record=stats);
        @statistic[rt](record=stats);
        @statistic[qt_notWrapped](record=vector,mean);
        @statistic[qt_wrapped](record=vector,mean);
        @statistic[rt_notWrapped](record=vector,mean);
        @statistic[rt_wrapped](record=vector,mean);
        @display("i=block/departure");
    gates:
        input in[nTill];
}
