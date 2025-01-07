all: hexeditplus digit_counter

hexeditplus: task1.o
	gcc -m32 -g -Wall -o hexeditplus task1.o

task1.o: task1.c
	gcc -m32 -g -Wall -c -o task1.o task1.c

digit_counter: task4.c
	gcc -m32 -fno-pie -fno-stack-protector -no-pie -o digit_counter task4.c

.PHONY: clean

clean:
	rm -f *.o hexeditplus digit_counter
