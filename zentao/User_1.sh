#!/bin/bash
day=`date +%Y-%m-%d__%H:%M:%S`
people=`awk -F: '$3>=200{print $1}' /etc/passwd | wc -l`
root=`awk -F: '$3==1000{print $1}' /etc/passwd`
user_demo=`last | awk -F" " '{print ","$1"_"$2"_"$3}' | grep -v 'wtmp' | grep -v '__' `


for i in $a
do
    i=$i
done


echo $day $people [$root] [$user_demo]
