#!/bin/bash
function find_in_file(){
    for file in ` ls $1`; do if [ -d $1"/"$file ]; then ergodic $1"/"$file; fi; done;INIT_PATH=".";
    for i in `ergodic $INIT_PATH`; do for j in `cat $i |tr -c 'a-zA-Z' " "`; do echo $j >> ddd; done; done;
    if [[ -z $file ]]; then echo "yes"; else  echo "no"; fi

}

if [[ $1 =~ "." ]]
    then find_in_file;
else
    echo "no";
fi
