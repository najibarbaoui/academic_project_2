package ca.polymtl.inf2990.gestionnaires;

import java.awt.BorderLayout;
import java.awt.Canvas;
import java.awt.Color;
import java.awt.Dimension;
import ca.polymtl.inf2990.composants.Fenetre;
import ca.polymtl.inf2990.vue.editeur.EditeurVue;
import ca.polymtl.inf2990.vue.jeu.ModeJeuVue;
import ca.polymtl.inf2990.vue.menu.MenuVue;
//import ca.polymtl.inf2990.vue.modeScoreVue.ModeScoreVue;
import ca.polymtl.inf2990.vue.modetest.ModeTestVue;
import ca.polymtl.inf2990.vue.partie_rapide.PartieRapideVue;
import ca.polymtl.inf2990.vue.campagne.Campagne;
import ca.polymtl.inf2990.vues.Vue;

import javax.swing.JFrame;

import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.JOptionPane;

import ca.polymtl.inf2990.configuration.test1;
import ca.polymtl.inf2990.cpp.FacadeCpp;
public class GestionnaireDeVue {
	Fenetre fenetrePrincipale;
	GestionnaireEvenement ge;
	test1 config;
	Canvas canvas;
	MenuVue menuVue = null;
	public enum TypesVue {
		MENU, EDITEUR, JEU, CONFIGURATION, MODETEST, PARTIERAPIDE, CAMPAGNE
	}

	public GestionnaireDeVue(Fenetre fenetre) {
		// Initialise le gestionnaire d'évènements
		ge = new GestionnaireEvenement(this);

		// Assigne la fenetre principale
		this.fenetrePrincipale = fenetre;

		// Lorsque l'on clique sur X, ou File->close, on veut quitter
		fenetrePrincipale.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {
				int result = JOptionPane.showConfirmDialog(fenetrePrincipale, "Voulez vous vraiment quitter?", "Confirmer la fermeture", JOptionPane.YES_NO_OPTION);
				if (result == JOptionPane.YES_OPTION) {
					fenetrePrincipale.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				} else if (result == JOptionPane.NO_OPTION) {
					fenetrePrincipale.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
				}  
			}
		});

		// Création du canvas
		canvas = CreerCanvas();

		// Préparer le canvas pour le contexte opengl
		// Il sera initialisé à l'ouverture des modes qui en ont besoin
		PreparerCanvas();

		// Charger la vue Menu au départ
		ChargerVue(CreerVue(TypesVue.MENU));
	}

	public void ChangerVue(TypesVue typeVue) {
		if(typeVue == TypesVue.CONFIGURATION) {
			this.fenetrePrincipale.setVisible(false);
			config = new test1(fenetrePrincipale);
		} else {
			Vue nouvelleVue = CreerVue(typeVue);
			ChargerVue(nouvelleVue);
		}
	}

	public Fenetre getFenetre() {
		return fenetrePrincipale;
	}

	public Vue getCurrentVue() {
		return fenetrePrincipale.getVue();
	}

	private Canvas CreerCanvas() {
		Canvas c = new Canvas();
		c.setBackground(Color.BLACK);
		c.setPreferredSize(new Dimension(500, 500));

		return c;
	}
	private void PreparerCanvas() {
		fenetrePrincipale.add(canvas, BorderLayout.CENTER);

		fenetrePrincipale.pack();

		canvas.setVisible(false);

		// Ajouter le gestionnaire d'évènements aux actions des composants
		canvas.addMouseListener(ge);
		canvas.addMouseMotionListener(ge);
		canvas.addMouseWheelListener(ge);
		canvas.addKeyListener(ge);

		fenetrePrincipale.addComponentListener(ge);
		fenetrePrincipale.setFocusable(true);
		fenetrePrincipale.addKeyListener(ge);
		fenetrePrincipale.getContentPane().addKeyListener(ge);
		
		// Ajout d'un gestionnaire pour la redimension.
		canvas.addComponentListener(new ComponentAdapter() {
	         public void componentResized(ComponentEvent evenement) {
	            FacadeCpp.fctC_redimensionnerFenetre(canvas.getWidth(), canvas.getHeight());
	         }
	      });
	}

	private Vue CreerVue(TypesVue typeMenu) {
		Vue vue = null;

		switch (typeMenu) {
		case MENU:
			vue = new MenuVue(fenetrePrincipale, ge);
			menuVue = (MenuVue) vue;
			break;
		case EDITEUR:
			vue = new EditeurVue(fenetrePrincipale, ge, canvas);
			break;
		case JEU:
			vue = new ModeJeuVue(fenetrePrincipale, ge, canvas);
			break;
		case MODETEST:
			vue = new ModeTestVue(fenetrePrincipale, ge, canvas);
			break;
		case PARTIERAPIDE:
			vue = new PartieRapideVue(fenetrePrincipale, ge);
			break;
		case CAMPAGNE:
			vue = new Campagne(fenetrePrincipale, ge);
			break;
		default:
			vue = new MenuVue(fenetrePrincipale, ge);
			break;
		}

		return vue;
	}

	private void ChargerVue(Vue nouvelleVue) {
		// Assigner la nouvelle vue
		if (nouvelleVue.getTypeVue() == TypesVue.MODETEST)
		{
			((EditeurVue)fenetrePrincipale.getVue()).HideEditorComponents();
		}
		else if (nouvelleVue.getTypeVue() == TypesVue.EDITEUR && fenetrePrincipale.getVue().getTypeVue() == TypesVue.EDITEUR)
		{
			((EditeurVue)fenetrePrincipale.getVue()).ShowEditorComponents();
		}
		else if (nouvelleVue.getTypeVue() == TypesVue.JEU && fenetrePrincipale.getVue().getTypeVue() == TypesVue.JEU)
		{
			((ModeJeuVue)fenetrePrincipale.getVue()).ActiverVue();
		}
		else
		{
			// Détruire l'ancienne vue
			if (fenetrePrincipale.getVue() != null)
				fenetrePrincipale.getVue().DetruireVue();


			fenetrePrincipale.setVue(nouvelleVue);

			nouvelleVue.setProprietesFenetre();

			// Activer la vue s'il y a lieu
			nouvelleVue.ActiverVue();
		}

		// Centrer la fenêtre
		fenetrePrincipale.setLocationRelativeTo(null);

		// Assigner la barre de menu
		fenetrePrincipale.setJMenuBar(nouvelleVue.construireMenu());
	}

}
