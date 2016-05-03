
public class Case {

	Player player;
	
	public Case(){
		player = null;
	}
	
	public boolean estLibre(){
		if (player == null){
			return true;
		}else{
			return false;
		}
	}
	
	public Player getPlayer(){
		return player;
	}
	
	public void setPlayer(Player player){
		this.player = player;
	}
}
