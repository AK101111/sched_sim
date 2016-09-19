#include "rr.h"


stats startRR(std::vector<process> &randData){
    stats stat;
    int QUANTUM = 1;
    int curr_time = 0;
    int on_time = 0;
    int waiting_time = 0;
    
    int numProcess = randData.size();
    int curr=0;
    int rr_curr = 0;
    
    std::vector<process> RR;
    while(numProcess){
        process top = randData[curr];
        curr_time += QUANTUM;
        if(top.arrival_time <= curr_time){
            RR.push_back(top);
            curr++;
        }
        
        if(rr_curr>RR.size())
            rr_curr=0;
        
        if(RR.empty()){
            curr_time = top.arrival_time;
            continue;
        }
        
        if((RR[rr_curr].burst_time) > 0){
            RR[rr_curr].burst_time -= QUANTUM;
            if(RR[rr_curr].burst_time == 0){
                RR.erase(RR.begin()+rr_curr);
                numProcess--;
            }
            on_time += QUANTUM;
            waiting_time += (RR.size()-1)*QUANTUM;
            rr_curr = (rr_curr+1)%(RR.size());
        }
    }
    printf("%d %d\n",curr_time,numProcess );
    numProcess = randData.size();
    //stat.avg_cpu_util = (float)on_time/curr_time;
    //stat.avg_throughput = (float)curr_time/numProcess;
    //stat.avg_waiting_time = (float)waiting_time/numProcess;
    return stat;
}