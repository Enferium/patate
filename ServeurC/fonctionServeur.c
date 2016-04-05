#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

#include "fonctionsTCP.h"
#include "protocoleTicTacToe.h"

void decoderCoup(TypCoupReq coup);

int connexionJoueur(int* sockTrans, int sockConx){
	*sockTrans = accept(sockConx,NULL,NULL);
	printf("Connexion d'un joueur\n");
	if(*sockTrans < 0){
		return -1;//erreur
	}
	return 1;
}

int demandePartie(int sock, int sockTransJ1, int sockTransJ2,TypSymbol* symbj1, TypSymbol* symbj2){
		
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

int receptionCoup(int sock, int sockTrans1, int sockTrans2){

    TypCoupReq coup;
    recv(sockTrans1,&coup,sizeof(TypCoupReq),0);

    decoderCoup(coup);

    if(coup.idRequest == COUP){
        printf("COUP");

        send(sockTrans2,&coup,sizeof(TypCoupReq),0);


        TypCoupRep rep;
        rep.propCoup = CONT;
        rep.validCoup = VALID;
        rep.err = ERR_OK;

        send(sockTrans1,&rep,sizeof(TypCoupRep),0);

        send(sockTrans2,&rep,sizeof(TypCoupRep),0);

        memset(&coup,0,sizeof(TypCoupReq));
        memset(&rep,0,sizeof(TypPartieRep));

        return 1;

    }
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