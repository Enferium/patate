#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

#include "fonctionsTCP.h"
#include "protocoleTicTacToe.h"

TypCoup pptCoup = CONT;

void decoderCoup(TypCoupReq coup);

void demandePartie(int sock, char* username) {
	int err;
	TypPartieReq demande;
	strcpy(demande.nomJoueur, username);
	demande.idRequest = PARTIE;
	err = send(sock, &demande, sizeof(demande), 0);
	if (err != sizeof(demande)) {
		perror("joueurTicTacToe : erreur sur le send");
		shutdown(sock, 2); close(sock);
		exit(3);
	}
}

int receptionPartie(int sock,char *nomAdversaire, TypSymbol* symbol){

	TypPartieRep reponse;
	int err = recv(sock,&reponse,sizeof(TypPartieRep),0);

	*symbol = reponse.symb;
	strcpy(nomAdversaire,reponse.nomAdvers);


	if(reponse.symb == CROIX){
		printf("Je suis la croix\n");
	} else {
		printf("Je suis le rond\n");
	}

	printf("nom Adversaire : %s\n",nomAdversaire );

	return 1;

}

void envoitCoup(int sock, TypSymbol symbol) {
	int err;
	TypCoupReq coup;
	coup.idRequest = COUP;
	coup.symbolJ = symbol;
	TypCase pos;
	pos.numPlat = D;
	pos.numSousPlat = TROIS;
	coup.pos = pos;
	coup.nbSousPlatG = 1;

	decoderCoup(coup);

	err = send(sock, &coup, sizeof(coup), 0);
	if (err != sizeof(coup)) {
		perror("joueurTicTacToe : erreur sur le send");
		shutdown(sock, 2); close(sock);
		exit(3);
	}
	TypCoupRep reponseCoup;
	err = recv(sock, &reponseCoup, sizeof(reponseCoup), 0);
}

int receptionCoup(int sock) {
	TypCoupRep reponseCoup;
	TypCoupReq coupAdversaire;
	int err1 = recv(sock, &coupAdversaire, sizeof(coupAdversaire), 0);
	int err = recv(sock, &reponseCoup, sizeof(reponseCoup), 0);
	
	decoderCoup(coupAdversaire);
	pptCoup = reponseCoup.propCoup;

	return 1;
}

int finPartie() {
	if (pptCoup == CONT) {
		return 0;
	} else if (pptCoup == NULLE || pptCoup == GAGNANT || pptCoup == PERDU) {
		return 1;
	}
}


void decoderCoup(TypCoupReq coup) {

	switch(coup.pos.numPlat) {
		case I :
			printf("I ");
			break;
		case B :
			printf("B ");
			break;
		case C :
			printf("C ");
			break;
		case D :
			printf("D ");
			break;
		case E :
			printf("E ");
			break;
		case F :
			printf("F ");
			break;
		case G :
			printf("G ");
			break;
		case H :
			printf("H ");
			break;
		case A :
			printf("A ");
			break;
		default :
			break;
	}
	switch (coup.pos.numSousPlat) {
		case UN :
			printf("UN\n");
			break;
		case DEUX :
			printf("DEUX\n");
			break;
		case TROIS :
			printf("TROIS\n");
			break;
		case QUATRE :
			printf("QUATRE\n");
			break;
		case CINQ :
			printf("CINQ\n");
			break;
		case SIX :
			printf("SIX\n");
			break;
		case SEPT :
			printf("SEPT\n");
			break;
		case HUIT :
			printf("HUIT\n");
			break;
		case NEUF :
			printf("NEUF\n");
			break;
		default :
			break;
	}
}