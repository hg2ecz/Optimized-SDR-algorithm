# Optimized-SDR-algorithm
Software Defined Radio algorithm - Optimized for ARM processor

I interested for wide band SDR, and the first problem: what sample speed enough the resources?<br>
The first block of wide band SDR: mixer with internal oscillator (sdr-mixer/) and the decimator with low pass filter (sdr-decimator/).

In the directory '*-complex' are same C programs, but they use complex.h and GCC internal complex arithmetics.

The next block work with output data of decimator, also fewer data, fewer resources.

I tested the algorythm mixer+osc and (mixer with "float complex") and decimator in one core. The results:

<ul>
<li>Odroid-U3 : 1,7 GHz ARM Cortex A9 : 75 Msps (90 Msps) and 50 Msps per core</li>
<li>Odroid-C1 : 1,5 GHz ARM Cortex A5 : 50 Msps (58 Msps) and 35 Msps per core</li>
<li>Raspberry2: 0,9 GHz ARM Cortex A7 : 29 Msps and 25 Msps per core</li>
<li>Raspberry3: 1,2 GHz ARM Cortex A53: 48 Msps (74 Msps) and 52 Msps per core (32 bit Linux)</li>
<li>3,4 GHz i7-2600: 380 Msps and 370 Msps per core</li>
</ul>

My experience: -mcpu=cortex-a5 -mfpu=neon-fp16 given better result for Cortex A5 and also Cortex A7, A9, A53. Why?

Other historical single core architectures:
<ul>
<li>2,8 GHz Pentium4: 95 Msps and 61 Msps</li>
<li>0,7 GHz Raspberry Pi1: 11,7 Msps and 11,6 Msps</li>
</ul>


These processors (except historical architectures) have multi-core, so one core can you run the mixer, the other core can you run the decimator and other can you run the next signal processing functions (demodulator, ...).
