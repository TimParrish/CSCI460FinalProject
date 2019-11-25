// algorithm for a shortest job first scheduler
int sjf(struct process processes[], int currentIndex) {

	// this means we're just starting or couldn't find a valid process
	if (currentIndex == -1) {

		// do nothing

	} else {

		// if we're already working on a process, we must keep working (no pre-emption)
		if (processes[currentIndex].remainingCpuTime > 0) {
			return currentIndex;
		}
	}

	int leastTime = INT_MAX;
	int leastTimeIndex = 0;

	// find the process with the shortest total cpu time
	for (int i = 0; i < numProcesses; i++) {
		if (processes[i].cpuTime < leastTime) {

			// check if this is a valid option
			if (processes[i].remainingCpuTime > 0 && processes[i].active == 1) {

				// if valid, redefine what our least time and the current best index is
				leastTime = processes[i].cpuTime;
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