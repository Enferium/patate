#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "fonctionsTCP.h"
#include "protocoleTicTacToe.h"
#include "fonctionJoueur.c"


main(int argc, char **argv){
	int sock, i, port;

	TypCoupReq coup;
	TypPartieReq demande;
	TypPartieRep reponse;
	char nomAdv[MAX_CH];
	TypSymbol symb;

	port = atoi(argv[2]);

	sock = socketClient(argv[1], port);
	if (sock < 0) {      
		printf("joueurTicTacToe : erreur socketClient\n");
		exit(2);
	}

	sleep(2);
	printf("Demande\n" );
	// DEMANDE DE PARTIE
	demandePartie(demande, sock);


	receptionPartie(sock, nomAdv, &symb);



	shutdown(sock, 2);
	close(sock);
}
