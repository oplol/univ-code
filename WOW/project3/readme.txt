This folder has the following files:
1. aosproj3_1.c
2. aosproj3_1.pdf
3. aosproj3_2.c
4. aosproj3_2.pdf
5. input1.txt
6. input2.txt
7. makefile
8. readme.txt



Project3_1:
1. Using MPI to implement Lamport's logical clocks
2. Open a input file from the command line
3. Read in a set of simulation parameters and then print the logical clocks associated with each event
3. Using the master and slaves algorithm to simulate the Lamport's logical clocks
4. The master process provides the information for the slaves processes
5. The slaves processes record the logical time for each event
6. Show the result in jumpshot

Project3_2:
1. Using MPI to implement vector clocks
2. Open a input file from the command line
3. Read in a set of simulation parameters and then print the logical clocks associated with each event
3. Using the master and slaves algorithm to simulate the vector clocks
4. The master process provides the information for the slaves processes
5. The slaves processes record the vector time for each event
6. Show the result in jumpshot



to complie both programs
$make

to run the project3_1
for example:
$mpirun -np 4 aosproj3_1 input1.txt

to run the project1_2
for example:
$mpirun -np 4 aosproj3_2 input2.txt

to clean the directory
$make clean