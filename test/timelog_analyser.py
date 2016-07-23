#!/usr/bin/python

import sys

i=0
ossz=0.
adat=[]
for sor in open(sys.argv[1], "r").readlines():
    m = sor.split()
    i+=1
    ossz += float(m[3])
    adat.append(float(m[3]))

atlag = ossz/i
szoras = 0.
for a in adat:
    szoras += (a - atlag)**2
szoras /= i

print "Average: %f, variance: %f"%(atlag, szoras)
