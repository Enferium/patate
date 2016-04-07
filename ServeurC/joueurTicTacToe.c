#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "fonctionsTCP.h"
#include "protocoleTicTacToe.h"
#include "fonctionJoueur.c"


int main(int argc, char **argv){

	/*
	* verification des arguments
	*/
	if (argc != 4) {
  		printf ("usage : joueurTicTacToe server no_port userName\n");
  		return -1;
	}

	int sock, port;
	
	char nomAdv[MAX_CH];
	TypSymbol symb;

	port = atoi(argv[2]);

	sock = socketClient(argv[1], port);
	if (sock < 0) {      
		printf("joueurTicTacToe : erreur socketClient\n");
		exit(2);
	}

	sleep(2);
	// DEMANDE DE PARTIE
	printf("Demande\n" );
	demandePartie(sock, argv[3]);
	// Reception demande de partie
	receptionPartie(sock, nomAdv, &symb);
	
	if(symb == CROIX) {
		// Envoit d'un coup
		printf("Envoit coup : ");
		envoitCoup(sock, symb);
	}
	while(finPartie() != 1) {
		sleep(7);
		// Reception Coup Autre joueur
		printf("Reception coup adversaire : ");
		receptionCoup(sock);

		printf("Envoit coup : ");
		envoitCoup(sock, symb);
	}
	

	shutdown(sock, 2);
	close(sock);
}
