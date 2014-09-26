# Makefile for CS 455 PA5
#
#     make concord
#        Makes concord executable
#
#     make grades
#        Makes grades executable
#     
#     ./concord -s < ../testfiles/poe.txt > outfile
#


concord: concord.o Table.o
	g++ -ggdb -Wall -o concord concord.o Table.o

grades: grades.o Table.o
	g++ -ggdb -Wall -o grades grades.o Table.o


concord.o: concord.cpp Table.h
	g++ -ggdb -Wall -c concord.cpp

Table.o: Table.cpp Table.h
	g++ -ggdb -Wall -c Table.cpp

grades.o: grades.cpp Table.h
	g++ -ggdb -Wall -c grades.cpp

clean: 
	rm -f *.o concord grades
