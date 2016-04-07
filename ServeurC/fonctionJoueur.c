#include "fonctionJoueur.h"

TypCoup pptCoup = CONT;


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
	recv(sock,&reponse,sizeof(TypPartieRep),0);

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

void envoitCoup(int sock, TypSymbol symbol, int socketJava) {

	int tabCoup[2];
	demandeCoupProlog(tabCoup, socketJava);

	TypCase pos = encoderCoup(tabCoup[0], tabCoup[1]);

	int err;
	TypCoupReq coup;
	coup.idRequest = COUP;
	coup.symbolJ = symbol;
	coup.pos = pos;
	coup.nbSousPlatG = 1;

	// On affiche le coup que l'on envoit à l'adversaire
	decoderCoup(coup);

	err = send(sock, &coup, sizeof(coup), 0);
	if (err != sizeof(coup)) {
		perror("joueurTicTacToe : erreur sur le send");
		shutdown(sock, 2); close(sock);
		exit(3);
	}
	TypCoupRep reponseCoup;
	err = recv(sock, &reponseCoup, sizeof(reponseCoup), 0);

	if(reponseCoup.validCoup == VALID){
			printf("Coup Valide\n");
	}else if(reponseCoup.validCoup == TIMEOUT){
		printf("Je suis en TIMEOUT\n");
	}else if(reponseCoup.validCoup == TRICHE){
		
	}
	pptCoup = reponseCoup.propCoup;
}

int receptionCoup(int sock) {
	TypCoupRep reponseCoup;
	TypCoupReq coupAdversaire;
	recv(sock, &coupAdversaire, sizeof(coupAdversaire), 0);
	recv(sock, &reponseCoup, sizeof(reponseCoup), 0);
	

	if(reponseCoup.validCoup == VALID){
		decoderCoup(coupAdversaire);
	}else if(reponseCoup.validCoup == TIMEOUT){
		printf("Le joueur adversaire est en TIMEOUT\n");
	}else if(reponseCoup.validCoup == TRICHE){
		
	}

	// On affiche le coup que l'on reçoit de l'adversaire
	
	pptCoup = reponseCoup.propCoup;

	return 1;
}

int finPartie() {
	if (pptCoup == CONT) {
		return 0;
	} else if (pptCoup == NULLE || pptCoup == GAGNANT || pptCoup == PERDU) {
		return 1;
	}
	return 1;
}


void demandeCoupProlog(int *tabCoup, int sock) {

	int demandeCoupProlog = 10;
	send(sock, &demandeCoupProlog, sizeof(int), 0);

	char intBufferCoupReq[1024];
	memset(intBufferCoupReq, '\0', sizeof(intBufferCoupReq));

	int k = 0;
	while ( 1 ) { 
	    int nbytes = recv(sock, &intBufferCoupReq[k], sizeof(intBufferCoupReq), 0); 
	    if ( nbytes == -1 ) { break; }
	    k++;
	}

	int *myints = (int*) intBufferCoupReq;
	int i = 0;
	for ( i=0; i<(k/4); i++ ) {
		tabCoup[i] = ntohl(myints[i]);
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

TypCase encoderCoup(int numPlat, int numSousPlat) {

	TypCase pos;
	switch(numPlat) {
		case 1 :
			pos.numPlat = A;
			break;
		case 2 :
			pos.numPlat = B;
			break;
		case 3 :
			pos.numPlat = C;
			break;
		case 4 :
			pos.numPlat = D;
			break;
		case 5 :
			pos.numPlat = E;
			break;
		case 6 :
			pos.numPlat = F;
			break;
		case 7 :
			pos.numPlat = G;
			break;
		case 8 :
			pos.numPlat = H;
			break;
		case 9 :
			pos.numPlat = I;
			break;
	}

	switch(numSousPlat) {
		case 1 :
			pos.numSousPlat = UN;
			break;
		case 2 :
			pos.numSousPlat = DEUX;
			break;
		case 3 :
			pos.numSousPlat = TROIS;
			break;
		case 4 :
			pos.numSousPlat = QUATRE;
			break;
		case 5 :
			pos.numSousPlat = CINQ;
			break;
		case 6 :
			pos.numSousPlat = SIX;
			break;
		case 7 :
			pos.numSousPlat = SEPT;
			break;
		case 8 :
			pos.numSousPlat = HUIT;
			break;
		case 9 :
			pos.numSousPlat = NEUF;
			break;

	}

	return pos;

}