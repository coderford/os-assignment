/* Question 17:
 * Design a scheduler following non-preemptive scheduling approach 
 * to schedule the processes that arrives at different units and having burst 
 * time double the arrival time. Scheduler selects the process with largest
 * burst time from the queue for the execution. Process is not being 
 * preempted until it finishes its service time. Compute the average waiting 
 * time and average turnaround time. What should be the average waiting time 
 * if processes are executed according to Shortest Job First scheduling 
 * approach with the same attribute values.
 */

#include <stdio.h>

typedef struct {
	int id;
	int arrival_time;
	int burst_time;
	int wait_time;
	int executed;
} process;

int completion_time(process *p) {
	return p->arrival_time + p->wait_time + p->burst_time;
}

void sort_asc(process **arr, int n) {
	// bubble sorting the processes according to burst time:
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

void schedule(process *p_list, int n, void (*sort)(process **, int)) {
	process *ready_queue[n];	
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
			printf("\tpid %d executed\n", ready_queue[ready_n-1]->id);
			ready_n--;
			finished++;
		}
		for(i = 0; i<ready_n; i++) {
			ready_queue[i]->wait_time++;
		}

		clock++;
	}
}

int main() {
	int p_count;
	printf("Number of processes: ");
	scanf("%d", &p_count);

	process p_list[p_count];

	int i;
	for(i = 0; i<p_count; i++) {
		printf("%d.\tArrival time: ", i+1);
		scanf("%d", &p_list[i].arrival_time);
		p_list[i].burst_time = p_list[i].arrival_time*2;
		p_list[i].id = i+1;
		p_list[i].wait_time = 0;
		p_list[i].executed = 0;
	}

	printf("\npid\tarrival\tburst\n");
	for(i = 0; i<p_count; i++) {
		printf("%d\t%d\t%d\n", p_list[i].id, p_list[i].arrival_time,
								p_list[i].burst_time);
	}
	printf("\nNow scheduling the processes (LJF):\n");
	schedule(p_list, p_count, sort_asc);
}
