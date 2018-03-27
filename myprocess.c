#include <stdio.h>
#include <stdlib.h>
#include "myprocess.h"

int completion_time(process *p) {
	return p->arrival_time + p->wait_time + p->burst_time;
}

void sort_asc(process **arr, int n) {
	// bubble sorting the processes according to burst time:
	// ascending order for LJF
	int i, j;
	for(i = 0; i<n-1; i++) {
		for(j = 0; j<n-i-1; j++) {
			if(arr[j]->burst_time > arr[j+1]->burst_time) {
				process *temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}
void sort_desc(process **arr, int n) {
	// bubble sorting the processes according to burst time:
	// descending order for SJF
	int i, j;
	for(i = 0; i<n-1; i++) {
		for(j = 0; j<n-i-1; j++) {
			if(arr[j]->burst_time < arr[j+1]->burst_time) {
				process *temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

void schedule(process *p_list, int n, 
		void (*sort)(process **, int), 
		int *order
	) {
	process **ready_queue = (process **)malloc(n*sizeof(process*));	
	int ready_n;
	int clock = 0;					
	int finished = 0;				// no. of processes done executing
	process *current = NULL; 		// currently executing process
	int i;
	
	while(finished < n) {
		for(i = 0; i<n; i++) {
			if(p_list[i].arrival_time == clock && p_list[i].executed == 0) {
				ready_queue[ready_n] = &p_list[i];
				ready_n++;
			}
		}
		if(current != NULL && completion_time(current) == clock) {
			current = NULL;
		}

		if(ready_n > 0 && current == NULL) {
			sort(ready_queue, ready_n);
			ready_queue[ready_n-1]->executed = 1;
			current = ready_queue[ready_n-1];
			order[finished] = ready_queue[ready_n-1]->id;

			ready_n--;
			finished++;
		}

		for(i = 0; i<ready_n; i++) {
			ready_queue[i]->wait_time++;
		}

		clock++;
	}
	free(ready_queue);
}
