
package caiaginillo;

simple QueueManager
{
    parameters:
        @display("i=block/dispatch,white");
        int nTill;
        int kTill;
    gates:
        input inCustomer;
        input inTill[nTill - kTill] @loose;
        output outTill[nTill];
}
