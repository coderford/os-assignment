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
#include <stdlib.h>
#include "myprocess.h"

void print_order(int *order, process *p_list, int n) {
	int i;
	for(i = 0; i<n; i++) {
		printf("\tpid %d executed\n",order[i]);
		printf("\t\twaiting time: %d, completion time: %d\n", 
		 p_list[order[i]-1].wait_time, 
		 completion_time(&p_list[order[i]-1])
		);
	}
}

int main() {
	int p_count;
	printf("Number of processes: ");
	scanf("%d", &p_count);

	process *p_list = (process *)malloc(p_count*sizeof(process));
	int *order = (int *)malloc(p_count*sizeof(int));

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
	printf("\nScheduling the processes with LJF:\n");
	schedule(p_list, p_count, sort_asc, order);
	print_order(order, p_list, p_count);

	float total_wt = 0;
	float total_tat = 0;
	for(i = 0; i<p_count; i++) {
		total_wt += p_list[i].wait_time;
		total_tat += completion_time(&p_list[i]) - p_list[i].arrival_time;
	}
	printf("\n - Total waiting time: %.2f\n", total_wt);
	printf(" - Total turn-around time: %.2f\n", total_tat);
	printf(" - Average waiting time: %.2f\n",total_wt/p_count);
	printf(" - Average turn-around time: %.2f\n", total_tat/p_count);

	for(i = 0; i<p_count; i++) {
		p_list[i].wait_time = 0;
		p_list[i].executed = 0;
	}

	printf("\nScheduling the processes with SJF:\n");
	schedule(p_list, p_count, sort_desc, order);
	print_order(order, p_list, p_count);

	total_wt = 0;
	total_tat = 0;
	for(i = 0; i<p_count; i++) {
		total_wt += p_list[i].wait_time;
		total_tat += completion_time(&p_list[i]) - p_list[i].arrival_time;
	}
	printf("\n - Total waiting time: %.2f\n", total_wt);
	printf(" - Total turn-around time: %.2f\n", total_tat);
	printf(" - Average waiting time: %.2f\n", (float)(total_wt)/p_count);
	printf(" - Average turn-around time: %.2f\n", (float)(total_tat)/p_count);

	free(p_list);
	free(order);
	return 0;
}
