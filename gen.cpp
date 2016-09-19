#include "utilities.h"

int main(int argc, char *argv[])
{
    std::vector<process> Rand;
    genRandom(Rand,atoi(argv[1]));
    writeVector(argv[2],Rand);
    printf("Creating Data of size %d in %s\n",atoi(argv[1]),argv[2]);
    return 0;
}