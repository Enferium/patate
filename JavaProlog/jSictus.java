// importation des classes utiles à Jasper
import se.sics.jasper.*;
// pour utiliser les HashMap 
import java.util.*;

public class jSictus {

	
    /*public static void main(String[] args) {
    	int coup = demandeCoupProlog("minimax(5,x,[0,0,0,0,0,0,0,0,0],Sol).");
    	System.out.println(coup);
    }
    */
    
    public static int demandeCoupProlog(String symbole, String casePlateau) {
    	
    	String predicat = construitPredicat(symbole,casePlateau);
    	
    	String saisie = predicat;
    	SICStus sp = null;
    	int sol = 0;
    	// HashMap utilisé pour stocker les solutions
		HashMap<String, SPTerm> results = new HashMap<String, SPTerm>();
    	
    	try {
    		// Creation d'un object SICStus
    		sp = new SICStus();

    		// Chargement d'un fichier prolog .pl
    		sp.load("alpha_beta.pl");

    	}
    	// exception déclanchée par SICStus lors de la création de l'objet sp
    	catch (SPException e) {
    		System.err.println("Exception SICStus Prolog : " + e);
    		e.printStackTrace();
    		System.exit(-2);
    	}

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
    
    public static String construitPredicat(String symbole, String casePlateau) {
		
    	return casePlateau;
    }
}