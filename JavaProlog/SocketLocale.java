import java.net.* ;
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
			while (true) {
				if (isConnected) {
					if (inToClient.read() == 10) {
						System.out.println("Demande de coup : " + getName());
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