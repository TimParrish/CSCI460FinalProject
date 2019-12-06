# CSCI460 Final Project - Process Scheduling Analysis

* CSCI 460 
* 12/06/2019
* Rial Johnson, Rusty Clayton, Tim Parrish

**There are two ways to run the program:**

##### Without arguments
`./Scheduling

##### With arguments
`./Scheduling 1000 10 4 1
When running with arguments, the first argument is k (the time interval during which processes may arrive). The second is the number of processes, the third is the time quanta for the Round Robin algorithm, and the fourth is a flag. A 0 for the fourth argument will result in one run of the program with a single d value and results printed to the screen. Anything else in the final argument will run the simulation many times for many d values and output to a `results.csv` file.
