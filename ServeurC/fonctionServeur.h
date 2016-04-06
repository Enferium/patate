#ifndef _fonctionServeur_h
#define _fonctionServeur_h

int connexionJoueur(int* sockTrans, int sockConx);
int demandePartie(int sockTransJ1, int sockTransJ2,TypSymbol* symbj1, TypSymbol* symbj2);
int receptionCoup(int sockTrans1, int sockTrans2);
int TraitementCoup(TypCoupReq coup, int sockTrans1, int sockTrans2);
void decoderCoup(TypCoupReq coup);

#endif