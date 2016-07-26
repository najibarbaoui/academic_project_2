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
	 * Fonction qui initialise un contexte OpenGL dans la fen�tre identifi�e par
	 * le canvas AWT pass� en param�tre. Cette fonction doit �tre la premi�re �
	 * �tre appel�e, car la cr�ation de l'objet du mod�le C++ s'attend � avoir
	 * un contexte OpenGL valide.
	 * 
	 * @param canvas
	 *            Le canvas dans lequel cr�er le contexte OpenGL.
	 */
	public static native void fctC_initialiserOpenGL(Canvas canvas);

	/**
	 * Fonction qui lib�re le contexte OpenGL dans la fen�tre identifi�e par le
	 * canvas AWT pass� en param�tre. Cette fonction doit �tre la derni�re �
	 * �tre appel�e, car elle lib�re �galement l'objet du mod�le C++.
	 * 
	 * @param canvas
	 *            Le canvas dans lequel cr�er le contexte OpenGL.
	 */
	public static native void fctC_libererOpenGL(Canvas canvas);

	/**
	 * Fonction qui affiche la sc�ne dans la fen�tre identifi�e par le canvas
	 * AWT pass� en param�tre.
	 * 
	 * @param canvas
	 *            Le canvas dans lequel cr�er le contexte OpenGL.
	 */
	public static native void fctC_dessinerOpenGL(Canvas canvas);

	/**
	 * Fonction qui doit �tre appel�e lorsque la fen�tre est redimensionn�e afin
	 * d'ajuster les param�tres de la machine � �tats d'OpenGL pour correspondre
	 * aux nouvelles dimensions de la fen�tre.
	 * 
	 * @param largeur
	 *            La nouvelle largeur de la fen�tre.
	 * @param hauteur
	 *            La nouvelle hauteur de la fen�tre.
	 */
	public static native void fctC_redimensionnerFenetre(int largeur,
			int hauteur);

	/**
	 * Fonction qui anime le jeu d'un certain intervalle de temps.
	 * 
	 * Elle vise � �tre appel�e de nombreuses fois par seconde. Elle effectue
	 * les diff�rents calculs de physique et effectue un affichage.
	 * 
	 * @param temps
	 *            L'intervalle de temps � utiliser pour les diff�rents calculs.
	 *            On vise � faire correspondre cet invervalle de temps au temps
	 *            entre deux appels � la fonction.
	 */
	public static native void fctC_animer(float temps);

	/**
	 * Fonction qui applique un zoom avant sur le pr�sent volume de vision.
	 */
	public static native void fctC_zoomIn();

	/**
	 * Fonction qui applique un zoom arri�re sur le pr�sent volume de vision.
	 */
	public static native void fctC_zoomOut();

	/**
	 * Fonction qui retourne le nombre moyen d'affichage par secondes.
	 */
	public static native int obtenirAffichagesParSeconde();

	/**
	 * Fonction qui retourne l'identifiant de l'�tat action.
	 */
	public static native int fctC_obtenirEtatActionId();

	/**
	 * Fonction qui ex�cute les jeux de tests unitaires C++.
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
	 * Fonction qui ouvre le niveau dans le fichier sp�cifi�.
	 */
	public static native boolean fctC_ouvrirFichier(String filePath);

	/**
	 * Fonction qui sauvegarde le niveau dans le fichier sp�cifi�.
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
