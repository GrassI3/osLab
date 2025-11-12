#!/bin/bash
echo "Enter Temp in Celsius"
read tmp
farh=$(echo "scale=2; (($tmp*9/5)+32)" | bc -l)
echo "Temp in Farhenheit = "${farh}
