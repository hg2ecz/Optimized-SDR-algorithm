CC=gcc
CFLAGS=-Wall -Ofast -funroll-loops -fopt-info

CFLAGS+=-mcpu=cortex-a5 -mfpu=neon-fp16
#CFLAGS+=-mcpu=cortex-a7 -mfpu=neon-vfpv4
#CFLAGS+=-mcpu=cortex-a8 -mfpu=neon
#CFLAGS+=-mcpu=cortex-a9 -mfpu=neon-fp16
#CFLAGS+=-mcpu=cortex-a15 -mfpu=neon-vfpv4
#CFLAGS+=-mcpu=cortex-a53 -mfpu=neon-fp-armv8

LDFLAGS=-lm -s
OBJS=benchmark.o

OBJS_MIXER=$(OBJS) sdr-mixer/benchmark_timetest.o sdr-mixer/mixer.o
OBJS_MIXER_COMPLEX=$(OBJS) sdr-mixer-complex/benchmark_timetest.o sdr-mixer-complex/mixer.o
OBJS_DECIMATOR=$(OBJS) sdr-decimator/benchmark_timetest.o sdr-decimator/decimator_10.o
OBJS_DECIMATOR_COMPLEX=$(OBJS) sdr-decimator-complex/benchmark_timetest.o sdr-decimator-complex/decimator_10.o


TARGET=sdr-mixer sdr-mixer-complex sdr-decimator_10 sdr-decimator_10-complex

all: $(TARGET)

sdr-mixer: $(OBJS_MIXER)
	$(CC) $(OBJS_MIXER) $(LDFLAGS) -o benchmark-$@

sdr-mixer-complex: $(OBJS_MIXER_COMPLEX)
	$(CC) $(OBJS_MIXER_COMPLEX) $(LDFLAGS) -o benchmark-$@

sdr-decimator_10: $(OBJS_DECIMATOR)
	$(CC) $(OBJS_DECIMATOR) $(LDFLAGS) -o benchmark-$@

sdr-decimator_10-complex: $(OBJS_DECIMATOR_COMPLEX)
	$(CC) $(OBJS_DECIMATOR_COMPLEX) $(LDFLAGS) -o benchmark-$@

clean:
	rm -f $(OBJS_MIXER) $(OBJS_MIXER_COMPLEX) $(OBJS_DECIMATOR) $(OBJS_DECIMATOR_COMPLEX)
	@for i in $(TARGET); do rm -f benchmark-$$i; done
