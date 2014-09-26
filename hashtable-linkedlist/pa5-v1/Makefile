# Makefile for CS 455 PA5
#
#     gmake getfiles
#        Copies or links assignment files to current directory
#
#     gmake concord
#        Makes concord executable
#
#     gmake grades
#        Makes grades executable
#
#     gmake submit
#        Submits the assignment.
#

# need to use gmake

HOME = /auto/home-scf-06/csci455/
ASSGTS = $(HOME)/assgts
ASSGTDIR = $(HOME)/assgts/pa5


getfiles:
	-ln -s $(ASSGTDIR)/melville.txt .
	-ln -s $(ASSGTDIR)/poe.txt .
	-$(ASSGTS)/bin/safecopy $(ASSGTDIR)/concord.cpp
	-$(ASSGTS)/bin/safecopy $(ASSGTDIR)/grades.cpp
	-$(ASSGTS)/bin/safecopy $(ASSGTDIR)/Table.h
	-$(ASSGTS)/bin/safecopy $(ASSGTDIR)/Table.cpp
	-$(ASSGTS)/bin/safecopy $(ASSGTDIR)/Makefile


concord: concord.o Table.o
	g++ -ggdb -Wall -Wno-sign-compare -o concord concord.o Table.o

grades: grades.o Table.o
	g++ -ggdb -Wall -Wno-sign-compare -o grades grades.o Table.o


concord.o: concord.cpp Table.h
	g++ -ggdb -Wall -Wno-sign-compare -c concord.cpp

Table.o: Table.cpp Table.h
	g++ -ggdb -Wall -Wno-sign-compare -c Table.cpp

grades.o: grades.cpp Table.h
	g++ -ggdb -Wall -Wno-sign-compare -c grades.cpp

submit:
	submit -user csci455 -tag pa5 README Table.h Table.cpp grades.cpp
