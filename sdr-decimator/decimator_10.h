#define BUFSIZE 1000

struct _complexf {
    float i;
    float q;
};

int decimator_10(struct _complexf *output, const struct _complexf *input, int *remain);
