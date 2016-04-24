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
OBJS_DECIMATOR=$(OBJS) sdr-decimator/benchmark_timetest.o sdr-decimator/decimator_10.o

TARGET=sdr-mixer sdr-decimator_10

all: $(TARGET)

sdr-mixer: $(OBJS_MIXER)
	$(CC) $(OBJS_MIXER) $(LDFLAGS) -o benchmark-$@

sdr-decimator_10: $(OBJS_DECIMATOR)
	$(CC) $(OBJS_DECIMATOR) $(LDFLAGS) -o benchmark-$@

clean:
	rm -f $(OBJS_MIXER) $(OBJS_DECIMATOR)
	@for i in $(TARGET); do rm -f benchmark-$$i; done
