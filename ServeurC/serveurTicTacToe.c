#include "fonctionServeur.c"
/* taille du buffer de reception */

int main(int argc, char** argv) {

  int sockConx;        /* descripteur socket connexion */
  int sockTransJ1;
  int sockTransJ2;       /* descripteur socket transmission */
  int port;            /* numero de port */
  TypSymbol symbJ1;
  TypSymbol symbJ2;
  int joueurActif;
  int joueurInactif;
  int joueurTmp;
  bool tmpDepasser = false;

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
  printf("/!\\Erreur démarrage serveur !\n");
}

connexionJoueur(&sockTransJ1, sockConx);
connexionJoueur(&sockTransJ2, sockConx);

demandePartie(sockTransJ1, sockTransJ2,&symbJ1,&symbJ2);

if(symbJ1 == CROIX){
	joueurActif = sockTransJ1;
	joueurInactif = sockTransJ2;
}else{
	joueurActif = sockTransJ2;
	joueurInactif = sockTransJ1;
}
int i=0;
while(i<10 && tmpDepasser == false){
	printf("Coup n0:  %d\n",i );
	if(receptionCoup(joueurActif,joueurInactif) == 0){
    tmpDepasser = true;
  }

	joueurTmp = joueurInactif;
	joueurInactif = joueurActif;
	joueurActif = joueurTmp;

	i++;
}
/* 
* arret de la connexion et fermeture
*/
printf("ARBITRE : Fermeture du serveur\n");
close(sockConx);

return 0;
}