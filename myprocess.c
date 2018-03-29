#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "myprocess.h"

int completion_time(process *p) {
	return p->arrival_time + p->wait_time + p->burst_time;
}

void swap_max(process *ready_queue[], int n) {
	int max_bt = 0;
	int max_index = 0;
	int i;
	for(i = 0; i<n; i++) {
		if(ready_queue[i]->burst_time > max_bt) {
			max_bt = ready_queue[i]->burst_time;
			max_index = i;
		}
	}
	process *temp = ready_queue[n-1];
	ready_queue[n-1] = ready_queue[max_index];
	ready_queue[max_index] = temp;
}

void swap_min(process *ready_queue[], int n) {
	int min_bt = INT_MAX;
	int min_index = 0; 
	int i;
	for(i = 0; i<n; i++) {
		if(ready_queue[i]->burst_time < min_bt) {
			min_bt = ready_queue[i]->burst_time;
			min_index = i;
		}
	}
	process *temp = ready_queue[n-1];
	ready_queue[n-1] = ready_queue[min_index];
	ready_queue[min_index] = temp;
}

void schedule(process *p_list, int n, int type, int *order) {
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
			if(type == 1) {
				swap_max(ready_queue, ready_n);
			}
			else {
				swap_min(ready_queue, ready_n);
			}
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
