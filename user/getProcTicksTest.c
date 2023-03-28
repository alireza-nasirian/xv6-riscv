#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
    int pid = atoi(argv[1]);
    int ticks_passed = getProcTick(pid);
    printf("Ticks passed since start of process %d: %d\n", pid, ticks_passed);
    exit(0);
}