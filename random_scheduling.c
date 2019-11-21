// algorithm for a random time scheduling
int random_scheduling(struct process processes[]) {

  	int selectedProcess = -1;
	int counter = 0;
	int processSelected = 0;
	int activeProcessExists = 0;
	for(int i = 0; i < numProcesses; i++){
		if(processes[i].active == 1){
			activeProcessExists = 1;
		}
	}

	while(processSelected == 0 && activeProcessExists != 0){
		int randomSelect = rand()%numProcesses;
		if(processes[randomSelect].active == 1){
			processSelected = 1;
			selectedProcess = randomSelect;
		}
	}


        // if no valid process was found to return
        if (selectedProcess == -1) {
                return -1;
        } else {
                return selectedProcess;
        }
}
