
//Lowest Response Ratio Next
#define BIG_NUM = 100000
int lowest_response_ratio_next(struct process processes[numProcesses], int clock, int indexOfRunning, int lrrRunning)
{
        int indexOfLRRN = -1;
        int lowestResponseRatio = BIG_NUM;

        if(lrrRunning == -1) {
                for(int i = 0; i < numProcesses; i++){
                        if(processes[i].active == 1){
                                float response = clock - processes[i].cpuTime;
                                response = response / processes[i].cpuTime;
                                if(response < lowestResponseRatio){
                                        indexOfLRRN = i;
                                        lowestResponseRatio = response;
                                }
                        }
                }
        } else {
                indexOfLRRN = indexOfRunning;
        }
        return indexOfLRRN;
}
