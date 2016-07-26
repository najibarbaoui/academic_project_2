package ca.polymtl.inf2990;

import java.awt.BorderLayout;
import java.io.File;

import javax.swing.WindowConstants;

import ca.polymtl.inf2990.composants.Fenetre;
import ca.polymtl.inf2990.cpp.FacadeCpp;
import ca.polymtl.inf2990.gestionnaires.GestionnaireDeVue;

public class Main {
	static Fenetre fenetrePrincipale;
	static GestionnaireDeVue gv;

	public static void main(String[] args) {
		// Vérifier si nous exécuterons les tests unitaires...
		if (args.length >= 1 && args[0].equals("testsC++")) {
			// Exécution des tests C++
			int resultat = FacadeCpp.fctC_executerTests();
			System.exit(resultat);
		}
		// Pas d'exécution des tests unitaires, crééons la fenêtre et
		// affichons-là
		else {
			CreerDossierZones();

			// Créer la fenêtre
			fenetrePrincipale = new Fenetre();

			fenetrePrincipale.setTitle("INF2990");
			fenetrePrincipale.setVisible(true);
			fenetrePrincipale
					.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

			fenetrePrincipale.setLayout(new BorderLayout());

			// Créer le gestionnaire de vue
			gv = new GestionnaireDeVue(fenetrePrincipale);
		}
	}
	
	private static void CreerDossierZones() {
		File theDir = new File("zones");

		// if the directory does not exist, create it
		if (!theDir.exists()) {
			System.out.println("creating directory: "
					+ theDir.getAbsolutePath());
			boolean result = theDir.mkdir();

			if (result) {
				System.out.println("DIR created");
			}
		}
	}
}
