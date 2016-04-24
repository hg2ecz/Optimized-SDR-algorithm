#include <stdio.h>
#include "benchmark_timetest.h"

#include <time.h>
void proc_cpu_usage_clock(int argc, char **argv) {
    clock_t cstart, cend;
    unsigned long usec;

    cstart=clock();
    timetest(argc, argv);
    cend=clock();

    usec = cend - cstart;
    printf("process   cpu  usage: %11.6f msec\n", usec/1000.);
}


#include <time.h>
void proc_cpu_usage_gettime(int argc, char **argv) {
    struct timespec gstart, gend;
    unsigned long long nsec;

    // cat /sys/devices/system/clocksource/clocksource0/current_clocksource
    // good:
    //    x86: tsc
    //    arm: arch_sys_counter (ARM Cortex A53)
    // else the real resolution is microsec only (ARM Cortex A5)
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart);
    timetest(argc, argv);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);

    nsec = 1000*1000*1000*(gend.tv_sec - gstart.tv_sec) + gend.tv_nsec - gstart.tv_nsec;
    printf("process   cpu  usage: %11.6f msec (very good if CPU has internal clock counter)\n", nsec/1000./1000.);
}

#include <sys/time.h>
void proc_elapsed_time(int argc, char **argv) {
    struct timeval tstart, tend;
    unsigned long usec;

    gettimeofday(&tstart, NULL);
    timetest(argc, argv);
    gettimeofday(&tend, NULL);

    usec = 1000*1000*(tend.tv_sec - tstart.tv_sec) + tend.tv_usec - tstart.tv_usec;
    printf("process elapsed time: %11.6f msec\n", usec/1000.);
}

#include <sys/resource.h>
void proc_rusage(int argc, char **argv) {
    struct rusage rstart, rend;
    unsigned long usec, sys_usec;

    getrusage(RUSAGE_SELF, &rstart);
    timetest(argc, argv);
    getrusage(RUSAGE_SELF, &rend);

    usec = 1000*1000*(rend.ru_utime.tv_sec - rstart.ru_utime.tv_sec) + rend.ru_utime.tv_usec - rstart.ru_utime.tv_usec;
    sys_usec = 1000*1000*(rend.ru_stime.tv_sec - rstart.ru_stime.tv_sec) + rend.ru_stime.tv_usec - rstart.ru_stime.tv_usec;
    // quantum: 10 msec - why?
    printf("process  user   time: %11.6f msec (sys time: %5.4f msec)\n", usec/1000., sys_usec/1000.);
}

// ----- MAIN -----

void print_usage(int argc, char **argv) {
    timetest(argc, argv);
    proc_cpu_usage_clock(argc, argv);
    proc_cpu_usage_gettime(argc, argv);
    proc_elapsed_time(argc, argv);
    proc_rusage(argc, argv);
    printf("\n");
}

int main(int argc, char **argv) {
    timetest_setup(argc, argv);
    print_usage(argc, argv);
    print_usage(argc, argv);
    print_usage(argc, argv);
    return 0;
}