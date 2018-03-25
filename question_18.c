/* Question 18: 
 * Ten students (a,b,c,d,e,f,g,h,i,j) are going to attend an event. 
 * There are lots of gift shops, they all are going to the gift shops and
 * randomly picking the gifts. After picking the gifts they are randomly 
 * arriving in the billing counter. The accountant gives the preference to 
 * that student who has maximum number of gifts. Create a C or Java program 
 * to define order of billed students?
 */

#include <stdio.h>
#define N 10

struct student {
	char name;
	int arrival_time;
	int gifts_bought;
};

int main() {
	struct student students[N];
	for(int i = 0; i<N; i++) {
		students[i].name = 'A'+i;
		printf("Enter gifts bought by %c: ", students[i].name);
		scanf("%d", &(students[i].gifts_bought));
		printf("Enter arrival time (in minutes) of %c: ", students[i].name);
		scanf("%d", &(students[i].arrival_time));
		students[i]
	}
}
