import java.util.Arrays;

public class Morpion {
	public Case[][] grille;
	boolean verif;
	boolean verifPlein;
	
	public Morpion(){
		grille = new Case[3][3];
		for (int i = 0; i < grille.length; i++) {
			for (int j = 0; j < grille.length; j++) {
				grille[i][j] = new Case();
			}
		}
		verif=false;
		verifPlein=false;
	}
	
	public void jouerCoup(Player player,int x, int y){
		Case c = getCase(x, y);
		if(c.estLibre()){
			c.setPlayer(player);
		}
	}
	
	public Case getCase(int x, int y){
		return grille[x][y];
	}
	
	public Case[][] getGrille(){
		return grille;
	}
	
	public boolean getVerif(){
		return verif;
	}
	
	public void verif(){
		for (int i = 0; i < grille.length; i++) {
			if(grille[i][0].getPlayer() == grille[i][1].getPlayer() &&
					grille[i][0].getPlayer() == grille[i][2].getPlayer() &&
					!grille[i][0].estLibre()){
				verif = true;
			}
		}
		for (int i = 0; i < grille.length; i++) {
			if(grille[0][i].getPlayer() == grille[1][i].getPlayer() &&
					grille[0][i].getPlayer() == grille[2][i].getPlayer() &&
					!grille[0][i].estLibre()){
				verif = true;
			}
		}
		
		if(grille[0][0].getPlayer() == grille[1][1].getPlayer() &&
				grille[0][0].getPlayer() == grille[2][2].getPlayer() &&
				!grille[0][0].estLibre()){
			verif = true;
		}
		
		if(grille[0][2].getPlayer() == grille[1][1].getPlayer() &&
				grille[0][2].getPlayer() == grille[2][0].getPlayer() &&
				!grille[0][2].estLibre()){
			verif = true;
		}
		
	}
	
	public void verifPlein(){
		if (!grille[0][0].estLibre() && !grille[0][1].estLibre() && !grille[0][2].estLibre() &&
				!grille[1][0].estLibre() && !grille[1][1].estLibre() && !grille[1][2].estLibre() &&
				!grille[2][0].estLibre() && !grille[2][1].estLibre() && !grille[2][2].estLibre()) {
			verifPlein = true;
		}
	}

	@Override
	public String toString() {
		for (int i = 0; i < grille.length; i++) {
			for (int j = 0; j < grille.length; j++) {
				if(grille[i][j].getPlayer() == null){
					System.out.print("n");
				}else{
					System.out.print(grille[i][j].getPlayer().getName());

				}
			}
			System.out.println();
		}
		return "";
	}
	
	
}
