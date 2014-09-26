warmup1: main.o my402list.o
	gcc -o warmup1 -g main.o my402list.o

main.o: main.c my402list.h
	gcc -g -c -Wall main.c

my402list.o: my402list.c my402list.h
	gcc -g -c -Wall my402list.c

clean:
	rm -f *.o warmup1
