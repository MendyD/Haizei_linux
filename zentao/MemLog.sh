#!/bin/bash
date=`date +%Y-%m-%d__%H:%M:%S`

eval $(free -m | tail -n 2 | head -n 1 | awk -v total=0 -v used=0 '{printf("total=%d used=%d\n", $2,$3)}')



MemPers=`echo "scale=1;${used}*100/${total}" | bc`

DyAver=$1
if [[ x"DyAver" == x ]];then
    exit 1
fi


Ave=`echo "scale=1;${MemPers}*0.7+${DyAver}*0.3" | bc`



echo $date ${total}M $[$total-$used]M ${MemPers}% ${Ave}%

