#!/bin/bash

if [ $# -eq 0 ]; then
   exit
fi

declare -i i=$1

# declare -i $1
while [ $i -le ${2} ]; do
    j=$((100+${i}))
    dir="Chapter${j:1}"
    # mkdir "Chapter${i}"
    mkdir ${dir}
    ex="${dir}/exercises"
    mkdir ${ex}
    i=${i}+1;
done
