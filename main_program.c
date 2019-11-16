// CSCI-460: Operating Systems
// Fall 2019
// Team Members:
// Rusty Clayton
// Rial Johnson
// Tim Parrish

#include <stdio.h>
#include "improved_round_robin.c"
#include "highest_response_ratio_next.c"
#include "improved_multilevel_feedback_queue.c"
#include "preemptive_priority_based.c"

int main(void)
{
    printf("In the main program, callinig down to methods in other files now...\n");
    improved_round_robin();
    highest_response_ratio_next();
    improved_multilevel_feedback_queue();
    preemptive_priority_based();

    return 0;
}