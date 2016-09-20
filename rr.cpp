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
        while((curr < randData.size()) && (randData[curr].arrival_time <= curr_time)){
            RR.push_back(randData[curr]);
            curr++;
        }
        if(!RR.empty()){
            RR[rr_curr].burst_time -= QUANTUM;
            on_time += QUANTUM;
            if(RR[rr_curr].burst_time <= 0){
                RR.erase(RR.begin() + rr_curr);
                numProcess--;
                if(RR.size() == 0){
                    rr_curr = 0;
                }
                else{
                    rr_curr = rr_curr%(RR.size());
                    waiting_time += QUANTUM * (RR.size());
                }
            }
            else{
                rr_curr = (rr_curr+1)%(RR.size());
                waiting_time += QUANTUM * (RR.size() - 1);
            }
        }
        curr_time += QUANTUM;
    }
    numProcess = randData.size();
    stat.avg_cpu_util = (float)on_time/curr_time;
    stat.avg_throughput = (float)curr_time/randData.size();
    stat.avg_waiting_time = (float)waiting_time/randData.size();
    return stat;
}