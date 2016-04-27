#########
#
# Makefile
#
#########


# For Linux
LD_FLAGS = -std=c99 -Wall -Wextra

all: joueurTicTacToe serveurTicTacToe

fonctionsTCP.o: fonctionsTCP.c fonctionsTCP.h
	gcc -c -o fonctionsTCP.o fonctionsTCP.c

joueurTicTacToe: joueurTicTacToe.c fonctionJoueur.h fonctionJoueur.c fonctionsTCP.o
	gcc joueurTicTacToe.c -o joueurTicTacToe fonctionsTCP.o $(LD_FLAGS)

serveurTicTacToe: serveurTicTacToe.c fonctionServeur.h fonctionServeur.c fonctionsTCP.o tictactoe.o
	gcc serveurTicTacToe.c -o serveurTicTacToe  fonctionsTCP.o tictactoe.o $(LD_FLAGS)

clean:
	rm *~ ; rm serveurTicTacToe ; rm joueurTicTacToe ; rm fonctionsTCP.o
