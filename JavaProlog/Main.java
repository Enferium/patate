public class Main {

	public static void main(String[] args) {
		
		SocketLocale sock1 = new SocketLocale(5555);
		SocketLocale sock2 = new SocketLocale(6666);
		sock1.start();
		sock2.start();
		
	}

}