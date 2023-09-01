###
### Makefile for ZAP Project
###
### Author:  Sam Miller
###
### Purpose: The purpose of this file is to build, clean and compile all of
###   		 the files that are needed to build the ultimate execulatable 
###			 which is Zap. 

MAKEFLAGS += -L 
CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3

# HuffmanCoder: HuffmanCoder.o phaseOne.o main.o 
# 	$(CXX) $(CXXFLAGS) -o HuffmanCoder HuffmanCoder.o phaseOne.o main.o 

zap: HuffmanCoder.o phaseOne.o main.o BinaryIO.o HuffmanTreeNode.o
	$(CXX) $(LDFLAGS) -o zap HuffmanCoder.o phaseOne.o main.o BinaryIO.o \
						 HuffmanTreeNode.o

HuffmanCoder.o: HuffmanCoder.cpp HuffmanCoder.h BinaryIO.h phaseOne.o \
		HuffmanTreeNode.o
	$(CXX) $(CXXFLAGS) -c HuffmanCoder.cpp
	
phaseOne.o: phaseOne.cpp phaseOne.h BinaryIO.h HuffmanTreeNode.h HuffmanCoder.h
	$(CXX) $(CXXFLAGS) -c phaseOne.cpp

# # building main
main.o: main.cpp phaseOne.h HuffmanTreeNode.h BinaryIO.h HuffmanCoder.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# The below rule will be used by unit_test.
unit_test: unit_test_driver.o phaseOne.o HuffmanTreeNode.o  \
HuffmanCoder.o BinaryIO.o 
	$(CXX) $(CXXFLAGS) $^

clean:
	rm main.o phaseOne.o HuffmanCoder.o zap

# ## Here is a rule for compiling .cyl files for use in your testing
# ##
# %.cylc:  %.cyl
# 	./cylc $^