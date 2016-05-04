import java.net.* ;

import javax.sound.sampled.ReverbType;

import java.io.* ;

class SocketLocale extends Thread {

	Socket connectionSocket;
	boolean isConnected = false;
	Ultimate ultimate = new Ultimate();
	Player nous = new Player();
	Player adv = new Player();

	public SocketLocale(int numPort) {
		try {
			ServerSocket welcomeSocket = new ServerSocket(numPort);
			connectionSocket = welcomeSocket.accept();
			System.out.println(getName() + " Un joueur s'est connecté");
			isConnected = true;
		} catch (IOException e) {
			System.out.println(getName() + " CONNECTION");
			e.printStackTrace();
		}
	}

	public void run() {

		try {
			System.out.println("blabla");
			DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());
			DataInputStream inToClient = new DataInputStream(connectionSocket.getInputStream());

			String inputLine;
			
			while (true) {
				if (isConnected) {
					int joueur = inToClient.readInt();
					int sousPlateau = inToClient.readInt();
					int casePlateau = inToClient.readInt();

					if (joueur == 1) {
						nous.setName("x");
						adv.setName("o");
						
						// MAJ MORPION JAVA ADV
						Morpion m = ultimate.getMorpion(getLigne(sousPlateau), getColonne(sousPlateau));
						m.jouerCoup(adv, getLigne(casePlateau), getColonne(casePlateau));
						
						// NOTRE COUP
						// Par defaut on jouera dans le sous plateau qui correspond a la case plateau de l'adv
						Morpion sousPlateauDansLequelOnVaJouer = ultimate.getMorpion(getLigne(casePlateau), getColonne(casePlateau));
						String symboleJoueur = "x";
						System.out.println("Demande de coup : " + getName());
						
						m = ultimate.getMorpion(getLigne(casePlateau), getColonne(casePlateau));
						m.verif();
						int ligne = 0;
						int colonne=0;
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
						}
						
						int indiceDuSousPlateauDansLequelOnVaJouer = (ligne+1)*(colonne+1);
						
						int coup = jSictus.demandeCoupProlog(symboleJoueur,sousPlateauDansLequelOnVaJouer);
						
						// Premier int = NUM PLATEAU
						outToClient.writeInt(indiceDuSousPlateauDansLequelOnVaJouer);
						// NUM SOUS PLATEAU
						outToClient.writeInt(coup);
						// Coup envoyé E CINQ
						outToClient.flush();
					
					} else if (joueur == 0) {
						nous.setName("o");
						adv.setName("x");
						
						// MAJ MORPION JAVA ADV
						Morpion m = ultimate.getMorpion(getLigne(sousPlateau), getColonne(sousPlateau));
						m.jouerCoup(adv, getLigne(casePlateau), getColonne(casePlateau));
						
						// NOTRE COUP
						// Par defaut on jouera dans le sous plateau qui correspond a la case plateau de l'adv
						Morpion sousPlateauDansLequelOnVaJouer = ultimate.getMorpion(getLigne(casePlateau), getColonne(casePlateau));
						String symboleJoueur = "x";
						System.out.println("Demande de coup : " + getName());
						
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
						}
						
						int indiceDuSousPlateauDansLequelOnVaJouer = (ligne+1)*(colonne+1);
						
						int coup = jSictus.demandeCoupProlog(symboleJoueur,sousPlateauDansLequelOnVaJouer);
						
						// Premier int = NUM PLATEAU
						outToClient.writeInt(indiceDuSousPlateauDansLequelOnVaJouer);
						// NUM SOUS PLATEAU
						outToClient.writeInt(coup);
						// Coup envoyé E CINQ
						outToClient.flush();
					}
				}
			}	
						
		} catch (IOException e) {
			System.out.println(getName() + " RECEPTION 10");
			e.printStackTrace();
		}
  	}
	
	public int getLigne(int SP) {
		int val = 0;
		if (SP <= 3)
			val = 0;
		if (SP > 3 && SP <= 6)
			val = 1;
		if (SP > 6)
			val = 2;
		return val;
	}
	
	public int getColonne(int SP) {
		int val = 0;
		if (SP == 1 || SP == 4 || SP == 7)
			val = 0;
		if (SP == 2 || SP == 5 || SP == 8)
			val = 1;
		if (SP == 3 || SP == 6 || SP == 9)
			val = 2;
		return val;
	}
	
}
