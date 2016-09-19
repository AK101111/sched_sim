#include "utilities.h"

bool compareByArrival(const process &a, const process &b)
{
  return (a.arrival_time < b.arrival_time);
}

void genRandom(std::vector<process> &Rand, int size)
{
  std::uniform_int_distribution<int> randomNode(1,MAX_MAX-1);
    short seedr = clock()%MAX_MAX;
    std::default_random_engine generator{seedr};
    
    
  for(int i=0; i<size; ++i){
    int pid = randomNode(generator);
    int burst_time = randomNode(generator)%BURST_TIME;
    if(burst_time)
      burst_time++;
    int arrival_time = randomNode(generator)%(MAX_MAX-1);
    int priority = randomNode(generator)%PRIORITY;
    int state = 0;
    process p;
      p.pid = pid; p.burst_time = burst_time;
      p.arrival_time = arrival_time; p.priority = priority;
      p.state = 0;
      Rand.push_back(p);
  }

  std::sort(Rand.begin(), Rand.end(), compareByArrival);
}

void addtovector(char *line, std::vector<process> &Data)
{
  const char s1[2] = " ";
  
  char *token;
  
  /* get the first token */
  token = strtok(line, s1);
  
  int pid = atoi(token);
  token = strtok(NULL, s1);

  int burst_time = atoi(token);
  token = strtok(NULL, s1);

  int arrival_time = atoi(token);
  token = strtok(NULL, s1);

  int priority = atoi(token);
  token = strtok(NULL, s1);

  int state = atoi(token);
  token = strtok(NULL, s1);
    
    process p;
    p.pid = pid; p.burst_time = burst_time;
    p.arrival_time = arrival_time; p.priority = priority;
    p.state = state;
    Data.push_back(p);

}

int parse(char infile[], std::vector<process> &Data)
{
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  
  fp = fopen(infile, "r");
  if (fp == NULL)
      return -1;
  if((read = getline(&line, &len, fp)) == -1)
      return -1;
  int numLines = atoi(line);
  
  while ((read = getline(&line, &len, fp)) != -1) {
      addtovector(line,Data);
  }
  
  fclose(fp);
  if (line)
      free(line);
  return 0;
}

void writeVector(const char outfile[], std::vector<process> &Rand)
{
    freopen(outfile,"w",stdout);
    printf("%d\n",Rand.size());
    for(int i=0;i<Rand.size();++i){
        printf("%d %d %d %d %d\n", Rand[i].pid, Rand[i].burst_time,
         Rand[i].arrival_time, Rand[i].priority, Rand[i].state);
    }
    fclose (stdout);
}

void printstat(stats stat)
{
    printf("avg_cpu_util %f avg_throughput %f process/sec avg_waiting time %f s\n",
           stat.avg_cpu_util,stat.avg_throughput,stat.avg_waiting_time);
}