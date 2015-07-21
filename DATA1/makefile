all: play_rps referee player

clean:
	rm *.o play_rps referee player

play_rps: play_rps.o
	g++ play_rps.o -o play_rps

play_rps.o: play_rps.cpp
	g++ -Wall -c play_rps.cpp

referee: referee.o
	g++ referee.o -o referee

referee.o: referee.cpp
	g++ -Wall -c referee.cpp 

player: player.o
	g++ player.o -o player

player.o: player.cpp
	g++ -Wall -c player.cpp 
