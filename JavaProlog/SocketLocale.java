import java.net.* ;
import java.io.* ;

class SocketLocale extends Thread {

	Socket connectionSocket;
	boolean isConnected = false;

	public SocketLocale(int numPort) {
		try {
			ServerSocket welcomeSocket = new ServerSocket(numPort);
			connectionSocket = welcomeSocket.accept();
			System.out.println(getName() + " welcomeSocket.accept() called");
			isConnected = true;
		} catch (IOException e) {
			System.out.println(getName() + " CONNECTION");
			e.printStackTrace();
		}
	}

	public void run() {

		try {

			while (true) {
				if (isConnected) {
					DataInputStream inToClient = new DataInputStream(connectionSocket.getInputStream());
					if (inToClient.read() == 10) {
						System.out.println("Demande de coup : " + getName());
						DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());

						// Premier int = NUM PLATEAU
						outToClient.writeInt(5);
						// NUM SOUS PLATEAU
						outToClient.writeInt(5);
						// Coup envoyé E CINQ
						outToClient.close();
					}
					inToClient.close();
				}
			}	
						
		} catch (IOException e) {
			System.out.println(getName() + " RECEPTION 10");
			e.printStackTrace();
		}
  	}
}