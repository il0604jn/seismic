#!/bin/bash
IFS=$'\n'
c1=ysjeon.stloc.lst
c2=stloc.20160630.lst

for line1 in $(cat $c1);do
	st1=$(echo $line1 | awk '{printf "%s",$1}')
#	la1=$(echo $line1 | awk '{printf "%s",$2}')
#	lo1=$(echo $line1 | awk '{printf "%s",$3}')
#	el1=$(echo $line1 | awk '{printf "%s",$4}')
	N="x"
	for line2 in $(cat $c2);do
		st2=$(echo $line2 | awk '{printf "%s",$1}')
#		la2=$(echo $line2 | awk '{printf "%s",$2}')
#		lo2=$(echo $line2 | awk '{printf "%s",$3}')
#		el2=$(echo $line2 | awk '{printf "%s",$4}')
		if [ "$st1" == "$st2" ];then
			N="o"
		fi
	done
	if [ "$N" == "x" ];then
		echo $line1
	fi
	
done 
