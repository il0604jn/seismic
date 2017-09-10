#!/bin/bash
f1=test.sac.cut
f2=test.sac.cut
g++ crosscor_sac.cpp -o crosscor_sac

t1=$(date +%s)
./crosscor_sac $f1 $f2 > cc1.txt
t2=$(date +%s)
echo $t1 $t2 | awk '{print "binary:",$2-$1}'


t1=$(date +%s)
sac2asc $f1 > $f1.ascii
sac2asc $f2 > $f2.ascii
crosscor $f1.ascii $f2.ascii cc2.txt
t2=$(date +%s)
echo $t1 $t2 | awk '{print "ascii:",$2-$1}'
