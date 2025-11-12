#!/bin/bash
echo "Enter Number"
read num
digits=$(echo "$num" | grep -o . | sort -n)
array=($digits)
len=${#array[*]}
echo "Second Min ="${array[1]}
echo "Second Max ="${array[$(($len - 2))]}
