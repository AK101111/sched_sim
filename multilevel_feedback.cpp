//Simulting with 2 queues {fore, back}
#include "multilevel_feedback.h"

#define LIMIT 25
const int QUANTUM  = 5;

bool comp_f(process a, process b){ 
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

stats sch_multilevel_feedback(std::vector<process> &input1){
  // std::cout << "hey!" << std::endl;
  stats mlq_stat;
  int curr_time = 0;
  int on_time = 0;
  int waiting_time = 0;
  int num_process = input1.size();

  std::vector<process> foreground1; // High priority
  std::vector<int> foretime1;
  std::vector<process> background1; // Low priority

  // Schedule foreground1 and background1 with time sharing of 4:1
  sort(input1.begin(), input1.end(), comp_f);
  process incoming_job = input1.front(); bool lapsed;
  // std::cout << "hey!" << std::endl;
  bool t = true;
  while (true){
    // std::cout << "hey! " << curr_time << std::endl;
    while (t && curr_time >= incoming_job.arrival_time){
      if (incoming_job.burst_time != 0){
        if (incoming_job.priority <= 2){
          foreground1.push_back(incoming_job);
          foretime1.push_back(0);
          // std::cout << "foreground1 pushed " << curr_time << std::endl;
        }
        else{
          background1.push_back(incoming_job);
          // std::cout << "background1 pushed " << std:: endl;
        }
      }
      input1.erase(input1.begin());      
      if (input1.size() == 0){
        t = false;
        break;
      }
      incoming_job = input1.front();
    }

    bool flapsed = false; // indicates if a fore-job has executed yet
    bool blapsed = false; // indicates if a back-job has executed yet
    if (!t && foreground1.size() == 0 && background1.size() == 0){
      break;
    }
    // Round Robin for foreground1 processes
    if (foreground1.size() != 0 && foreground1.front().burst_time != 0){
      flapsed = true;   
      if (curr_time % QUANTUM == 0){
        //Move first job to last every QUANTUM
        if(foretime1.front() >= LIMIT){
          process frt = foreground1.front();
          foreground1.erase(foreground1.begin());
          background1.push_back(frt);
        }
        else{
          process frt = foreground1.front();
          foreground1.erase(foreground1.begin());
          foreground1.push_back(frt);
          int ftime = foretime1.front();
          foretime1.erase(foretime1.begin());
          foretime1.push_back(ftime);
        }
      }      

      foreground1.front().burst_time -= 1;
      foretime1.front()++;
      waiting_time += (foreground1.size() - 1);
            
      if (foreground1.front().burst_time == 0){        
        foreground1.erase(foreground1.begin());
        foretime1.erase(foretime1.begin());
      }
    }
    //FIFO for background1 processes
    if (flapsed == false && background1.size() != 0){
      blapsed = true;
      background1.front().burst_time -= 1;
      waiting_time += (background1.size() - 1);
      
      if (background1.front().burst_time == 0)
        background1.erase(background1.begin());
    }

    if (flapsed == true && background1.size() != 0){
      waiting_time += background1.size();      
    }

    if (flapsed || blapsed) on_time++; //On if any of process occurs
    curr_time++;
  }  

  mlq_stat.avg_cpu_util = (float)on_time/curr_time;
  mlq_stat.avg_throughput = (float)curr_time/num_process;
  mlq_stat.avg_waiting_time = (float)waiting_time/num_process;
  return mlq_stat;
}