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
			DataInputStream inToClient = new DataInputStream(connectionSocket.getInputStream());
			DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());
			
			BufferedReader bis = new BufferedReader(new 
			InputStreamReader(connectionSocket.getInputStream()));
			String inputLine;
			
			while (true) {
				if (isConnected) {
					String results = "";
					String joueur = "";
					String sousPlateau = "";
					String casePlateau = "";
					
					while ((inputLine = bis.readLine()) != null) {
					      results += inputLine;    
					}
					
					String[] recvSplit = results.split(",");
					joueur = recvSplit[0];
					sousPlateau = recvSplit[1];
					casePlateau = recvSplit[2];
					
					
					if (joueur == "1") {
						String symboleJoueur = "x";
						System.out.println("Demande de coup : " + getName());
						
						int coup = jSictus.demandeCoupProlog(symboleJoueur,casePlateau);
						
						// Premier int = NUM PLATEAU
						outToClient.writeInt(2);
						// NUM SOUS PLATEAU
						outToClient.writeInt(2);
						// Coup envoyé E CINQ
						outToClient.flush();
					
					} else if (joueur == "0") {
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
