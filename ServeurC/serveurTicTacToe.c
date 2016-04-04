#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

#include "fonctionsTCP.h"
#include "protocoleTicTacToe.h"
#include "fonctionServeur.c"
/* taille du buffer de reception */

int main(int argc, char** argv) {

  int sockConx;        /* descripteur socket connexion */
  int sockTransJ1;
  int sockTransJ2;       /* descripteur socket transmission */
  int port;            /* numero de port */
  int err;        /* code d'erreur */

/*
* verification des arguments
*/
if (argc != 2) {
  printf ("usage : serveurTicTacToe no_port\n");
  return -1;
}

port  = atoi(argv[1]);

sockConx = socketServeur(port);
if (sockConx < 0) {
  printf("Erreur démarrage serveur !\n");
}

connexionJoueur(&sockTransJ1, sockConx);
connexionJoueur(&sockTransJ2, sockConx);

demandePartie(sockConx, sockTransJ1, sockTransJ2);

/* 
* arret de la connexion et fermeture
*/
close(sockConx);

return 0;
}