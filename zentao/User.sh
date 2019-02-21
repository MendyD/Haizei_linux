#!/bin/bash
day=`date +%Y-%m-%d__%H:%M:%S`

people=`awk -F: '$3>=200{print $1}' /etc/passwd | wc -l`

user_three=`last | grep -v wtmp | grep -v shutdown | grep -v boot| grep [a-zA-Z] | awk '{printf("%s\n", $1);}' | sort | uniq -c | sort -n -r | awk '{printf(",%s", $2);}' | cut -d "," -f 2-4`

root=`awk -F: '$3==1000{print $1}' /etc/passwd`

user=`w -h | awk '{printf(",%s_%s_%s"), $1, $3, $2}' | cut -c 2-`


echo $day $people [$user_three] [$root] [$user]
