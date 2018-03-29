CC=clang
all: question_18 question_17
question_18: question_18.o myprocess.o
	$(CC) -o question_18 question_18.o myprocess.o
question_18.o: question_18.c myprocess.h 
	$(CC) -c question_18.c 
myprocess.o: myprocess.c myprocess.h
	$(CC) -c myprocess.c
question_17: question_17.o myprocess.o
	$(CC) -o question_17 question_17.o myprocess.o
question_17.o: question_17.c myprocess.h 
	$(CC) -c question_17.c 

clean: 
	rm *.o
