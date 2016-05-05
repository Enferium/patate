import java.io.* ;
import java.net.* ;


public class Main {



	public static void main(String[] args) {

		Socket connectionSocket = null;
		boolean isConnected = false;
		Ultimate ultimate = new Ultimate();
		Player nous = new Player();
		Player adv = new Player();
		jSictus jsp = new jSictus();

		try {
			ServerSocket welcomeSocket = new ServerSocket(Integer.parseInt(args[0]));
			connectionSocket = welcomeSocket.accept();
			isConnected = true;
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		try {
			DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());
			DataInputStream inToClient = new DataInputStream(connectionSocket.getInputStream());

			String inputLine;
			boolean isFirstPlay = true;
			while (true) {
				if (isConnected) {
					int joueur = inToClient.readInt();
					int sousPlateau = inToClient.readInt();
					int casePlateau = inToClient.readInt();
					if (joueur == 1) {
						nous.setName("x");
						adv.setName("o");
						
						Morpion sousPlateauDansLequelOnVaJouer;
						int indiceDuSousPlateauDansLequelOnVaJouer = 0;

						int ligne = 0;
						int colonne = 0;
						String symboleJoueur = "x";

						Morpion m;

						// MAJ MORPION JAVA ADV
						if(!isFirstPlay){
							m = ultimate.getMorpion(getLigne(sousPlateau), getColonne(sousPlateau));
							m.jouerCoup(adv, getLigne(casePlateau), getColonne(casePlateau));
							
							// NOTRE COUP
							// Par defaut on jouera dans le sous plateau qui correspond a la case plateau de l'adv
							sousPlateauDansLequelOnVaJouer = ultimate.getMorpion(getLigne(casePlateau), getColonne(casePlateau));
							
							m = ultimate.getMorpion(getLigne(casePlateau), getColonne(casePlateau));
							m.verif();

							if (m.verif) {
								// On cherche un autre sousPlateau qui n'est pas plein
								for (int i = 0; i < 3; i++) {
									for (int j = 0; j < 3; j++) {
										m = ultimate.getMorpion(i, j);
										m.verif();
										if (!m.verif) {
											sousPlateauDansLequelOnVaJouer = m;
											ligne = i;
											colonne = j;
										}
									}
								}
								indiceDuSousPlateauDansLequelOnVaJouer = getNumCase(ligne,colonne);
							} else {
								indiceDuSousPlateauDansLequelOnVaJouer = casePlateau;
							}
						} else {
							int r1 = 0+(int)(Math.random()*3);
							int r2 = 0+(int)(Math.random()*3);
							sousPlateauDansLequelOnVaJouer = ultimate.getMorpion(r1,r2);
							indiceDuSousPlateauDansLequelOnVaJouer = (r1+1) * (r2+1);
							isFirstPlay = false;
						}

						
						
						int coup = jsp.demandeCoupProlog(symboleJoueur,sousPlateauDansLequelOnVaJouer);
						
						m = ultimate.getMorpion(getLigne(indiceDuSousPlateauDansLequelOnVaJouer), getColonne(indiceDuSousPlateauDansLequelOnVaJouer));
						m.jouerCoup(nous, getLigne(coup), getColonne(coup));

						m.verif();
						if(m.verif == true){
							nous.setNb(nous.getNb() + 1);
						}

						// Premier int = NUM PLATEAU
						outToClient.writeInt(indiceDuSousPlateauDansLequelOnVaJouer);
						// NUM SOUS PLATEAU
						outToClient.writeInt(coup);

						outToClient.writeInt(nous.getNb());
						// Coup envoyé E CINQ
						outToClient.flush();

					} else if (joueur == 2) {
						nous.setName("o");
						adv.setName("x");
						
						// MAJ MORPION JAVA ADV
						Morpion m = ultimate.getMorpion(getLigne(sousPlateau), getColonne(sousPlateau));
						m.jouerCoup(adv, getLigne(casePlateau), getColonne(casePlateau));
						
						// NOTRE COUP
						// Par defaut on jouera dans le sous plateau qui correspond a la case plateau de l'adv
						Morpion sousPlateauDansLequelOnVaJouer = ultimate.getMorpion(getLigne(casePlateau), getColonne(casePlateau));
						String symboleJoueur = "o";

						int indiceDuSousPlateauDansLequelOnVaJouer = 0;
						
						m = ultimate.getMorpion(getLigne(casePlateau), getColonne(casePlateau));
						m.verif();
						int ligne = 0;
						int colonne = 0;
						if (m.verif) {
								// On cherche un autre sousPlateau qui n'est pas plein
								for (int i = 0; i < 3; i++) {
									for (int j = 0; j < 3; j++) {
										m = ultimate.getMorpion(i, j);
										m.verif();
										if (!m.verif) {
											sousPlateauDansLequelOnVaJouer = m;
											ligne = i;
											colonne = j;
										}
									}
								}


								indiceDuSousPlateauDansLequelOnVaJouer = getNumCase(ligne,colonne);
						} else {
							indiceDuSousPlateauDansLequelOnVaJouer = casePlateau;
						}
						
						
						int coup = jsp.demandeCoupProlog(symboleJoueur,sousPlateauDansLequelOnVaJouer);

						m = ultimate.getMorpion(getLigne(indiceDuSousPlateauDansLequelOnVaJouer), getColonne(indiceDuSousPlateauDansLequelOnVaJouer));
						m.jouerCoup(nous, getLigne(coup), getColonne(coup));


						m.verif();
						if(m.verif == true){
							nous.setNb(nous.getNb()+1);
						}
						
						// Premier int = NUM PLATEAU
						outToClient.writeInt(indiceDuSousPlateauDansLequelOnVaJouer);
						// NUM SOUS PLATEAU
						outToClient.writeInt(coup);

						outToClient.writeInt(nous.getNb());

						// Coup envoyé E CINQ
						outToClient.flush();
					}
				}
			}	

		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public static int getLigne(int SP) {
		int val = 0;
		if (SP <= 3)
			val = 0;
		if (SP > 3 && SP <= 6)
			val = 1;
		if (SP > 6)
			val = 2;
		return val;
	}
	
	public static int getColonne(int SP) {
		int val = 0;
		if (SP == 1 || SP == 4 || SP == 7)
			val = 0;
		if (SP == 2 || SP == 5 || SP == 8)
			val = 1;
		if (SP == 3 || SP == 6 || SP == 9)
			val = 2;
		return val;
	}

	public static int getNumCase(int ligne, int colonne){
		if(ligne == 0 && colonne == 0){
			return 1;
		}else if(ligne == 1 && colonne == 0){
			return 4;
		}else if(ligne == 2 && colonne == 0){
			return 7;
		}else if(ligne == 0 && colonne == 1){
			return 2;
		}else if(ligne == 1 && colonne == 1){
			return 5;
		}else if(ligne == 2 && colonne == 1){
			return 8;
		}else if(ligne == 0 && colonne == 2){
			return 3;
		}else if(ligne == 1 && colonne == 2){
			return 6;
		}else if(ligne == 2 && colonne == 2){
			return 9;
		}
		return 1;
	}
	
}