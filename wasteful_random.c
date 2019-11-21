// algorithm for a random time preemptive random scheduling
int wasteful_random(struct process processes[]) {

  int selectedProcess = -1;
  int randomSelect = rand()%numProcesses;


  if(processes[randomSelect].active == 1){
    selectedProcess = randomSelect;
  }

	// if no valid process was found to return
	if (selectedProcess == -1) {
		return -1;
	} else {
		return selectedProcess;
	}
}
