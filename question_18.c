/* Question 18:
 * Ten students (a,b,c,d,e,f,g,h,i,j) are going to attend an event.
 * There are lots of gift shops, they all are going to the gift shops and
 * randomly picking the gifts. After picking the gifts they are randomly
 * arriving in the billing counter. The accountant gives the preference to
 * that student who has maximum number of gifts. Create a C or Java program
 * to define order of billed students?
 */

#include <stdio.h>

/*
	Using structures and functions developed for question 17 here to represent
	a student as a process. Here the burst time or billing time for a student
	is equal to the number of gifts he/she purchased. Whether they have been
	billed or not is indicated by the 'executed' variable in the structure.
*/

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
	// ascending order
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

void schedule(process *p_list, int n,
		void (*sort)(process **, int),
		int *order
	) {
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
			order[finished] = ready_queue[ready_n-1]->id;

			ready_n--;
			finished++;
		}

		for(i = 0; i<ready_n; i++) {
			ready_queue[i]->wait_time++;
		}

		clock++;
	}
}

void print_order(int *order, process *p_list, char *names, int n) {
	int i;
	for(i = 0; i<n; i++) {
		printf("\t%d. %c:",i+1, names[order[i]-1]);
		printf("\twaiting time: %d, completion time: %d\n",
		 p_list[order[i]-1].wait_time,
		 completion_time(&p_list[order[i]-1])
		);
	}
}

int main() {
	int N = 3;
	process students[N];
	int order[N];
	char names[N];
	int i;

	// get input:
	for(i = 0; i<N; i++) {
		names[i] = 'A'+i;
		printf("%c:\tGifts bought: ", names[i]);
		scanf("%d", &students[i].burst_time);
		printf("\tArrival time: ");
		scanf("%d", &students[i].arrival_time);
		//printf("%d", students[i].arrival_time);

		students[i].id = i+1;
		students[i].executed = 0;
		students[i].wait_time = 0;
	}


	schedule(students, N, sort_asc, order);
    printf("\nThe billing order will be as follows:\n");
	print_order(order, students, names, N);

	return 0;
}
