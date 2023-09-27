#!/bin/bash
for ((nvectores=5;nvectores<=20;nvectores++))
do
  echo -e "\n  - Para $nvectores vectores:"
   ./mezcla 10 $nvectores >> mezcla.dat
done