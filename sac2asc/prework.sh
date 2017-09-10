#!/bin/bash
cp ./raw/* ./
./chnhdr.sh
rm *.H??

#instrumental remove
sac<<EOF
r *SAC
rtr
rmean
w over
q
EOF
ls *.SAC >saclist
