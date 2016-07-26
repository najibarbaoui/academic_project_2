package ca.polymtl.inf2990.vue.editeur;

import java.awt.BorderLayout;
import java.awt.Canvas;
import java.awt.Dimension;
import java.lang.reflect.InvocationTargetException;
import java.util.Timer;
import java.util.TimerTask;

import javax.swing.JMenuBar;
import javax.swing.SwingUtilities;

import ca.polymtl.inf2990.composants.Fenetre;
import ca.polymtl.inf2990.cpp.FacadeCpp;
import ca.polymtl.inf2990.gestionnaires.GestionnaireEtatAction;
import ca.polymtl.inf2990.gestionnaires.GestionnaireEvenement;
import ca.polymtl.inf2990.gestionnaires.GestionnaireDeVue.TypesVue;
import ca.polymtl.inf2990.vue.jeu.ModeJeuVue;
import ca.polymtl.inf2990.vues.Vue;

public class EditeurVue extends Vue {
	private Boolean viewLoaded = false;
	private ModeJeuVue modeJeu;
	public Canvas canvas;
	// Minuterie qui gère l'affichage constant du context OpenGL
	Timer minuterie;
	// Le temps souhaité entre 2 affichages, en millisecondes.
	static private final int TEMPS_INTER_AFFICHAGE = 30;

	EditeurBarreOutils barreOutils;
	EditeurBarreProprietes barreProprietes;
	GestionnaireEtatAction gestionEtatAction;
	
	public EditeurVue(Fenetre fenetre,
			GestionnaireEvenement gestionnaireDEvenement, Canvas canvas) {
		super(fenetre, gestionnaireDEvenement);
		typeVue = TypesVue.EDITEUR;
		titreFenetre = "Éditeur - INF2990";
		largeurFenetre = 1600;
		hauteurFenetre = 900;

		this.canvas = canvas;
	}

	public void ActiverVue() {
		// Afficher le context OpenGL et activer la minuterie
		canvas.setVisible(true);
		this.activerMinuterie();
		viewLoaded = true;
	}

	public Boolean getviewLoadingStat() { return viewLoaded;}
	
	public void DetruireVue() {
		// Désactiver la minuterie et masquer le context OpenGL
		minuterie.cancel();
		canvas.setVisible(false);
		gestionnaireEvenement.deleteObserver(gestionEtatAction);
		viewLoaded = false;
	}

	private void activerMinuterie() {
		final float temps = TEMPS_INTER_AFFICHAGE / 1000.0f;

		minuterie = new Timer();
		minuterie.scheduleAtFixedRate(new TimerTask() {
			@Override
			public void run() {
				try {
					SwingUtilities.invokeAndWait(new Runnable() {
						public void run() {
							FacadeCpp.fctC_animer(temps);
							FacadeCpp.fctC_dessinerOpenGL(canvas);
						}
					});
				} catch (InvocationTargetException ex) {
					ex.printStackTrace();
				} catch (InterruptedException ex) {
					ex.printStackTrace();
				}
			}
		}, 0, TEMPS_INTER_AFFICHAGE);
	}

	public JMenuBar construireMenu() {
		return new EditeurMenu(gestionnaireEvenement);
	}

	
	@Override
	public void setProprietesFenetre() {
		// Affecter le titre de la fenêtre et sa taille à l'affichage
		fenetrePrincipale.setTitle(this.getTitreFenetre());
		fenetrePrincipale.setSize(this.getLargeurFenetre(),
				this.getHauteurFenetre());

		// Définir une taille minimale sur la fenêtre (Dimensions pour garder le
		// la barre de proprietes et la barre d'outils visible)
		fenetrePrincipale.setMinimumSize(new Dimension(474, 328));
		gestionnaireEvenement.setResizeCanvas(true);
	}

	@Override
	protected void CreerComposants() {
		this.gestionEtatAction = new GestionnaireEtatAction();

		// Creation des barres d'outils et de proprietes
		barreOutils = new EditeurBarreOutils(gestionnaireEvenement,
				gestionEtatAction);
		barreProprietes = new EditeurBarreProprietes(gestionnaireEvenement);
		
		gestionnaireEvenement.addObserver(barreProprietes);
		gestionnaireEvenement.addObserver(gestionEtatAction);
		
		listeComposants.add(barreOutils);
		listeComposants.add(barreProprietes);
	}

	@Override
	public void ChargerComposants() {
		// Obligé de faire ça sinon y veut pas se centrer criss!
		fenetrePrincipale.remove(canvas);
		fenetrePrincipale.add(canvas, BorderLayout.CENTER);

		// Initialiser le contexte opengl à l'affichage du mode éditeur
		FacadeCpp.fctC_initialiserOpenGL(canvas);

		// On charge la barre d'outils
		fenetrePrincipale.add(barreOutils, BorderLayout.NORTH);
		fenetrePrincipale.add(barreProprietes, BorderLayout.WEST);
	}

	public Dimension getCanvasSize() {
		return new Dimension(canvas.getSize());
	}
	
	public void HideEditorComponents()
	{
		barreOutils.setVisible(false);
		barreProprietes.setVisible(false);
		fenetrePrincipale.getJMenuBar().setVisible(false);
	}
	
	public void ShowEditorComponents()
	{
		barreOutils.setVisible(true);
		barreProprietes.setVisible(true);
		fenetrePrincipale.getJMenuBar().setVisible(true);
	}
}
