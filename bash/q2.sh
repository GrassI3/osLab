#!/bin/bash
echo "Enter Number"
read num
sqRoot=$(echo "scale=2; sqrt($num)" | bc -l )
echo ${sqRoot}
