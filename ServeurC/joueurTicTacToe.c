#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "fonctionsTCP.h"
#include "protocoleTicTacToe.h"
#include "fonctionJoueur.c"


main(int argc, char **argv){
	int sock, i, port;

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
	
	if(symb == ROND) {
		// Envoit d'un coup
		printf("Envoit coup\n");
		envoitCoup(sock, symb);
	}
	// Reception Coup Autre joueur
	printf("Reception coup adversaire\n");
	receptionCoup(sock);
	

	shutdown(sock, 2);
	close(sock);
}
