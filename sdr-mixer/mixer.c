#include <math.h>
#include <string.h>
#include "mixer.h"

void mixer_oscgen(struct _local_osc *local_osc, double mixfreq, int samplerate) {
    double radian = -2*M_PI*mixfreq/samplerate;
    local_osc->vfo_state.cos=1.;
    local_osc->vfo_state.sin=0;
    local_osc->sin_cos_phase.cos = cos(radian);
    local_osc->sin_cos_phase.sin = sin(radian);
}

int mixer(struct _complexf *output, const struct _complexf *input, struct _local_osc *local_osc) {
    int i;
    struct _sin_cos sin_cos_phase = local_osc->sin_cos_phase;
    if (sin_cos_phase.sin != 0) {
	struct _sin_cos vfo_state = local_osc->vfo_state;
	for(i=0; i < BUFSIZE; i++) {  // mixer func
	    struct _sin_cos vfo_state_new;
	    output[i].i = input[i].i * (float)vfo_state.cos - input[i].q * (float)vfo_state.sin;
	    output[i].q = input[i].q * (float)vfo_state.cos + input[i].i * (float)vfo_state.sin;
	    vfo_state_new.cos = vfo_state.cos * sin_cos_phase.cos - vfo_state.sin * sin_cos_phase.sin;
	    vfo_state_new.sin = vfo_state.sin * sin_cos_phase.cos + vfo_state.cos * sin_cos_phase.sin;
	    vfo_state = vfo_state_new;
	}
	local_osc->vfo_state=vfo_state;
    } else { // if no freq --> simple copy
	memcpy(output, input, BUFSIZE*sizeof(struct _complexf));
    }
    return 0;
}
