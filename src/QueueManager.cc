#include "QueueManager.h"
#include "Customer_m.h"

namespace caiaginillo {

Define_Module(QueueManager);

void QueueManager::initialize()
{

}

/*
 * Insert a till in the vector of till in a specified index
 * @param t is the till to insert
 * @param index is the index in which the till is placed
 */
void QueueManager::addTill(Till* t, int index)
{
    tills.insert(tills.begin() + index, t);
}
/*
 * Search the till with the minimum # of customer
 * @param lowBound is the lower limit for the index at which the QueueManager
 * starts to look for the min queue in the vector of tills
 * @param upBound is the upper bound for the index at which the QueueManager
 * stops to look for the min queue in the vector of tills
 * @return the index of the till which has the min queue within the specified
 * bounds
 */
int QueueManager::enqueueCustomer(int lowBound, int upBound)
{
    int min = tills[lowBound]->getCustomerNum();
    std::vector<int> minSizeTillIndexes;
    for(int i = lowBound+1; i < upBound; i++)
    {
        int temp = tills[i]->getCustomerNum();
        if(min > temp)
        {
            min = temp;
        }
    }
    for(int j = lowBound; j < upBound; j++)
    {
        if(tills[j]->getCustomerNum() == min)
        {
            minSizeTillIndexes.push_back(j);
        }
    }
    int chosenIndex = (int)uniform(0,minSizeTillIndexes.size());
    return minSizeTillIndexes[chosenIndex];
}

void QueueManager::handleMessage(cMessage *msg)
{
    Customer* c = check_and_cast<Customer*>(msg);
    int nTill = par("nTill");
    int kTill = par("kTill");
    bool separatedTills = getParentModule()->par("separatedTills");
    int tillIndex;
    //the customer is asking for check-out
    if(!c->getCheckedOut())
    {
        //in not-separated tills the customer can be enqueued in every till
        if(!separatedTills)
        {
            tillIndex = enqueueCustomer(0,nTill);
        }
        //in separated tills the customer can be enqueued in the tills which
        //perform check-out
        else
        {
            tillIndex = enqueueCustomer(0,nTill - kTill);
        }
    }
    //the customer is asking for gift-wrap. In this case the tills are separated
    //otherwise the customer wouldn't have come back to QueueManager
    else
    {
        tillIndex = enqueueCustomer(nTill - kTill, nTill);
    }
    send(msg,"outTill",tillIndex);
}

} //namespace
