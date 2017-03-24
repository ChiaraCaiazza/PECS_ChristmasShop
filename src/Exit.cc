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

#include "Exit.h"
#include "Customer_m.h"

namespace caiaginillo {

Define_Module(Exit);

void Exit::initialize()
{
    qt = registerSignal("qt");
    rt = registerSignal("rt");
    qt_notWrapped = registerSignal("qt_notWrapped");
    qt_wrapped = registerSignal("qt_wrapped");
    rt_notWrapped = registerSignal("rt_notWrapped");
    rt_wrapped = registerSignal("rt_wrapped");
}

void Exit::handleMessage(cMessage *msg)
{
    Customer* c = check_and_cast<Customer*>(msg);
    simtime_t queueingTime = c->getQct() + c->getQwt();
    simtime_t responseTime = simTime() - c->getCreationTime();
    emit(qt, queueingTime);
    emit(rt, responseTime);
    //the client didn't wrap the good
    if (c->getWt() == 0)
    {
        emit(qt_notWrapped, queueingTime);
        emit(rt_notWrapped, responseTime);
    }
    else
    {
        emit(qt_wrapped, queueingTime);
        emit(rt_wrapped, responseTime);
    }
    delete msg;
}

} //namespace
