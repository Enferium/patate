#########
#
# Makefile pour mini
#
#########

# For Solaris
#LD_FLAGS = -lsocket -lnsl

# For Linux
LD_FLAGS =

all: joueurTicTacToe serveurTicTacToe

fonctionsTCP.o: fonctionsTCP.c fonctionsTCP.h
	gcc -c fonctionsTCP.c

joueurTicTacToe: joueurTicTacToe.c fonctionJoueur.c fonctionsTCP.h fonctionsTCP.o
	gcc fonctionsTCP.o joueurTicTacToe.c -o joueurTicTacToe  $(LD_FLAGS)

serveurTicTacToe: serveurTicTacToe.c fonctionServeur.c fonctionsTCP.h fonctionsTCP.o
	gcc fonctionsTCP.o serveurTicTacToe.c -o serveurTicTacToe   $(LD_FLAGS)

clean:
	rm *~ ; rm -i \#* ; rm *.o; \
        rm serveurTicTacToe ; rm joueurTicTacToe
