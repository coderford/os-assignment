/* Question 18:
 * Ten students (a,b,c,d,e,f,g,h,i,j) are going to attend an event.
 * There are lots of gift shops, they all are going to the gift shops and
 * randomly picking the gifts. After picking the gifts they are randomly
 * arriving in the billing counter. The accountant gives the preference to
 * that student who has maximum number of gifts. Create a C or Java program
 * to define order of billed students?
 */

#include <stdio.h>
#include "myprocess.h"

/*
	Using structures and functions developed for question 17 here to represent
	a student as a process. Here the burst time or billing time for a student
	is equal to the number of gifts he/she purchased. Whether they have been
	billed or not is indicated by the 'executed' variable in the structure.
*/

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
	int N = 10;
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
