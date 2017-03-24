
package caiaginillo;

simple Till
{
    parameters:
        //queuing-check-out time
    	@signal[qct](type=simtime_t);
    	//check-out time
    	@signal[ct](type=simtime_t);
    	//queuing-wrap time
    	@signal[qwt](type=simtime_t);
    	//wrap time
    	@signal[wt](type=simtime_t);
    	//utilization
    	@signal[u](type=double);
    	//activity period
    	@signal[activity](type=simtime_t);
    	//inactivity period
    	@signal[inactivity](type=simtime_t);
    	//number of customer enqueued
    	@signal[n_enqueued](type=simtime_t);
    	
    	@statistic[qct](record=vector,mean);
    	@statistic[ct](record=vector,mean);
    	@statistic[qwt](record=vector,mean);
    	@statistic[wt](record=vector,mean);
    	@statistic[u](record=last);
    	@statistic[activity](record=vector);
    	@statistic[inactivity](record=vector);
    	@statistic[n_enqueued](record=vector);
        @display("i=block/queue,red");
        @display("q=queue");
    gates:
        input in;
        output out @loose;
        output exit;
}
