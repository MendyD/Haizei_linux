#!/bin/bash
a=`date +"%Y-%m-%d__%H:%M:%S"`
b=`cat /proc/loadavg | cut -d " " -f 1-3`
temp=`cat /sys/class/thermal/thermal_zone0/temp`
temp=`echo "scale=2;$temp/1000" | bc`
echo $a $b $temp
