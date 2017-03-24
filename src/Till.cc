#include <stdlib.h>
#include "Till.h"
#include "QueueManager.h"

namespace caiaginillo
{
Define_Module(Till);


void Till::initialize()
{
    //message used in the scheduleAt function
    serviceCompleted = new cMessage("serviceCompleted");
    queue = new cQueue("queue");
    //time spent in the queue for check out
    qct = registerSignal("qct");
    //time spent in the check out
    ct = registerSignal("ct");
    //time spent in the queue for wrapping
    qwt = registerSignal("qwt");
    //time spent for wrapping
    wt = registerSignal("wt");
    //utilization
    u = registerSignal("u");
    //activity intervals
    activity = registerSignal("activity");
    //inactivity intervals
    inactivity = registerSignal("inactivity");
    //number of customer enqueued
    n_enqueued = registerSignal("n_enqueued");
    //add a reference of this till in the QueueManager's vector
    QueueManager* qm = (QueueManager*)getModuleByPath("Shop.qm");
    qm->addTill(this,getIndex());
    //at the beginning the till isn't serving anyone
    serving = NULL;
    workingTime = 0;
    scheduledTime = 0;
    changeStateTime = 0;
}


/*
 * generate a random time depending on:
 * 1) type of distribution selected
 * 2) type of service (check-out/wrap)
 * @param checkedOut
 *    - false: the customer has not cheked-out yet
 *    - true: the customer has already checked-out and he/she's asking for wrap
 * @return the time the service will take
 */
double Till::getServiceTime(bool checkedOut)
{
    //uniform distribution
    double serviceTime;
    if(getParentModule()->par("isUniformDistr"))
    {
        //customer has to check-out
        if(!checkedOut)
        {
            serviceTime = uniform(15,45);
            //serviceTime = 40;
        }
        //customer has to wrap
        else
        {
            serviceTime = uniform(90,120,1);
            //serviceTime = 80;
        }
    }
    //exponential distribution
    else
    {
        //customer has to check-out
        if(!checkedOut)
        {
            serviceTime = exponential(30);
            //serviceTime = 40;
        }
        //customer has to wrap
        else
        {
            serviceTime = exponential(105,1);
            //serviceTime = 80;
        }
    }
    //data to compute till utilization
    if(simTime() >= simulation.getWarmupPeriod())
    {
        workingTime += serviceTime;
    }
    scheduledTime = simTime() + serviceTime;
    if(simTime() < simulation.getWarmupPeriod() && simulation.getWarmupPeriod() < scheduledTime)
    {
        workingTime += scheduledTime - simulation.getWarmupPeriod();
    }
    return serviceTime;
}


/*
 * check how much time a customer has passed in queues or in services
 * @param c is the customer in which the statistic is stored
 * @param type is the type of time-interval:
 *      0: queuing check-out time
 *      1: check-out time
 *      2: queuing wrap time
 *      3: wrap time
 * @return the time the customer has passed in queues or in check-out/gift-wrap
 */
simtime_t Till::getTimeInterval(Customer* c,int type)
{
    simtime_t res = simTime();
    switch(type)
    {
        case 3: res -= c->getQwt();
        case 2: res -= c->getCt();
        case 1: res -= c->getQct();
        case 0: res -= c->getCreationTime();
    }
    return res;
}


/*
 * another customer is served unless the queue is empty
 */
void Till::nextCustomer()
{
    //there is at least one customer in the queue
    if(queue->length() > 0)
    {
        //select the next customer to be served and delete the customer from the queue
        serving = (Customer*)queue->pop();
        //set how long the customer has been in queue for check-out
        if(!serving->getCheckedOut())
        {
            serving->setQct(getTimeInterval(serving,0));
        }
        //set how long the customer has been in queue for gift-wrap
        else
        {
            serving->setQwt(getTimeInterval(serving,2));
        }
        //generate a service time depending on which service the customer is asking for
        double serviceTime = getServiceTime(serving->getCheckedOut());
        scheduleAt(simTime() + serviceTime, serviceCompleted);
    }
    //there are no customers in the queue
    else
    {
        //stop to work
        changeState(false);
        serving = NULL;
    }
}

/*
 * keeps track about the time a till starts/stops
 * for statistic on activity/inactivity
 * @param isNowWorking is true if the till is starting to work
 */
void Till::changeState(bool isNowWorking){
    simtime_t now = simTime();
    if(isNowWorking)
    {
        emit(inactivity,now - changeStateTime);
    }
    else
    {
        emit(activity, now - changeStateTime);
    }
    changeStateTime = now;
}

/*
 * returns how many customers are in the till (in the queue + who is served)
 */
int Till::getCustomerNum()
{
    return queue->length() + (int)(serving != NULL);
}

void Till::handleMessage(cMessage *msg)
{
    double serviceTime;
    //new customer arrives
    if(!msg->isSelfMessage())
    {
        Customer* customerMsg = check_and_cast<Customer*>(msg);
        ev << getName() << "[" << getIndex() << "]: " << queue->length() << endl;
        //the till is not serving anyone
        if(!serving)
        {
            //start to work
            changeState(true);
            //serve the customer immediately
            serving = customerMsg;
            serviceTime = getServiceTime(customerMsg->getCheckedOut());
            scheduleAt(simTime() + serviceTime, serviceCompleted);
        }
        //not empty queue
        else
        {
            //put the customer in the queue
            queue->insert(customerMsg);
        }
        emit(n_enqueued,queue->length());
    }
    //a service has completed
    else
    {
        bool separatedTills = getParentModule()->par("separatedTills");
        //unified tills
        if(!separatedTills)
        {
            //check-out has finished in any case
            if(!serving->getCheckedOut())
            {
                serving->setCheckedOut(true);
                serving->setCt(getTimeInterval(serving,1));
            }
            else
            {
                serving->setWt(getTimeInterval(serving,3));
            }
            //check if wrap is needed
            if(serving->getHasToWrap())
            {
                //wrapping service is scheduled
                serving->setHasToWrap(false);
                serviceTime = getServiceTime(serving->getCheckedOut());
                scheduleAt(simTime() + serviceTime, serviceCompleted);
            }
            //wrap is not needed
            else
            {
                emit(qct,serving->getQct());
                emit(ct,serving->getCt());
                emit(qwt,serving->getQwt());
                emit(wt,serving->getWt());
                send(serving, "exit");
                nextCustomer();
            }
        }
        //a service is finished in separated tills
        else
        {
            //a checkout operation is finished
            if(!serving->getCheckedOut())
            {
                serving->setCheckedOut(true);
                serving->setCt(getTimeInterval(serving,1));
                emit(qct,serving->getQct());
                emit(ct,serving->getCt());
                //the customer needs to wrap the gift
                if(serving->getHasToWrap()){
                    send(serving,"out");
                }
                //the customer leaves the shop without wrapping
                else
                {
                    send(serving, "exit");
                }
            }
            //wrapping is finished
            else
            {
                serving->setWt(getTimeInterval(serving,3));
                emit(qwt,serving->getQwt());
                emit(wt,serving->getWt());
                send(serving, "exit");
            }
            nextCustomer();
        }
    }
}


void Till::finish()
{
    simtime_t finishTime = simTime();
    //if the current job should have finished after the end of the simulation
    //workingTime is adjusted
    if(scheduledTime > finishTime)
    {
        workingTime -= scheduledTime - finishTime;
    }
    emit(u, workingTime/(finishTime - simulation.getWarmupPeriod()));
    cancelEvent(serviceCompleted);
    delete serviceCompleted;
    if (serving)
    {
        changeState(false);
        delete serving;
    }
    queue->clear();
    delete queue;
}


} //namespace
