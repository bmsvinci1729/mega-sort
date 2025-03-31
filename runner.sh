#!/bin/bash

start_time=$(date +%s)  # Capture the start time

python3 chunks.py
g++ basic.cpp
./a.out
g++ -std=c++17 -pthread -o merge_100M merge.cpp
./merge_100M
rm a.out
rm merge_100M

end_time=$(date +%s)  # Capture the end time

execution_time=$((end_time - start_time))  # Calculate execution time
echo "Total execution time: $execution_time seconds"
