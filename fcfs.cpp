#include "fcfs.h"
#include "utilities.h"

//randData is sorted by arrival time.
stats startFCFS(std::vector<process> &randData)
{
	stats stat;
	int curr_time = 0;
  int on_time = 0;
  int waiting_time = 0;
  int numProcess = randData.size();
  std::queue<process> Q;
  for(std::vector<process>::iterator it = randData.begin(); it != randData.end(); ++it)
      Q.push(*it);
	while(!Q.empty()){
		// FCFS
    process scheduling_process = Q.front();
		Q.pop();

		if(curr_time < scheduling_process.arrival_time){
      // Waiting, no process
      curr_time = scheduling_process.arrival_time;
    }else{
      // Job ongoing, some waiting
      waiting_time += (Q.size())*(curr_time - scheduling_process.arrival_time);
    }

    // Scheduling
    curr_time += scheduling_process.burst_time;
    on_time += scheduling_process.burst_time;
	}
  stat.avg_cpu_util = (float)on_time/curr_time;
  stat.avg_throughput = (float)curr_time/numProcess;
  stat.avg_waiting_time = (float)waiting_time/numProcess;
  return stat;
}