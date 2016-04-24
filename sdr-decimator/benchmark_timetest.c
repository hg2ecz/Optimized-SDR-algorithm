#include "../benchmark_timetest.h"
#include "decimator_10.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALLBUF (1000*1000)
struct _complexf allin[ALLBUF+BUFSIZE];
struct _complexf goutput[BUFSIZE];


void timetest_setup(int argc, char **argv) {
    int type;
    if (argc < 2) {
	printf("Please give one argument: 1 or 2\n");
	exit(-1);
    }
    type = atoi(argv[1]);
    if (type == 1) printf("Test1: Get %d element from input[i-remain]\n", BUFSIZE);
    else printf("Test2: Memmove & Get (%d-remain) element\n", BUFSIZE);
}


void timetest(int argc, char **argv) {
    int i=0, remain=0;
    struct _complexf in[BUFSIZE];
    int type = atoi(argv[1]);

    if (type == 1) { // faster, if you copy from buffer
	while (i < ALLBUF) {
	    memcpy(in, &allin[i-remain], BUFSIZE*sizeof(struct _complexf));
	    decimator_10(goutput, in, &remain);
	    i+=BUFSIZE-remain;
	}
    } else {
	while (i < ALLBUF) { // if you use read()
	    memmove(in, &in[BUFSIZE-remain], remain*sizeof(struct _complexf));
	    memcpy(in, &allin[i], (BUFSIZE-remain)*sizeof(struct _complexf)); // or read(BUFSIZE-remain)
	    decimator_10(goutput, in, &remain);
	    i+=BUFSIZE-remain;
	}
    }
}
