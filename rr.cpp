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
    std::set<int>S;
    std::vector<process> RR;
    while(numProcess){
        process top;
        if(curr<randData.size())
            top = randData[curr];
        
        if(top.arrival_time <= curr_time){
            if(S.find(top.pid) == S.end()){
                S.insert(top.pid);
                RR.push_back(top);
                curr++;
            }
        }
        
        if(rr_curr>=RR.size())
            rr_curr=0;
        
        if(RR.empty()){
            curr_time = top.arrival_time;
            continue;
        }
        
        if(RR[rr_curr].burst_time > 0){
            RR[rr_curr].burst_time -= QUANTUM;
            if(RR[rr_curr].burst_time == 0){
                RR.erase(RR.begin()+rr_curr);
                numProcess--;
                rr_curr = 0;
            }
            on_time += QUANTUM;
            if(RR.size()){
                rr_curr = (rr_curr+1)%RR.size();
                waiting_time += (RR.size()-1)*QUANTUM;
            }
        }
        curr_time += QUANTUM;
    }
    numProcess = randData.size();
    stat.avg_cpu_util = (float)on_time/curr_time;
    stat.avg_throughput = (float)curr_time/numProcess;
    stat.avg_waiting_time = (float)waiting_time/numProcess;
    return stat;
}