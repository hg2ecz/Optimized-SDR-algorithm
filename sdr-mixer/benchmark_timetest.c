#include "../benchmark_timetest.h"
#include "mixer.h"

struct _complexf goutput[BUFSIZE];
struct _complexf ginput[BUFSIZE];

void timetest_setup(int argc, char **argv) {
}

void timetest(int argc, char **argv) {
    int i;
    struct _local_osc glocal_osc;
    mixer_oscgen(&glocal_osc, 1e6, 2.4e6);
    for (i=0; i<1000; i++) mixer(goutput, ginput, &glocal_osc);
}
