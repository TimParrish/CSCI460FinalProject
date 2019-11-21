// improved Round Robin

int round_robin(struct process processes[], int currentIndex, int *scheduledTimeLeft, int timeQuanta)
{
	
	// if we're already working on a process, we must keep working it unless it's schedule time is up
	if (currentIndex != -1) {	
		*scheduledTimeLeft = *scheduledTimeLeft - 1; // decrement the time left to ensure each program runs for it's schedule time quanta	
		if (processes[currentIndex].active == 1 && *scheduledTimeLeft > 0) {
			printf("Scheduled time left is: %d", *scheduledTimeLeft);
			return currentIndex;
		}
	}	
		
	*scheduledTimeLeft = timeQuanta; // if we're moving on to a new process, reset the timeQuanta 
	
	// start where we just finished and start looking after until end of array
	for (int i = currentIndex + 1; i < numProcesses; i++) {
		if (processes[i].active == 1) {
			return i;
		}		
	}
	
	// if nothing was found, loop back to beginning of array and look until where we left off 
	for (int i = 0; i <= currentIndex; i++) {
		if (processes[i].active == 1) {
			return i;
		}
	}
		
	return -1; // if we found no valid process to run
}