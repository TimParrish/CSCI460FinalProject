//Highest Response Ratio Next

int highest_response_ratio_next(struct process processes[numProcesses], int clock, int indexOfRunning, int hrrRunning)
{
	int indexOfHRRN = -1;
	int highestResponseRatio = 0;

	if(hrrRunning == -1) {
		for(int i = 0; i < numProcesses; i++){
			if(processes[i].active == 1){
				float response = clock - processes[i].cpuTime;
				response = response / processes[i].cpuTime;
				if(response > highestResponseRatio){
					indexOfHRRN = i;
					highestResponseRatio = response;
				}
			}
		}
	} else {
		indexOfHRRN = indexOfRunning;
	}
	return indexOfHRRN;
}
