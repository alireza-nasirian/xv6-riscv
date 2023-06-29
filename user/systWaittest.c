#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void printReport(long cpuburst_time, long turnaround_time, long waitingTimeFirst);

void printReportSecond(long cpuburst_time2, long turnaround_time2, long waitingTimeSecond);

int testScheduler();

int checkScheduler();

void checkSchedulerSecond(int p_id);

int main(void)
{
    return testScheduler();
}

int testScheduler() {
    set_scheduler(FCFS);
    int p = checkScheduler();

    if (p == 0)
    {
        return 0;
    }
    int p_id = 0;
    set_scheduler(Round_Robin);
    checkSchedulerSecond(p_id);

    return 0;
}

void checkSchedulerSecond(int p_id) {
    struct proctime proctWait2[32];
    for (int i = 0; i < 32; i++)
    {
        p_id = fork();
        if (p_id == 0)
        {

            long arrayOne[100000000];
            long arrayTwo[100000000];

            for (int i = 0; i < 100000000; i++)
            {
                arrayOne[i] = 2;
            }

            for (int i = 0; i < 100000000; i++)
            {
                arrayTwo[i] = 1;
            }

            long y = 0;

            for (int i = 0; i < 100000000; i++)
            {
                y += arrayOne[i] + arrayTwo[i];
            }
            sleep(50);
            break;
        }
    }

    if (p_id != 0)
    {
        long cpuburst_time2 = 0;
        long turnaround_time2 = 0;
        long waitingTimeSecond = 0;
        int exitp;

        for (int i = 0; i < 32; i++)
        {
            tWait(&exitp, &proctWait2[i]);
            waitingTimeSecond += proctWait2[i].waitingTimeFirst;
            turnaround_time2 += proctWait2[i].turnaround_time;
            cpuburst_time2 += proctWait2[i].cpuburst_time;
        }

        printReportSecond(cpuburst_time2, turnaround_time2, waitingTimeSecond);
    }
}

int checkScheduler() {
    int p;
    struct proctime proctWait[32];
    for (int i = 0; i < 32; i++)
    {
        p = fork();
        if (p == 0)
        {
            long arrayOne[100000000];
            long arrayTwo[100000000];
            for (int i = 0; i < 100000000; i++)
            {
                arrayOne[i] = 2;
            }
            for (int i = 0; i < 100000000; i++)
            {
                arrayTwo[i] = 1;
            }
            long y = 0;
            for (int i = 0; i < 100000000; i++)
            {
                y += arrayOne[i] + arrayTwo[i];
            }
            sleep(50);
            break;
        }
    }
    if (p != 0)
    {
        long cpuburst_time = 0;
        long turnaround_time = 0;
        long waitingTimeFirst = 0;
        int exitp;
        for (int i = 0; i < 32; i++)
        {
            tWait(&exitp, &proctWait[i]);
            cpuburst_time += proctWait[i].cpuburst_time;
            turnaround_time += proctWait[i].turnaround_time;
            waitingTimeFirst += proctWait[i].waitingTimeFirst;
        }

        printReport(cpuburst_time, turnaround_time, waitingTimeFirst);
    }
    return p;
}

void printReportSecond(long cpuburst_time2, long turnaround_time2, long waitingTimeSecond) {
    printf("Round_Robin cpuburst_time:   %d\n", cpuburst_time2 / 32);
    printf("Round_Robin turnaround_time: %d\n", turnaround_time2 / 32);
    printf("Round_Robin waitingTimeFirst:  %d\n", waitingTimeSecond / 32);
}

void printReport(long cpuburst_time, long turnaround_time, long waitingTimeFirst) {
    printf("FCFS cpuburst_time:   %d\n", cpuburst_time / 32);
    printf("FCFS turnaround_time: %d\n", (long)turnaround_time / 32);
    printf("FCFS waitingTimeFirst:  %d\n", (long)waitingTimeFirst / 32);
}
