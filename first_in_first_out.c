// algorithm for a first-in-first-out scheduler
int fifo(struct process processes[numProcesses]) {
	
	int smallestArrivalIndex = -1;
	int firstArrivalTime = k; // first arrival time cannot be after max arrival time
	
	// find active process that arrived the earliest
	for (int i = 0; i < numProcesses; i++) {
		
		// check if process is active
		if (processes[i].active == 1) {
		
			// check if the processe's arrival time was earlier than the earliest known
			if (processes[i].arrivalTime < firstArrivalTime) {
				
				firstArrivalTime = processes[i].arrivalTime; // set new earleist known arrival time
				smallestArrivalIndex = i; // return index of the earliest known arrival time			
			}		
		}
	}
	
	return smallestArrivalIndex;	
}