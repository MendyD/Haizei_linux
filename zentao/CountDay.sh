#!/bin/bash
for i in $(seq $1 $[$1+9])
do
    if [ $[$1%4] -eq 0 -a $[$1%100] -ne 0 ] || [ $[$1%400] -eq 0 ] 
    then
        day=$[$day + 366]
    else
        day=$[$day + 365]
    fi
done
echo $day
