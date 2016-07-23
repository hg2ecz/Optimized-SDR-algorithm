#include <complex.h>
#define BUFSIZE 1000

struct _local_osc {
    double complex vfo_state;
    double complex sin_cos_phase;
};

void mixer_oscgen(struct _local_osc *local_osc, double mixfreq, int samplerate);
int mixer(float complex *output, const float complex *input, struct _local_osc *local_osc);
