/* Question 18: 
 * Ten students (a,b,c,d,e,f,g,h,i,j) are going to attend an event. 
 * There are lots of gift shops, they all are going to the gift shops and
 * randomly picking the gifts. After picking the gifts they are randomly 
 * arriving in the billing counter. The accountant gives the preference to 
 * that student who has maximum number of gifts. Create a C or Java program 
 * to define order of billed students?
 */

#include <stdio.h>
#include <limits.h>
#define N 10

struct student {
	char name;
	int arrival_time;
	int gifts_bought;
	int billed;
};

int main() {
	struct student students[N];
	int billed_count = 0;
	int i;
		
	// get input:
	for(i = 0; i<N; i++) {
		students[i].name = 'A'+i;
		printf("Enter gifts bought by %c: ", students[i].name);
		scanf("%d", &(students[i].gifts_bought));
		printf("Enter arrival time (in minutes) of %c: ", students[i].name);
		scanf("%d", &(students[i].arrival_time));
		students[i].billed = 0;
	}

	printf("\nThe billing order will be as follows:\n");

	// now calculate billing order and print:
	while(billed_count<N) {
		int to_bill = 0;
		int min_arrival = INT_MAX;
		int max_gifts = 0;
		for(int i = 0; i<N; i++) {
			if(!students[i].billed) {
				if(students[i].arrival_time < min_arrival) {
					to_bill = i;
					min_arrival = students[i].arrival_time;
					max_gifts = students[i].gifts_bought;
				}
				if(students[i].arrival_time == min_arrival) {
					if(students[i].gifts_bought > max_gifts) {
						to_bill = i;
						max_gifts = students[i].gifts_bought;
					}
				}
			}
		}
		students[to_bill].billed = 1;
		billed_count++;
		printf("%c ", students[to_bill].name);
	}
	printf("\n");
	return 0;
}
