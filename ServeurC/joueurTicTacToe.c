#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "fonctionsTCP.h"
#include "protocoleTicTacToe.h"
#include "fonctionJoueur.c"


main(int argc, char **argv){
	int sock, i, port;
	int joueurActif;

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
	demandePartie(sock);
	// Reception demande de partie
	receptionPartie(sock, nomAdv, &symb);
	
	if(symb == CROIX) {
			// Envoit d'un coup
			printf("Envoit coup : ");
			envoitCoup(sock, symb);
		}
	while(finPartie() != 1) {
		
		// Reception Coup Autre joueur
		printf("Reception coup adversaire : ");
		receptionCoup(sock);

		printf("Envoit coup : ");
		envoitCoup(sock, symb);
	}
	

	shutdown(sock, 2);
	close(sock);
}
