#include "fcfs.h"
#include "rr.h"
#include "sjf.h"
#include "priority.h"
#include "multilevel_que.cpp"

int main()
{
  printf("Schedule multilevel_que\n");
  char infile[100];
  scanf("%s",infile);
    std::vector<process> Rand;
  parse(infile,Rand);
  stats statFCFS = startFCFS(Rand);
  printstat(statFCFS);
  // stats statRR = startRR(Rand);
  // printstat(statRR);
  stats statSJF = startSJF(Rand);
	printstat(statSJF);
  // stats mlq = sch_multilevel_que(Rand);
  // printstat(mlq);
	return 0;
}
