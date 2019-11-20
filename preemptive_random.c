// algorithm for a random time preemptive random scheduling
int preemptive_random(struct process processes[]) {

	int selectedProcess = -1;
  int randomSelect = rand()%numProcesses;
  printf("%d", randomSelect);
  if(processes[randomSelect].active == 1){
    selectedProcess = randomSelect; 
  }

	// if no valid process was found to return
	if (selectedProcess = -1) {
		return -1;
	} else {
		return selectedProcess;
	}
}
