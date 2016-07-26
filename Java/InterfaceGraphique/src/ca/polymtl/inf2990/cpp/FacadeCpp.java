package ca.polymtl.inf2990.cpp;

import java.awt.Canvas;

import ca.polymtl.inf2990.modele.ProprietesJeu;
//import ca.polymtl.inf2990.modele.ProprietesJeu;
import ca.polymtl.inf2990.modele.ProprietesNoeud;

public class FacadeCpp {

	public enum EtatModele {
		MENU, EDITEUR, JEU, CONFIGURATION, MODETEST, PARTIERAPIDE, CAMPAGNE
	}

	/**
	 * Initialisation statique de la classe qui charge la librairie C++
	 * contenant l'implantation des fonctions natives.
	 */
	static {
		System.loadLibrary("DLL/INF2990");
	}

	/**
	 * Fonction qui initialise un contexte OpenGL dans la fenêtre identifiée par
	 * le canvas AWT passé en paramètre. Cette fonction doit être la première à
	 * être appelée, car la création de l'objet du modèle C++ s'attend à avoir
	 * un contexte OpenGL valide.
	 * 
	 * @param canvas
	 *            Le canvas dans lequel créer le contexte OpenGL.
	 */
	public static native void fctC_initialiserOpenGL(Canvas canvas);

	/**
	 * Fonction qui libère le contexte OpenGL dans la fenêtre identifiée par le
	 * canvas AWT passé en paramètre. Cette fonction doit être la dernière à
	 * être appelée, car elle libère également l'objet du modèle C++.
	 * 
	 * @param canvas
	 *            Le canvas dans lequel créer le contexte OpenGL.
	 */
	public static native void fctC_libererOpenGL(Canvas canvas);

	/**
	 * Fonction qui affiche la scène dans la fenêtre identifiée par le canvas
	 * AWT passé en paramètre.
	 * 
	 * @param canvas
	 *            Le canvas dans lequel créer le contexte OpenGL.
	 */
	public static native void fctC_dessinerOpenGL(Canvas canvas);

	/**
	 * Fonction qui doit être appelée lorsque la fenêtre est redimensionnée afin
	 * d'ajuster les paramètres de la machine à états d'OpenGL pour correspondre
	 * aux nouvelles dimensions de la fenêtre.
	 * 
	 * @param largeur
	 *            La nouvelle largeur de la fenêtre.
	 * @param hauteur
	 *            La nouvelle hauteur de la fenêtre.
	 */
	public static native void fctC_redimensionnerFenetre(int largeur,
			int hauteur);

	/**
	 * Fonction qui anime le jeu d'un certain intervalle de temps.
	 * 
	 * Elle vise à être appelée de nombreuses fois par seconde. Elle effectue
	 * les différents calculs de physique et effectue un affichage.
	 * 
	 * @param temps
	 *            L'intervalle de temps à utiliser pour les différents calculs.
	 *            On vise à faire correspondre cet invervalle de temps au temps
	 *            entre deux appels à la fonction.
	 */
	public static native void fctC_animer(float temps);

	/**
	 * Fonction qui applique un zoom avant sur le présent volume de vision.
	 */
	public static native void fctC_zoomIn();

	/**
	 * Fonction qui applique un zoom arrière sur le présent volume de vision.
	 */
	public static native void fctC_zoomOut();

	/**
	 * Fonction qui retourne le nombre moyen d'affichage par secondes.
	 */
	public static native int obtenirAffichagesParSeconde();

	/**
	 * Fonction qui retourne l'identifiant de l'état action.
	 */
	public static native int fctC_obtenirEtatActionId();

	/**
	 * Fonction qui exécute les jeux de tests unitaires C++.
	 */
	public static native int fctC_executerTests();

	public static native void fctC_mouseMoved(int x, int y,
			boolean ctrlPressed, boolean altPressed);

	public static native void fctC_mousePressed(int x, int y, int button,
			boolean ctrlPressed, boolean altPressed);

	public static native void fctC_mouseClicked(int x, int y, int button,
			boolean ctrlPressed, boolean altPressed);

	public static native void fctC_mouseDragged(int x, int y, int dx, int dy,
			boolean ctrlPressed, boolean altPressed);

	public static native void fctC_mouseReleased(int x, int y, int button,
			boolean ctrlPressed, boolean altPressed);

	public static native void keyPressed(int keyCode);

	public static native void keyReleased(int keyCode);

	public static native void fctC_buttonPressed(String action);

	public static native int fctC_obtenirEtat();

	public static native void fctC_changerEtat(int etat);

	/**
	 * Fonction qui ouvre le niveau dans le fichier spécifié.
	 */
	public static native boolean fctC_ouvrirFichier(String filePath);

	/**
	 * Fonction qui sauvegarde le niveau dans le fichier spécifié.
	 */
	public static native boolean fctC_sauvegarderFichier(String filePath);

	public static native boolean fctC_fichierSauvegardeEstDefini();

	public static native String fctC_obtenirNomFichierSauvegarde();
	
	public static native ProprietesNoeud fctC_obtenirSeulNoeudSelectionne();

	public static native ProprietesJeu fctC_obtenirProprietesJeu();

	public static native void fctC_modifierSeulNoeudSelectionne(
			ProprietesNoeud noeudSelectionne);

	public static native void fctC_modifierProprietesJeu(
			ProprietesJeu proprietesJeu);

	public static native void fctC_move(int direction);
	
	public static native boolean fctC_getIsGagne();
	
	public static native boolean fctC_isTermine();
	
	public static native void fctC_obtenirOptionDebogage(
			boolean bAfficheDebug,
			boolean bApparitionAsteroid, 
			boolean bChangementJoueurVirtuel,
			boolean bEclairage,
			boolean bCible,
			boolean bCadreDepart,
			boolean bZonePassage,
			boolean bLimiteAttractionPortails
			);
	
	public static native void fctC_obtenirControles(
			int avancer_j1,
			int demitour_j1,
			int droite_j1,
			int gauche_j1,
			int tir_j1,
			int avancer_j2,
			int demitour_j2,
			int droite_j2,
			int gauche_j2,
			int tir_j2
			);
	
	public static native void fctC_obtenirInfoPartie(
			int duree,
			int ptvie
			);

	public static native void fctC_activerVuePerspective();
	
	public static native void fctC_activerVueOrthogonale();
}
