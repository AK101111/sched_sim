#include "fcfs.h"
#include "rr.h"
#include "sjf.h"
#include "priority.h"
#include "multilevel_que.h"
#include "multilevel_feedback.h"

int main()
{
  printf("Schedule multilevel_que\n");
  char infile[100];
  scanf("%s",infile);
    std::vector<process> Rand;
  parse(infile,Rand);
  stats statFCFS = startFCFS(Rand);
  printstat(statFCFS);
 //  stats statRR = startRR(Rand);
 //  printstat(statRR);
 //  stats statSJF = startSJF(Rand);
	// printstat(statSJF);
 //  stats statsPRIORITY = startPRIORITY(Rand);
 //  printstat(statsPRIORITY);
 //  stats mlq = sch_multilevel_que(Rand);
 //  printstat(mlq);
 //  stats mlq_feedback = sch_multilevel_feedback(Rand);
 //  printstat(mlq_feedback);
	return 0;
}
