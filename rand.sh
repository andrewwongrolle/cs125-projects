#!/bin/bash

for i in {1..100}
do
	echo "Running trial $i"
	echo "Running trial $i" >> results.txt
	./random-3-SAT >> results.txt
done    

exit 0
