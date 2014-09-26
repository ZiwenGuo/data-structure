# Makefile for CS 455 extra credit assgt Spring 2014
#
#     gmake getfiles
#        Copies or links assignment files to current directory
#
#     gmake ectest
#        Makes ectest executable
#
#     gmake submit
#        Submits the assignment.
#

# need to use gmake

HOME = /auto/home-scf-06/csci455/
ASSGTS = $(HOME)/assgts
ASSGTDIR = $(HOME)/assgts/ec

CXX = g++

CXXFLAGS = -ggdb -Wall
OBJS = listFuncs.o ectest.o

getfiles:
	-$(ASSGTS)/bin/safecopy $(ASSGTDIR)/listFuncs.cpp
	-$(ASSGTS)/bin/safecopy $(ASSGTDIR)/listFuncs.h
	-$(ASSGTS)/bin/safecopy $(ASSGTDIR)/ectest.cpp
	-$(ASSGTS)/bin/safecopy $(ASSGTDIR)/Makefile
	-$(ASSGTS)/bin/safecopy $(ASSGTDIR)/README

ectest: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

$(OBJS): listFuncs.h


submit: 
	submit -user csci455 -tag ec README listFuncs.cpp

clean:
	rm -f *.o ectest
