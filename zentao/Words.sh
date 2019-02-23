#!/bin/bash

length=(0 0 0)
String=(0 0 0)
File=(0 0 0)

filter_conf=./filter.conf

function filter() {
	file_type=`basename $1 | tr [.] "\n" | tail -1` 
	grep -w ${file_type}  ${filter_conf}
}

function find_in_file() {
	file $1 | grep text 2>&1 >/dev/null
	if [[ $? -ne 0 ]]; then
		return
	fi
	words=`cat $1 | tr -c [a-z][A-Z][0-9][_] "\n"`
	for i in $words; do
		temp=${#i}
		if [[ $temp -ge ${length[0]} ]]; then
			length[2]=${length[1]}
			String[2]=${String[1]}
			File[2]=${File[1]}
			length[1]=${length[0]}
			String[1]=${String[0]}
			File[1]=${File[0]}
			length[0]=$temp
			String[0]=$i
			File[0]=$1
		elif [[ $temp -ge ${length[1]} ]]; then
			length[2]=${length[1]}
			String[2]=${String[1]}
			File[2]=${File[1]}
			length[1]=$temp
			String[1]=$i
			File[1]=$1
		elif [[ $temp -ge ${length[2]} ]]; then
			length[2]=$temp
			String[2]=$i
			File[2]=$1
		fi
	done
}

function find_in_dir() {
	for i in `ls -A $1`; do
		if [[ -f $1/$i ]]; then
			filter $1/$i
			if [[ $? -eq 0 ]]; then
				continue
			fi
			find_in_file $1/$i
		elif [[ -d $1/$i ]]; then
			find_in_dir $1/$i
		fi
	done
}

if [[ $# -ne 1 ]]; then
	echo "Usage: Words.sh file_or_dir!"
	exit
fi

if [[ -d $1 ]]; then
	find_in_dir $1
elif [[ -f $1 ]]; then
	find_in_file $1
else
	echo "Error in $1!"
	exit
fi

echo "1 ${String[0]} ${length[0]} ${File[0]}:`grep -w ${String[0]} -n ${File[0]} | cut -d ":" -f 1`"
echo "2 ${String[1]} ${length[1]} ${File[1]}:`grep -w ${String[1]} -n ${File[1]} | cut -d ":" -f 1`"
echo "3 ${String[2]} ${length[2]} ${File[2]}:`grep -w ${String[2]} -n ${File[2]} | cut -d ":" -f 1`"

