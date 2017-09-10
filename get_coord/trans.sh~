#!/bin/bash
#ref_fname file format
#x,y: digitized
#lo, la: real
#no space
# x1,y1;lo1,la1
# x2,y2;lo2,la2
fname=$1
ref_fname=$2
outname=$1.trans
x1=$(cat $ref_fname | head -n 1 | awk -F";" '{print $1}' | awk -F"," '{print $1}')
y1=$(cat $ref_fname | head -n 1 | awk -F";" '{print $1}' | awk -F"," '{print $2}')
lo1=$(cat $ref_fname | head -n 1 | awk -F";" '{print $2}' | awk -F"," '{print $1}')
la1=$(cat $ref_fname | head -n 1 | awk -F";" '{print $2}' | awk -F"," '{print $2}')
x2=$(cat $ref_fname | tail -n 1 | awk -F";" '{print $1}' | awk -F"," '{print $1}')
y2=$(cat $ref_fname | tail -n 1 | awk -F";" '{print $1}' | awk -F"," '{print $2}')
lo2=$(cat $ref_fname | tail -n 1 | awk -F";" '{print $2}' | awk -F"," '{print $1}')
la2=$(cat $ref_fname | tail -n 1 | awk -F";" '{print $2}' | awk -F"," '{print $2}')

#echo $x1, $y1, $x2, $y2
#echo $lo1, $la1, $lo2, $la2

Dx=$(echo "scale=12; $x1-$x2" | bc)
xa=$(echo "scale=12; ($lo1-$lo2)/$Dx" | bc)
xb=$(echo "scale=12; ($x1*$lo2-$x2*$lo1)/$Dx" | bc)

Dy=$(echo "scale=12; $y1-$y2" | bc)
ya=$(echo "scale=12; ($la1-$la2)/$Dy" | bc)
yb=$(echo "scale=12; ($y1*$la2-$y2*$la1)/$Dy" | bc)

#echo "scale=12; $xa*$x1+$xb" | bc
#echo "scale=12; $xa*$x2+$xb" | bc
#echo "scale=12; $ya*$y1+$yb" | bc
#echo "scale=12; $ya*$y2+$yb" | bc

cat $fname | awk -v xa=$xa -v xb=$xb -v ya=$ya -v yb=$yb '{printf "%.12f %.12f\n", xa*$1+xb, ya*$2+yb}' > $outname
