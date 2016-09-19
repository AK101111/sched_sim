#include "fcfs.h"
#include "rr.h"

int main()
{
  printf("Schedule FCFS\n");
  char infile[100];
  scanf("%s",infile);
    std::vector<process> Rand;
  parse(infile,Rand);
  stats statFCFS = startFCFS(Rand);
  printstat(statFCFS);
  stats statRR = startRR(Rand);
  printstat(statRR);
  return 0;
}