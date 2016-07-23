#include <math.h>
#include <string.h>
#include "mixer.h"

void mixer_oscgen(struct _local_osc *local_osc, double mixfreq, int samplerate) {
    double radian = -2*M_PI*mixfreq/samplerate;
    local_osc->vfo_state=1. + 0*I;
    local_osc->sin_cos_phase = cos(radian) + sin(radian)*I;
}

int mixer(float complex *output, const float complex *input, struct _local_osc *local_osc) {
    int i;
    double complex sin_cos_phase = local_osc->sin_cos_phase;
    if (cimag(sin_cos_phase)) {
	double complex vfo_state = local_osc->vfo_state;
	for(i=0; i < BUFSIZE; i++) {  // mixer func
	    output[i] *= (float complex)vfo_state;
	    vfo_state *= sin_cos_phase;
	}
	local_osc->vfo_state=vfo_state;
    } else { // if no freq --> simple copy
	memcpy(output, input, BUFSIZE*sizeof(float complex));
    }
    return 0;
}
