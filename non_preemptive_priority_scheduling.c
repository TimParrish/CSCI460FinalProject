//nonPreemptive Priority Scheduling

int non_preemptive_priority_scheduling(struct process processes[numProcesses], int clock, int indexOfRunning, int running)
{
        int indexOfPriority = -1;
        int priority = 100000;

        if(running == -1) {
                for(int i = 0; i < numProcesses; i++){
                        if(processes[i].active == 1){
                                if(processes[i].priority < priority){
                                        indexOfPriority = i;
                                        priority = processes[i].priority;
                                }
                        }
                }
        } else {
                indexOfPriority = indexOfRunning;
        }
        return indexOfPriority;
}
