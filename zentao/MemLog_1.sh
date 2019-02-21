#!/bin/bash
day=`date +%Y-%m-%d__%H:%M:%S`

total=`cat /proc/meminfo | head -n 1|cut -d ' ' -f 2- | tr -d ' a-zA-Z'`
total=`echo $[$total/2014]`

free=`cat /proc/meminfo | head -n 2 | tail -n 1|cut -d ' ' -f 2- | tr -d ' a-zA-Z'`
free=`echo $[$free/2014]`

#per=`echo "scale=2;$[$[$temp-$free]*100]/$temp" | bc`

echo $day "$total"M "$free"M 
#$per
