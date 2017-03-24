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

#ifndef __CAIAGINILLO_TILL_H_
#define __CAIAGINILLO_TILL_H_

#include <omnetpp.h>
#include <queue>
#include "Customer_m.h"

namespace caiaginillo
{

class Till : public cSimpleModule
{
  private:
    //statistic parameters
    simsignal_t qct, ct, qwt, wt, u, inactivity, activity, n_enqueued;

    //message for the timer
    cMessage* serviceCompleted;
    //queue of customers
    cQueue* queue;
    //the customer under service
    Customer* serving;

    //total time the till is serving someone
    simtime_t workingTime;
    //at what time the service should end
    //it is used to correct the workingTime variable when the simulation ends
    simtime_t scheduledTime;
    //time when the till starts or stops
    simtime_t changeStateTime;

    double getServiceTime(bool checkedOut);
    void nextCustomer();
    void changeState(bool isNowWorking);
    simtime_t getTimeInterval(Customer* c, int type);
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
  public:
    int getCustomerNum();
};


} //namespace

#endif
