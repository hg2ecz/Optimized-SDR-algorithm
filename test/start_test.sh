#!/bin/bash

LOG=mix.log; PRG=../benchmark-sdr-mixer; >$LOG; $PRG; for i in {0..50}; do $PRG | grep very >> $LOG; done
LOG=mix-complex.log; PRG=../benchmark-sdr-mixer-complex; >$LOG; $PRG; for i in {0..50}; do $PRG | grep very >> $LOG; done

LOG=dec1.log; PRG=../benchmark-sdr-decimator_10; >$LOG; $PRG 1; for i in {0..50}; do $PRG 1 | grep very >> $LOG; done
LOG=dec1-complex.log; PRG=../benchmark-sdr-decimator_10-complex; >$LOG; $PRG 1; for i in {0..50}; do $PRG 1 | grep very >> $LOG; done

echo "-- Mixer --"
./timelog_analyser.py mix.log
echo "-- Mixer with complex.h --"
./timelog_analyser.py mix-complex.log
echo
echo "-- Decimator --"
./timelog_analyser.py dec1.log
echo "-- Decimator with complex.h --"
./timelog_analyser.py dec1-complex.log
