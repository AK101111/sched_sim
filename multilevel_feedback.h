#ifndef MULTILEVELFEED_
#define MULTILEVELFEED_
#include "utilities.h"

//randData is sorted by arrival time.
bool comp_f(process a, process b);
stats sch_multilevel_feedback(std::vector<process> &input1);

#endif