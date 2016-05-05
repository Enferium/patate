
public class Player {
	String name;
	int nbSousPlateauGagne;
	
	public Player(){
		this.name = "";
		nbSousPlateauGagne = 0;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getNb() {
		return nbSousPlateauGagne;
	}

	public void setNb(int nb) {
		this.nbSousPlateauGagne = nb;
	}
}
