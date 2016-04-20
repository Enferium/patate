#ifndef _fonctionServeur_h
#define _fonctionServeur_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "fonctionsTCP.h"
#include "protocoleTicTacToe.h"
#include "stdbool.h"

int connexionJoueur(int* sockTrans, int sockConx);
int demandePartie(int sockTransJ1, int sockTransJ2,TypSymbol* symbj1, TypSymbol* symbj2,char* nomJ1, char* nomJ2);
int receptionCoup(int sockTrans1, int sockTrans2);
int TraitementCoup(TypCoupReq coup, int sockTrans1, int sockTrans2);
int envoyerTempsDepasser(int sockTrans1, int sockTrans2);
void decoderCoup(TypCoupReq coup);

#endif