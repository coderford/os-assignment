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
void swap_min(process **, int);
void swap_max(process **, int);
void schedule(process *, int, int, int *);

#endif
