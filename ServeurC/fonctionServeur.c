#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <signal.h>

#include "fonctionServeur.h"
#include "fonctionsTCP.h"
#include "protocoleTicTacToe.h"


int connexionJoueur(int* sockTrans, int sockConx){
	*sockTrans = accept(sockConx,NULL,NULL);
	printf("Connexion d'un joueur\n");
	if(*sockTrans < 0){
		return -1;//erreur
	}
	return 1;
}

int demandePartie(int sockTransJ1, int sockTransJ2,TypSymbol* symbj1, TypSymbol* symbj2){
		
	int nfsd= FD_SETSIZE;
	fd_set readSet;


	int joueur;

	FD_ZERO(&readSet) ;  // initialisation à zéro
    FD_SET(sockTransJ1, &readSet);
    FD_SET(sockTransJ2, &readSet);

    TypPartieReq demandeJ1;
    TypPartieReq demandeJ2;
    TypPartieRep reponseJ1;
    TypPartieRep reponseJ2;


    select(nfsd,&readSet,NULL,NULL,NULL);

    if(FD_ISSET(sockTransJ1,&readSet)){
		recv(sockTransJ1,&demandeJ1,sizeof(TypPartieReq),0);

		if(demandeJ1.idRequest == PARTIE){
			reponseJ1.symb = CROIX;
			reponseJ2.symb = ROND;

			reponseJ1.err = ERR_OK;
			strcpy(reponseJ2.nomAdvers,demandeJ1.nomJoueur);


  			printf("Joueur 1 demande partie\n");
		}else{
			reponseJ1.err = ERR_PARTIE;
		}
		joueur = 2;
    }

    if(FD_ISSET(sockTransJ2,&readSet)){
    	recv(sockTransJ2,&demandeJ2,sizeof(TypPartieReq),0);

    	if(demandeJ2.idRequest == PARTIE){
    		reponseJ2.symb = CROIX;
			reponseJ1.symb = ROND;

			strcpy(reponseJ1.nomAdvers ,demandeJ2.nomJoueur);
			reponseJ2.err = ERR_OK;
  			printf("Joueur 2 demande partie\n");
		}else{
			reponseJ2.err = ERR_PARTIE;
		}
		joueur = 1;
    }

    if(joueur == 1){
    	recv(sockTransJ1,&demandeJ1,sizeof(TypPartieReq),0);

    	if(demandeJ1.idRequest == PARTIE){
  			printf("Joueur 1 demande partie\n");
  			reponseJ1.err = ERR_OK;
  			strcpy(reponseJ2.nomAdvers, demandeJ1.nomJoueur);

    	}else{
    		reponseJ1.err = ERR_PARTIE;
    	}
    }else{
    	recv(sockTransJ2,&demandeJ2,sizeof(TypPartieReq),0);

    	if(demandeJ2.idRequest == PARTIE){
    		printf("Joueur 2 demande partie\n");
    		reponseJ2.err = ERR_OK;
    		strcpy(reponseJ1.nomAdvers , demandeJ2.nomJoueur);

    	}else{
    		reponseJ2.err = ERR_PARTIE;
    	}
    }

    send(sockTransJ1,&reponseJ1,sizeof(TypPartieRep),0);


    send(sockTransJ2,&reponseJ2,sizeof(TypPartieRep),0);

    *symbj1 = reponseJ1.symb;
    *symbj2 = reponseJ2.symb;

    return 0;
}



int receptionCoup(int sockTrans1, int sockTrans2){

    TypCoupReq coup;


    struct timeval tv;

    tv.tv_sec = 6;  /* 30 Secs Timeout */
    tv.tv_usec = 0;  // Not init'ing this can cause strange errors
    setsockopt(sockTrans1, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));

    int err = recv(sockTrans1,&coup,sizeof(TypCoupReq),0);
    if(err < 0){
        printf("ARBITRE : Erreur temps de 6 secondes dépasser\n");
        return 0;
    }
    TraitementCoup(coup,sockTrans1,sockTrans2);
    return 1;
}

int TraitementCoup(TypCoupReq coup, int sockTrans1, int sockTrans2){

    if(coup.idRequest == COUP){
        printf("ARBITRE : Reçu Coup\n");
        decoderCoup(coup);
        printf("ARBITRE : Transmission Coup\n");
        send(sockTrans2,&coup,sizeof(TypCoupReq),0);

        TypCoupRep rep;
        rep.propCoup = CONT;
        rep.validCoup = VALID;
        rep.err = ERR_OK;

        printf("ARBITRE : Envoie Validation \n");
        send(sockTrans1,&rep,sizeof(TypCoupRep),0);
        printf("ARBITRE : Envoie Validation \n");
        send(sockTrans2,&rep,sizeof(TypCoupRep),0);
        return 1;
    }else{
        printf("ARBITRE : Erreur Attendu COUP, Reçu PARTIE");
        return 0;
    }
    return 1;
}


int envoyerTempsDepasser(int sockTrans1, int sockTrans2){
    TypCoupRep rep;

    rep.err = ERR_COUP;
    rep.validCoup = TIMEOUT;
    rep.propCoup = PERDU;

    send(sockTrans1,&rep,sizeof(TypCoupRep),0);

    TypCoupReq req;
    req.idRequest = COUP;

    send(sockTrans2,&req,sizeof(TypCoupReq),0);


    rep.propCoup = GAGNANT;
    send(sockTrans2,&req,sizeof(TypCoupRep),0);

    return 1;
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