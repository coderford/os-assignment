#ifndef MYPROCESS_H
#define MYPROCESS_H


typedef struct {
	int id;
	int arrival_time;
	int burst_time;
	int wait_time;
	int executed;
} process;

int completion_time(process *);
void sort_asc(process **, int);
void sort_desc(process **, int);
void schedule(process *, int, void (*)(process **, int), int *);

#endif
