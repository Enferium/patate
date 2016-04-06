import java.net.Socket; import java.net.ServerSocket;
import java.io.*;
import java.util.*;

public class SocketLocale {

	public static void main(String[] args) {

		try {
			ServerSocket socketServeur = new ServerSocket(8080);
			Socket sockComm = socketServeur.accept();
			System.out.println("Socket Locale : Client c connecté");

			InputStream is = sockComm.getInputStream();
			OutputStream os = sockComm.getOutputStream();

            while (is.read() == 10) {
            	System.out.println("Demande de coup OK");
            	// On consulte le prolog pour avoir un coup

            	// On envoit le coup
            	System.out.println("Coup : " + 2 + " " + 1);
        		os.write(2);
        		os.write(1);
        		
            }

            socketServeur.close();
		
		} catch(IOException e) {
			e.printStackTrace();
		}

	}

}
