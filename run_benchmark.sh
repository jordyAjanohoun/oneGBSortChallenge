#!/bin/bash

# this script runs the benchmarking

killall sort.benchmark

if [ -d "build" ]; then
	cd build
	make
else
	./run_correctness_test.sh
	cd build
fi 


for nb_procs in 1 2 4
do      
	if [[ $nb_procs -eq 1 ]]
	then
		mpirun -n 1 ./sort.benchmark
	else
		mpirun -n ${nb_procs} --map-by node ./sort.benchmark --benchmark_filter=your_sort
	fi
done