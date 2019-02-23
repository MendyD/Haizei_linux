#!/bin/bash
User=`logname`
Pts=`who am i|awk "{print $1}"`
Time=`date +{%a}`
echo "${User} ${Pts}"
