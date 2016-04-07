#ifndef _fonctionJoueur_h
#define _fonctionJoueur_h

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

#include "fonctionsTCP.h"
#include "protocoleTicTacToe.h"


void demandePartie(int sock, char* username);
int receptionPartie(int sock,char *nomAdversaire, TypSymbol* symbol);
void envoitCoup(int sock, TypSymbol symbol, int portJava);
int receptionCoup(int sock);
int finPartie();
void decoderCoup(TypCoupReq coup);
void demandeCoupProlog(int *tabCoup, int portJava);
TypCase encoderCoup(int numPlat, int numSousPlat);

#endif