//Pre-emptive priority based

// algorithm for a preemptive priority based scheduler
int preemptive_priority_based(struct process processes[numProcesses]) {

	int lowestPriorityProcessIndex = -1;
	int lowestPriority = k; // first arrival time cannot be after max arrival time

	// find active process that arrived the earliest
	for (int i = 0; i < numProcesses; i++) {

		// check if process is active
		if (processes[i].active == 1) {

			// check if the processe's arrival time was earlier than the earliest known
			if (processes[i].arrivalTime < lowestPriority) {

				lowestPriority = processes[i].arrivalTime; // set new earleist known arrival time
				lowestPriorityProcessIndex = i; // return index of the earliest known arrival time
			}
		}
	}

	return lowestPriorityProcessIndex;
}