#include "types.h"
#include "user.h"
#include "../kernel/param.h"
#include "../kernel/sysinfo.h"

int main(int argc, char *argv[])
{
    struct sysinfo info;


/*    if (sysinfo(&info) == -1) {
        printf("Error: sysinfo failed\n");
        exit(0);
    }*/

    sysinfo(&info);

    printf("Uptime: %l\n", info.uptime);
    printf("Total RAM: %l KB\n", info.totalram/1024);
    printf("Free RAM: %l KB\n", info.freeram/1024);
    printf("Number of processes: %d\n", info.procs);

    exit(0);
}