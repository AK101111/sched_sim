#include "sjf.h"
struct burst_comp
{
    bool operator()(const process &a, const process &b) const
    {
        return (a.burst_time < b.burst_time);
    }
};

stats startSJF(std::vector<process> &randData){
    stats stat;
    int curr_time = 0;
    int on_time = 0;
    int waiting_time = 0;
    std::priority_queue<process, std::vector<process>, burst_comp> waiting;
    int numProcess = randData.size();
    int curr = 0;
    while(numProcess){
        process top;
        if(curr < randData.size()){
            top = randData[curr];
        }
        
        if(top.arrival_time <= curr_time){
            waiting.push(top);
            curr++;
        }
        
        if(!waiting.empty()){
            process to_execute = waiting.top();
            curr_time += to_execute.burst_time;
            on_time += to_execute.burst_time;
            waiting_time += (waiting.size() - 1)* (to_execute.burst_time);
            waiting.pop();
            numProcess--;
        }
        else{
            curr_time = top.arrival_time;
        }
    }
    numProcess = randData.size();
    stat.avg_cpu_util = (float)on_time/curr_time;
    stat.avg_throughput = (float)curr_time/numProcess;
    stat.avg_waiting_time = (float)waiting_time/numProcess;
    return stat;
    
}