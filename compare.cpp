#include "fcfs.h"
#include "rr.h"
#include "sjf.h"
#include "priority.h"
int main()
{
  printf("Schedule FCFS\n");
  char infile[100];
  scanf("%s",infile);
    std::vector<process> Rand;
  parse(infile,Rand);
  // stats statFCFS = startFCFS(Rand);
  // printstat(statFCFS);
  stats statRR = startRR(Rand);
  printstat(statRR);
  // stats statSJF = startSJF(Rand);
	// printstat(statSJF);
  // stats statPRIORITY = startPRIORITY(Rand);
  // printstat(statPRIORITY);
	return 0;
}