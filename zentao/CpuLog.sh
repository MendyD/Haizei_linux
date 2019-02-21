#!/bin/bash
a=`date +"%Y-%m-%d__%H:%M:%S"`
b=`cat /proc/loadavg | cut -d " " -f 1-3`
temp=`cat /sys/class/thermal/thermal_zone0/temp`
temp=`echo "scale=2;$temp/1000" | bc`

eval `cat /proc/stat | head -n 1 | awk -v sum1=0 -v idel1=0 '{printf("sum1=%d; idel1=%d",$2+$3+$4+$5+$6+$7+$8, $5)}'`

sleep 0.5

eval `cat /proc/stat | head -n 1 | awk -v sum2=0 -v idel2=0 '{printf("sum2=%d; idel2=%d",$2+$3+$4+$5+$6+$7+$8, $5)}'`

CpuUserPerc=`echo "scale=4;(1-($idel2-$idel1)/($sum2-$sum1))*100" | bc`
CpuUserPerc=`printf "%.2f\n" "$CpuUserPerc"`

echo $a $b $CpuUserPerc  $temp"℃"
