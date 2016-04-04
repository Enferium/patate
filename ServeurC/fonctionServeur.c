#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

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

int demandePartie(int sock, int sockTransJ1, int sockTransJ2){
		
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

    return 0;
}

int receptionCoup(int sock, int sockTrans){

    TypCoupReq coup;    
    recv(sockTrans,&coup,sizeof(TypCoupReq),0);
    if(coup.idRequest == COUP){
            printf("COUP");
    }
}