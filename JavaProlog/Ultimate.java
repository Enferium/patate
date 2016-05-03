
public class Ultimate {
	Morpion ultimate[][];
	private boolean verif;
	
	public Ultimate(){
		ultimate = new Morpion[3][3];
		verif = false;
		for (int i = 0; i < ultimate.length; i++) {
			for (int j = 0; j < ultimate.length; j++) {
				ultimate[i][j] = new Morpion();
			}
		}
	}
	
	
	public void verif(){
		for (int i = 0; i < ultimate.length; i++) {
			if(ultimate[i][0].getVerif() == ultimate[i][1].getVerif() &&
					ultimate[i][0].getVerif() == ultimate[i][2].getVerif() &&
					ultimate[i][0].getVerif() == true){
				verif = true;
			}
		}
		for (int i = 0; i < ultimate.length; i++) {
			if(ultimate[0][i].getVerif() == ultimate[1][i].getVerif() &&
					ultimate[0][i].getVerif() == ultimate[2][i].getVerif() &&
					ultimate[0][i].getVerif() == true){
				verif = true;
			}
		}
		
		if(ultimate[0][0].getVerif() == ultimate[1][1].getVerif() &&
				ultimate[0][0].getVerif() == ultimate[2][2].getVerif() &&
				ultimate[0][0].getVerif() == true){
			verif = true;
		}
		
		if(ultimate[0][2].getVerif() == ultimate[1][1].getVerif() &&
				ultimate[0][2].getVerif() == ultimate[2][0].getVerif() &&
				ultimate[0][2].getVerif() == true){
			verif = true;
		}
		
	}
	
	public Morpion getMorpion(int x, int y){
		return ultimate[x][y];
	}
	
	public boolean getVerif(){
		return verif;
	}
	
	
	public String toString(){
		
		for (int i = 0; i < ultimate.length; i++) {
			for (int j = 0; j < ultimate.length; j++) {
				System.out.println(ultimate[i][j].toString());
			}
			System.out.println();
		}		
		return "";
	}
}
