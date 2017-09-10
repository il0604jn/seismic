#!/bin/bash
n=100
b=$(date +%s)
for n in $(seq 1 $n);do
	sac2asc test.sac > test.sac.ascii
done
e=$(date +%s)
echo "$b $e" | awk '{print $2-$1}'
b=$(date +%s)
for n in $(seq 1 $n);do
	sac2asc_awk test.sac > test.sac.ascii
done
e=$(date +%s)
echo "$b $e" | awk '{print $2-$1}'
