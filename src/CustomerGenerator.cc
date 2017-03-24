#include "CustomerGenerator.h"
#include "Customer_m.h"

namespace caiaginillo {

Define_Module(CustomerGenerator);

/*
 * returns a random value with the specified distribution
 */
double CustomerGenerator::getArrivalTime()
{
    if(getParentModule()->par("isUniformDistr"))
    {
        if(par("peakHours"))
        {
            return uniform(0,30);
        }
        return uniform(0, 120);
    }
    else
    {
        if(par("peakHours"))
        {
            return exponential(15);
        }
        return exponential(60);
    }
}

void CustomerGenerator::initialize()
{
    newCustomerArrives = new cMessage("newCustomerArrives");
    scheduleAt(simTime() + getArrivalTime(),newCustomerArrives);
}

void CustomerGenerator::handleMessage(cMessage *msg)
{
    Customer* c = new Customer();
    double delay;
    //set if Customer has to gift-wrap the present with probability p
    double p = par("p");
    c->setCreationTime(simTime());
    c->setHasToWrap(uniform(0,1,1) < p);
    //send the Customer to QueueManager
    send(c,"out");
    //schedule another Customer arrival
    delay = getArrivalTime();
    scheduleAt(simTime() + delay,newCustomerArrives);
}

void CustomerGenerator::finish(){
    cancelEvent(newCustomerArrives );
    delete newCustomerArrives;
}

} //namespace
