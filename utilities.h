#ifndef UTILITIES_
#define UTILITIES_

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
#include <random>
#include <functional>
#include <time.h>
#include <string.h>

#define RUNNING 1
#define WAITING 0

#define MAX_MAX 500
#define BURST_TIME 10
#define PRIORITY 5

typedef struct process{
  int pid;
  int burst_time;
  int arrival_time;
  int priority;
  int state;
}process;

bool compareByArrival(const process &a, const process &b);

typedef struct stats{
  float avg_cpu_util;
  float avg_throughput;
  float avg_waiting_time;
}stats;

void genRandom(std::vector<process> &Rand, int size);
void addtovector(char *line, std::vector<process> &Data);
int parse(char infile[], std::vector<process> &Data);
void writeVector(const char outfile[], std::vector<process> &Rand);
void printstat(stats stat);

#endif


