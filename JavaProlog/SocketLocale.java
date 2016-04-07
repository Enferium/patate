import java.net.* ;
import java.io.* ;

class SocketLocale extends Thread {

	private int numPort;

	public SocketLocale(int numPort) {
		this.numPort = numPort;
	}

	public void run() {

		try {

			ServerSocket welcomeSocket = new ServerSocket(numPort);

			Socket connectionSocket = welcomeSocket.accept();
			System.out.println("welcomeSocket.accept() called");

			DataInputStream inToClient = new DataInputStream(connectionSocket.getInputStream());
			while (inToClient.read() == 10) {

				    DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());

				    // Premier int = NUM PLATEAU
				    outToClient.writeInt(5);
				    // NUM SOUS PLATEAU
				    outToClient.writeInt(5);
				    // Coup envoyé A DEUX
				    outToClient.close();
				    connectionSocket.close();

			}
			
			welcomeSocket.close();
			
		} catch (IOException e) {
			e.printStackTrace();
		}
  	}
}