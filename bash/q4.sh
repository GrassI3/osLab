#!/bin/bash
echo "Enter Principal amount:"
read P
echo "Enter Rate of interest:"
read R
echo "Enter Time in years:"
read T
SI=$(echo "scale=2; ($P*$R*$T)/100" | bc -l)
echo "Simple Interest = $SI Rs."
