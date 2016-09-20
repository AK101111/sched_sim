//Simulting with 2 queues {fore, back}
#include "multilevel_que.h"

#define QUANTUM 5

bool comp(process a, process b){ 
  if (a.arrival_time < b.arrival_time){
    return true;
  }
  else if (a.arrival_time == b.arrival_time && a.priority < b.priority){
    return true;
  }
  else{
    return false;
  }
}

stats sch_multilevel_que(std::vector<process> &input){
  stats mlq_stat;
  int curr_time = 0;
  int on_time = 0;
  int waiting_time = 0;
  int num_process = input.size();

  std::vector<process> foreground; // High priority
  std::vector<process> background; // Low priority

  // Schedule foreground and background with time sharing of 4:1
  sort(input.begin(), input.end(), comp);
  process incoming_job = input.front(); bool lapsed;
  bool t = true;
  while (true){
    while (t && curr_time >= incoming_job.arrival_time){
      if (incoming_job.burst_time != 0){
        if (incoming_job.priority <= 2){
          foreground.push_back(incoming_job);
        }
        else{
          background.push_back(incoming_job);
        }
      }
      input.erase(input.begin());      
      if (input.size() == 0){
        t = false;
        break;
      }
      incoming_job = input.front();
    }

    bool flapsed = false; // indicates if a fore-job has executed yet
    bool blapsed = false; // indicates if a back-job has executed yet
    if (!t && foreground.size() == 0 && background.size() == 0){
      break;
    }
    // Round Robin for Foreground processes
    if (foreground.size() != 0 && foreground.front().burst_time != 0){
      flapsed = true;   
      if (curr_time % QUANTUM == 0){
        //Move first job to last every QUANTUM
        process frt = foreground.front();
        foreground.erase(foreground.begin());
        foreground.push_back(frt);
      }      

      foreground.front().burst_time -= 1;
      waiting_time += (foreground.size() - 1);
            
      if (foreground.front().burst_time == 0){        
        foreground.erase(foreground.begin());
      }
    }
    //FIFO for background processes
    if (flapsed == false && background.size() != 0){
      blapsed = true;
      background.front().burst_time -= 1;
      waiting_time += (background.size() - 1);
      
      if (background.front().burst_time == 0)
        background.erase(background.begin());
    }

    if (flapsed == true && background.size() != 0){
      waiting_time += background.size();      
    }

    if (flapsed || blapsed) on_time++; //On if any of process occurs
    curr_time++;
  }  

  mlq_stat.avg_cpu_util = (float)on_time/curr_time;
  mlq_stat.avg_throughput = (float)curr_time/num_process;
  mlq_stat.avg_waiting_time = (float)waiting_time/num_process;
  return mlq_stat;
}