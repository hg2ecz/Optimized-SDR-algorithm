# Optimized-SDR-algorithm
Software Defined Radio algorithm - Optimized for ARM processor

I interested for wide band SDR, and the first problem: what sample speed enough the resources?
The first block of wide band SDR: mixer with internal oscillator (sdr-mixer/) and the decimator with low pass filter (sdr-decimator/).

The next block work with output data of decimator, also fewer data, fewer resources.

I tested the algorythm (mixer+osc  and decimator). The results:

Odroid-C1 : 1,5 GHz ARM Cortex A5 : 50 Msps and 35 Msps
Raspberry3: 1,2 GHz ARM Cortex A53: 48 Msps and 52 Msps (32 bit Linux)
3,4 GHz i7-2600: 380 Msps and 370 Msps

These processors have multi-core, so one core can you run the mixer, the other core can you run the decimator and other can you run the next signal processing functions (demodulator, ...).
