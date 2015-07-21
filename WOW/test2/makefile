#********************************************************************
#
# Xinyi Wang
# Advanced Operating Systems
# Programming Project #2: Programming using MPI and RPC
# Project 2_1: Token Ring
# Date Assigned: Thursday, March 7, 2013
# Due Date: Tuesday, March 26, 2013 by 9:30 a.m.
# Instructor: Dr. Ajay K. Katangur
#
#********************************************************************
CC=mpicc
CFLAGS=-mpe=mpilog
all: aosproj2_1
	@echo "	All files have been compiled!"
aosproj2_1: aosproj2_1.c
	$(CC) $(CFLAGS) -o aosproj2_1 aosproj2_1.c
clean:
	rm -f *.o *.core core aosproj2_1 *.clog2 *.slog2
	@echo "	The directory have been cleaned!"
	