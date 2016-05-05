// importation des classes utiles a Jasper
import se.sics.jasper.*;
// pour utiliser les HashMap 
import java.util.*;

public class jSictus {

	
    /*public static void main(String[] args) {
    	int coup = demandeCoupProlog("minimax(5,x,[0,0,0,0,0,0,0,0,0],Sol).");
    	System.out.println(coup);
    }
    */
    public static SICStus sp = null;

    public jSictus(){

        try {
            // Creation d'un object SICStus
            sp = new SICStus();

            // Chargement d'un fichier prolog .pl
            sp.load("alpha_beta.pl");
            System.out.println("LOAD EFFECT UYAYAYAYAYAYA");
        }
        // exception declanchee par SICStus lors de la creation de l'objet sp
        catch (SPException e) {
            System.err.println("Exception SICStus Prolog : " + e);
            e.printStackTrace();
            System.exit(-2);
        }
    }

    
    public static int demandeCoupProlog(String symbole,Morpion morpion) {
    	
    	String predicat = construitPredicat(symbole, morpion);
        System.out.println(predicat);
    	
    	String saisie = predicat;
    	int sol = 0;
    	// HashMap utilise pour stocker les solutions
		HashMap<String, SPTerm> results = new HashMap<String, SPTerm>();
    	
    	

    	// boucle pour saisir les informations 
    	if (! saisie.equals("halt.")) {
    
    		try {
    			Query qu = sp.openQuery(saisie,results);

    			// parcours des solutions
    			boolean moreSols = qu.nextSolution();

    			if (moreSols) {
       				sol = Integer.parseInt(results.get("Sol").toString());
    			}
    			
    			qu.close();

    		}
    		catch (SPException e) {
    			System.err.println("Exception prolog\n" + e);
    		}
    		catch (Exception e) {
    			System.err.println("Other exception : " + e);
    		}

    	}
    
		return sol;
    }
    
    public static String construitPredicat(String symbole,Morpion morpion) {
		// minimax(5,x,[1,0,-1,0,0,0,1,1]).
    	String predicat = "minimax(5,";
		predicat += symbole+",";
		
		String plateau = "[";
		for (int i = 0; i < morpion.grille.length; i++) {
			for (int j = 0; j < morpion.grille.length; j++) {
				if(morpion.grille[i][j].getPlayer() == null){
					plateau += "0,";
				}else{
					if (morpion.grille[i][j].getPlayer().getName() == symbole) {
						plateau += "1,";
					} else {
						plateau += "-1,";
					}
				}				
			}
		}
		return predicat+=plateau.substring(0,plateau.length()-1)+"],Sol).";
    }

    @Override
    protected void finalize() throws Throwable{
        super.finalize();
    }
}