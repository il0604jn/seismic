#!/bin/bash
IFS=$'\n'
raw=stinfo.necis.20151007.lst.raw
out1=stinfo.necis.20151007.lst
out2=stloc.necis.20151007.lst

cat $raw | awk '{
  n=$1
  nwk=$2
  stnm=$3

  if(substr($4,1,2)=="19" || substr($4,1,2)=="20"){
    begin=$4
    end=$5
    la=$6
    lo=$7
    el_km=$8
  }
  else if(substr($5,1,2)=="19" || substr($5,1,2)=="20"){
    begin=$5
    end=$6
    la=$7
    lo=$8
    el_km=$9    
    }
  else if(substr($6,1,2)=="19" || substr($6,1,2)=="20"){
    begin=$6
    end=$7
    la=$8
    lo=$9
    el_km=$10
  }
  el_m=el_km*1000
  
  if(la<0.01 && la>-0.01) la="-"
  if(lo<0.01 && lo>-0.01) lo="-"
  if(el_km<0.0001) el_km="-"
  if(el_m<0.0001) el_m="-"
  printf "%3d %6s %4s %10s %10s %9s %9s %6s\n", n,nwk,stnm,begin,end,la,lo,el_m
}' > $out1

cat $out1 | awk '{if($6!="-" && $7!="-") printf "%5s %10.4f %10.4f %7.1f\n", $3, $6, $7, $8}' > $out2
