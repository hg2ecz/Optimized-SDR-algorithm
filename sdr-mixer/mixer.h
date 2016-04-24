#define BUFSIZE 1000

struct _complexf {
    float i;
    float q;
};

struct _sin_cos {
    double sin;
    double cos;
};

struct _local_osc {
    struct _sin_cos vfo_state;
    struct _sin_cos sin_cos_phase;
};

void mixer_oscgen(struct _local_osc *local_osc, double mixfreq, int samplerate);
int mixer(struct _complexf *output, const struct _complexf *input, struct _local_osc *local_osc);
