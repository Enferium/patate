import java.net.Socket; import java.net.ServerSocket;
import java.io.*;
import java.util.*;

public class SocketLocale {

	public static void main(String[] args) {

		try {
	
			Socket socket = new Socket("localhost" , 8080 );
        	DataOutputStream out = new DataOutputStream(socket.getOutputStream());
        	out.writeInt(2);
        	out.writeInt(1);
        	socket.close();
		
		} catch(IOException e) {}

	}

}
