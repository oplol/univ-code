This folder has the following files:
1. aosproj4.c
2. aosproj4.pdf
3. input.txt
4. makefile
5. readme.txt



Project4:
1. Using MPI to simulate Chandy-Misra-Haas's edge chasing algorithm for distributed deadlock detection
2. Open a input file from the command line
3. Read the connections between the processes and the rank which is initiating deadlock detection
4. Send out the probe message from the rank which is initiating deadlock detection
5. If the block process receives its own probe, there is a deadlock; otherwise, no
6. Show the result in jumpshot



to complie the programs
$make

to run the project4
for example:
$mpirun -np 10 aosproj4 input.txt

to clean the directory
$make clean