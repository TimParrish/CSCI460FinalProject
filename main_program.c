// CSCI-460: Operating Systems
// Fall 2019
// Team Members:
// Rusty Clayton
// Rial Johnson
// Tim Parrish

static int k = 20; // interval in which processes may arrive
static int numProcesses = 5;
static int numPriorities = 10;

struct process {
	int id; // pi
	int active; // 0 is inactive, 1 is active
	int arrivalTime; // Ai
	int cpuTime; // Ti
	int remainingCpuTime; // Ri
	int turnaroundTime; // TTi
	int priority; // draw from uniform to get these values
};

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "improved_round_robin.c"
#include "highest_response_ratio_next.c"
#include "improved_multilevel_feedback_queue.c"
#include "preemptive_priority_based.c"
#include "first_in_first_out.c"
#include "shortest_job_first.c"
#include "shortest_remaining_time.c"


// runs the simulation for a given set of processes and a particular scheduling algorithm
double simulation(struct process processes[numProcesses], char algorithm[]) {

	int anyProcessRemains =  1;
	int currentProcessIndex = -1;
	int time = 0; // simulation time (t)
	int hrrnIndex = -1;
	// run through the simulation
	while (anyProcessRemains == 1) {

		// set active flags for each process
		for (int i = 0; i < numProcesses; i++) {

			if (processes[i].arrivalTime == time) {
				processes[i].active = 1;
			}

		}

		int i = -1; // initialize error process if algorithm name isn't valid

		// pick a process to run depending on the scheduling algorithm chosen
		if (strcmp("FIFO", algorithm) == 0) {

			i = fifo(processes); // run FIFO to get next process

		} else if (strcmp("SJF", algorithm) == 0) {

			// run SJF to get next process, keep track of current process because no pre-emption
			currentProcessIndex = sjf(processes, currentProcessIndex);
			i = currentProcessIndex;

		} else if (strcmp("SRT", algorithm) == 0) {

			i = srt(processes);

		} else if (strcmp("PPB", algorithm) == 0) {

			i = preemptive_priority_based(processes);

		} 
		else if (strcmp("HRRN", algorithm) == 0){
			// run HRRN to get next process, keep track of current process because no pre-emption
			currentProcessIndex = highest_response_ratio_next(processes, time, currentProcessIndex, hrrnIndex);
			i = currentProcessIndex;
			hrrnIndex = i;
			
		else if (strcmp("LRRN", algorithm) == 0){
			// run HRRN to get next process, keep track of current process because no pre-emption
			currentProcessIndex = lowest_response_ratio_next(processes, time, currentProcessIndex, hrrnIndex);
			i = currentProcessIndex;
			hrrnIndex = i;
			
		}else {
			printf("Not a known algorithm.");
		}


		if (i == -1) {
			// no valid process to run, do nothing
		} else {

			printf("\n\nProcess #%d was chosen to run for %s!\n", i, algorithm);
			printf("Simulation time is: %d\n", time);

			processes[i].remainingCpuTime = processes[i].remainingCpuTime - 1; // decrement remaining time for this process if it ran

			printf("Remaining time for process %d is: %d\n", i, processes[i].remainingCpuTime);

			// if the process has finished running on the cpu
			if (processes[i].remainingCpuTime == 0) {
				hrrnIndex = -1;
				processes[i].active = 0; // deactivate the process
				processes[i].turnaroundTime = time - processes[i].arrivalTime; // calculate turnaround time for this process
			}

		}

		time++; // increment time whether a process was ready to run or not

		anyProcessRemains = 0; // initialize flag to 0 before checking if there are any processes left

		// check if any process still needs to run
		for (int i = 0; i < numProcesses; i++) {

			if (processes[i].remainingCpuTime > 0) {
				anyProcessRemains = 1;
			}
		}
	}

	double averageTurnaroundTime = 0;
	int totalTurnaroundTime = 0;

	// add up all the turnaround times for each process
	for (int i = 0; i < numProcesses; i++) {
		totalTurnaroundTime += processes[i].turnaroundTime;
	}

	averageTurnaroundTime = totalTurnaroundTime / numProcesses; // compute average turnaround time

	return averageTurnaroundTime;

}

int main(int argc, char * argv[]) {

	srand(time(NULL));

	int fullPlot = 0;

	// set variables with command line arguments
	if (argc == 4) {
        k = atoi(argv[1]); // interval in which processes may arrive
        numProcesses = atoi(argv[2]);
		fullPlot = atoi(argv[3]);
    }

	struct process processes[numProcesses]; // array of all processes

	// initialize a random number generator
	gsl_rng_env_setup();
    const gsl_rng_type * T = gsl_rng_default;
    gsl_rng * r = gsl_rng_alloc (T);
	gsl_rng_set(r, rand());

	int d = 7;// mean for guassian distribution
	double v = 0.5 * d; // standard deviation is always 1/2 of mean for simplicity;

	// user can choose to get results for a single value of d (and print to screen) or plot a whole distribution
	// of d values and output to .csv
	if (fullPlot == 0) {

		// intialize values of all processes
		for (int i = 0; i < numProcesses; i++) {

			processes[i].id = i; // initialize a sequential id
			processes[i].active = 0; // initialize that a process is inactive at first
			processes[i].arrivalTime = gsl_ran_flat(r, 0, k); // get random integer (0-k) from a uniform distribution

			// get a random int from the normal distribution with mean d and standard deviation v
			int randomNormal = gsl_ran_gaussian(r, v); // returns ints around mean = 0
			randomNormal += d; // adds the mean to get correct gaussian int with mean = d and sd = v
			// set all negative or 0 values to 1
			if (randomNormal <= 0) {
				randomNormal = 1;
			}

			processes[i].cpuTime = randomNormal; // get random integer from the normal distribution
			processes[i].remainingCpuTime = processes[i].cpuTime; // initialize Ri = Ti
			processes[i].priority = gsl_ran_flat(r, 0, numPriorities); // get random integer (0-k) from a uniform distribution


			printf("Process #%d:\nAi: %d\nTi: %d\nRi: %d\nPriority: %d\n", processes[i].id, processes[i].arrivalTime, processes[i].cpuTime, processes[i].remainingCpuTime, processes[i].priority);

		}


		// copy all values of processes so we can recover from direct manipulation
		struct process processCopy[numProcesses];
		for (int i = 0; i < numProcesses; i++) {
			processCopy[i] = processes[i];
		}

		double fifoTurnaroundTime = 0;
		double sjfTurnaroundTime = 0;
		double srtTurnaroundTime = 0;
		double ppbTurnaroundTime = 0;
		double hrrnTurnaroundTime = 0;	
		double lrrnTurnaroundTime = 0;	


		// run our simulation with FIFO
		printf("---------------------- Starting FIFO -----------------------");
		fifoTurnaroundTime = simulation(processes, "FIFO");

		// copy all values from processCopy to restore our original processes
		for (int i = 0; i < numProcesses; i++) {
			processes[i] = processCopy[i];
		}

		// run our simulation with SJF
		printf("----------------------- Starting SJF -----------------------");
		sjfTurnaroundTime = simulation(processes, "SJF"); // run our simulation

		// copy all values from processCopy to restore our original processes
		for (int i = 0; i < numProcesses; i++) {
			processes[i] = processCopy[i];
		}

		// run our simulation with SRT
		printf("----------------------- Starting SRT -----------------------");
		srtTurnaroundTime = simulation(processes, "SRT"); // run our simulation
		
		// copy all values from processCopy to restore our original processes
		for (int i = 0; i < numProcesses; i++) {
			processes[i] = processCopy[i];
		}

		// run our simulation with Preemptive Priority Based
		printf("------------ Starting Preemptive Priority Based ------------");
		ppbTurnaroundTime = simulation(processes, "PPB"); // run our simulation
		
		// copy all values from processCopy to restore our original processes
		for (int i = 0; i < numProcesses; i++) {
			processes[i] = processCopy[i];
		}
		
		// run our simulation with HRRN
		printf("--------------- Starting HRRN ---------------");
		hrrnTurnaroundTime = simulation(processes, "HRRN"); // run our simulation
		
		// copy all values from processCopy to restore our original processes
		for (int i = 0; i < numProcesses; i++) {
			processes[i] = processCopy[i];
		}
		
		// run our simulation with HRRN
		printf("--------------- Starting LRRN ---------------");
		lrrnTurnaroundTime = simulation(processes, "LRRN"); // run our simulation

		printf("\nAverage Turnaround Time for FIFO was: %lf\n", fifoTurnaroundTime);
		printf("\nAverage Turnaround Time for SJF was: %lf\n", sjfTurnaroundTime);
		printf("\nAverage Turnaround Time for SRT was: %lf\n", srtTurnaroundTime);
		printf("\nAverage Turnaround Time for PPB was: %lf\n", ppbTurnaroundTime);
		printf("\nAverage Turnaround Time for HRRN was: %lf\n", hrrnTurnaroundTime);
		printf("\nAverage Turnaround Time for LRRN was: %lf\n", lrrnTurnaroundTime);


	} else {

		// csv file initialization
		FILE *fp;
		fp = fopen("results.csv","w+");

		// print header of csv
		fprintf(fp, "Mean (d),Standard Deviation(v),FIFO,SJF,SRT\n");

		// iterate over many values of d to create plots
		for (d = 1; d < k  * 5; d++) {
			v = 0.5 * d; // standard deviation is always 1/2 of mean for simplicity

				// intialize values of all processes
			for (int i = 0; i < numProcesses; i++) {

				processes[i].id = i; // initialize a sequential id
				processes[i].active = 0; // initialize that a process is inactive at first
				processes[i].arrivalTime = gsl_ran_flat(r, 0, k); // get random integer (0-k) from a uniform distribution

				// get a random int from the normal distribution with mean d and standard deviation v
				int randomNormal = gsl_ran_gaussian(r, v); // returns ints around mean = 0
				randomNormal += d; // adds the mean to get correct gaussian int with mean = d and sd = v
				// set all negative or 0 values to 1
				if (randomNormal <= 0) {
					randomNormal = 1;
				}

				processes[i].cpuTime = randomNormal; // get random integer from the normal distribution
				processes[i].remainingCpuTime = processes[i].cpuTime; // initialize Ri = Ti


				printf("Process #%d:\nAi: %d\nTi: %d\nRi: %d\n", processes[i].id, processes[i].arrivalTime, processes[i].cpuTime, processes[i].remainingCpuTime);

			}


			// copy all values of processes so we can recover from direct manipulation
			struct process processCopy[numProcesses];
			for (int i = 0; i < numProcesses; i++) {
				processCopy[i] = processes[i];
			}

			double fifoTurnaroundTime = 0;
			double sjfTurnaroundTime = 0;
			double srtTurnaroundTime = 0;

			// run our simulation with FIFO
			printf("--------------- Starting FIFO ---------------");
			fifoTurnaroundTime = simulation(processes, "FIFO");

			// copy all values from processCopy to restore our original processes
			for (int i = 0; i < numProcesses; i++) {
				processes[i] = processCopy[i];
			}

			// run our simulation with SJF
			printf("--------------- Starting SJF ---------------");
			sjfTurnaroundTime = simulation(processes, "SJF"); // run our simulation

			// copy all values from processCopy to restore our original processes
			for (int i = 0; i < numProcesses; i++) {
				processes[i] = processCopy[i];
			}

			// run our simulation with SRT
			printf("--------------- Starting SRT ---------------");
			srtTurnaroundTime = simulation(processes, "SRT"); // run our simulation

			fprintf(fp, "%d,%lf,%lf,%lf,%lf\n", d, v, (d / fifoTurnaroundTime), (d / sjfTurnaroundTime), (d / srtTurnaroundTime));

		}
		fclose(fp);
	}

	gsl_rng_free (r);

	// printf("In the main program, calling down to methods in other files now...\n");
    // improved_round_robin();
    // highest_response_ratio_next();
    // improved_multilevel_feedback_queue();
    // preemptive_priority_based();

    return 0;
}
