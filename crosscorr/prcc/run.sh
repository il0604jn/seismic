#!/bin/bash
b=$(date +%s)
crosscor cos.txt sin.txt out.txt
e=$(date +%s)
echo $b $e | awk '{print $2-$1}'
