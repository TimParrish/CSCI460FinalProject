// algorithm for a shortest remaining time scheduler
int srt(struct process processes[]) {	
		
	int leastTime = INT_MAX;
	int leastTimeIndex = 0;
	
	// find the process with the shortest remaining cpu time
	for (int i = 0; i < numProcesses; i++) {
		if (processes[i].remainingCpuTime < leastTime) {
			
			// check if this is a valid option
			if (processes[i].remainingCpuTime > 0 && processes[i].active == 1) {
				
				// if valid, redefine what our least time and the current best index is
				leastTime = processes[i].remainingCpuTime;
				leastTimeIndex = i;
			} 		
		}
	}
	
	// if no valid process was found to return
	if (leastTime == INT_MAX) {
		return -1;
	} else {
		return leastTimeIndex;
	}
}