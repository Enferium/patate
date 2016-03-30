#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

#include "fonctionsTCP.h"
#include "protocoleTicTacToe.h"


void demandePartie(TypPartieReq demande, int sock) {
	int err;
	demande.idRequest = PARTIE;
	demande.nomJoueur[0]='T';demande.nomJoueur[1]='\0';
	err = send(sock, &demande, sizeof(demande), 0);
	if (err != sizeof(demande)) {
		perror("joueurTicTacToe : erreur sur le send");
		shutdown(sock, 2); close(sock);
		exit(3);
	}
}

int receptionPartie(int sock,char *nomAdversaire, TypSymbol* symbol){

	TypPartieRep reponse;
	recv(sock,&reponse,sizeof(TypPartieRep),0);

	*symbol = reponse.symb;
	strcpy(nomAdversaire,reponse.nomAdvers);


	if(reponse.symb == CROIX){
		printf("Je suis la croix\n");
	}
	else{
		printf("Je suis le rond\n");
	}

	printf("nom Adversaire : %s\n",nomAdversaire );

	return 1;

}