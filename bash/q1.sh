#!/bin/bash
echo "Enter Number Of Rows:"
read rows
echo "Enter Number Of Columns:"
read cols
declare -A matrix

echo "Enter The Elements"
for ((i=0; i<rows; i++))
do
    	for ((j=0; j<cols; j++))
	do
        	read matrix[$i,$j]
    	done
done

echo "Original Matrix"
for ((i=0; i<rows; i++))
do
        for ((j=0; j<cols; j++))
        do
                echo -n ${matrix[$i,$j]} ""
        done
	echo
done

echo "Transpose Matrix"
for ((i=0; i<cols; i++))
do
        for ((j=0; j<rows; j++))
        do
                echo -n ${matrix[$j,$i]} ""
        done
        echo
done
