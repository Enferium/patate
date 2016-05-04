import java.net.* ;

import javax.sound.sampled.ReverbType;

import java.io.* ;

class SocketLocale extends Thread {

	Socket connectionSocket;
	boolean isConnected = false;

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
					System.out.println("blabla2");

					System.out.println("a "+joueur);
					System.out.println("b "+ sousPlateau);
					System.out.println("c "+ casePlateau);


					
					if (joueur == 1) {
						String symboleJoueur = "x";
						System.out.println("Demande de coup : " + getName());
						
						//int coup = jSictus.demandeCoupProlog(symboleJoueur,casePlateau);
						
						// Premier int = NUM PLATEAU
						outToClient.writeInt(2);
						// NUM SOUS PLATEAU
						outToClient.writeInt(2);
						// Coup envoyé E CINQ
						outToClient.flush();
					
					} else if (joueur == 0) {
						String symboleJoueur = "o";
						System.out.println("Demande de coup : " + getName());
						
						int coup = jSictus.demandeCoupProlog(symboleJoueur,casePlateau);
						
						// Premier int = NUM PLATEAU
						outToClient.writeInt(2);
						// NUM SOUS PLATEAU
						outToClient.writeInt(2);
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
}
