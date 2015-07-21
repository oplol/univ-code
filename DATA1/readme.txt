RPS_Play
Yuchen Tong and Xinyi Wang
This directory contains:
readme.txt
makefile
player_rps.cpp
referee.cpp
player.cpp

Description:
This program  is a simple game of rock, paper, and scissors where two players compete against each other while the  referee tabulates the score and decides the winner of the game. The main purpose of the project is to learn how to communicate between  processes using sockets.



To run the game with individual commands:
$ g++ -o play_rps play_rps.cpp
$ g++ -o referee referee.cpp
$ g++ -o player player.cpp
$ ./play_rps n   (Note: n stands for the number of rounds in a game)

To run the game using the makefile:
$ make
$ ./play_rps n    (Note: n stands for the number of rounds in a game)

