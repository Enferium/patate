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
	if (argc != 5) {
  		printf ("usage : joueurTicTacToe server no_port userName portJava\n");
  		return -1;
	}

	int sock, port;
	
	char nomAdv[MAX_CH];
	TypSymbol symb;
	TypCoupReq coupAdversaire;

	port = atoi(argv[2]);
	int portJava = atoi(argv[4]);

	sock = socketClient(argv[1], port);
	if (sock < 0) {      
		printf("joueurTicTacToe : erreur socketClient\n");
		exit(2);
	}
	int socketJava = socketClient(argv[1], portJava);
	if (socketJava < 0) { 
	    printf("client : erreur socket comm JAVA\n");
	    exit(2);
	}

	sleep(2);
	// DEMANDE DE PARTIE
	printf("\n------------ DEMANDE PARTIE ----------------\n");
	demandePartie(sock, argv[3]);
	// Reception demande de partie
	receptionPartie(sock, nomAdv, &symb);
	
	if(symb == CROIX) {
		// Envoit d'un coup
		printf("\n------------ ENVOIT COUP -----------------\n");
		printf("COUP : ");
		envoitCoup(sock, symb, socketJava,coupAdversaire);
	}

	while(finPartie() != 1) {
		// Reception Coup Autre joueur
		printf("\n------------ RECEPTION COUP OPPONENT -------------------\n");
		printf("COUP : ");
		coupAdversaire = receptionCoup(sock);

		if(finPartie() !=1){
			printf("\n------------ ENVOIT COUP -----------------\n");
			printf("COUP : ");
			envoitCoup(sock, symb, socketJava,coupAdversaire);
		}
	}
	
	final();

	shutdown(sock, 2);
	close(sock);
	close(socketJava);
}
