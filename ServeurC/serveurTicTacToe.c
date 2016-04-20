#include "fonctionServeur.c"
/* taille du buffer de reception */

int main(int argc, char** argv) {

  int sockConx;        /* descripteur socket connexion */
  int sockTransJ1;
  int sockTransJ2;       /* descripteur socket transmission */
  int port;            /* numero de port */
  TypSymbol symbJ1;
  TypSymbol symbJ2;
  
  bool tmpDepasser = false;

  char nomJ1[MAX_CH];
  char nomJ2[MAX_CH];

 typedef struct
   {
   char nom[MAX_CH];
   int socket;
   TypSymbol symbol;
   }TypJoueur;

   TypJoueur joueurActif;
   TypJoueur joueurInactif;
   TypJoueur joueurTmp;

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

demandePartie(sockTransJ1, sockTransJ2,&symbJ1,&symbJ2,nomJ1,nomJ2);

if(symbJ1 == CROIX){
	joueurActif.socket = sockTransJ1;
  strcpy(joueurActif.nom,nomJ1);
  joueurActif.symbol = symbJ1;
	joueurInactif.socket = sockTransJ2;
  strcpy(joueurActif.nom,nomJ2);
  joueurInactif.symbol = symbJ2;
}else{
	joueurActif.socket = sockTransJ2;
  strcpy(joueurActif.nom,nomJ2);
  joueurActif.symbol = symbJ2;
  joueurInactif.socket = sockTransJ1;
  strcpy(joueurActif.nom,nomJ1);
  joueurInactif.symbol = symbJ1;
}
int i=0;
while(i<10 && tmpDepasser == false){
	printf("Coup n°:  %d\n",i );
	if(receptionCoup(joueurActif.socket,joueurInactif.socket) == 0){
    tmpDepasser = true;
    envoyerTempsDepasser(joueurActif.socket,joueurInactif.socket);
  }

	joueurTmp = joueurInactif;
	joueurInactif = joueurActif;
	joueurActif = joueurTmp;

	i++;
}

printf("JOUEUR GAGNANT %s\n",joueurInactif.nom);
printf("JOUEUR PERDANT %s\n",joueurActif.nom );

/* 
* arret de la connexion et fermeture
*/
printf("ARBITRE : Fermeture du serveur\n");
close(sockConx);

return 0;
}