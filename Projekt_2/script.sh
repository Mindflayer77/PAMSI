#!/bin/bash

for ((i=0; i < 100000; ++i)) do
read line;
echo $line >> test.csv
done < Data.csv