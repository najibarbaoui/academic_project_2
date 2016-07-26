package ca.polymtl.inf2990.vue.jeu;

import java.awt.BorderLayout;
import java.awt.Canvas;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.lang.reflect.InvocationTargetException;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.CancellationException;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JMenuBar;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import ca.polymtl.inf2990.composants.Fenetre;
import ca.polymtl.inf2990.cpp.FacadeCpp;
import ca.polymtl.inf2990.gestionnaires.GestionnaireEtatAction;
import ca.polymtl.inf2990.gestionnaires.GestionnaireEvenement;
import ca.polymtl.inf2990.gestionnaires.GestionnaireDeVue.TypesVue;
import ca.polymtl.inf2990.vue.editeur.EditeurBarreOutils;
import ca.polymtl.inf2990.vue.editeur.EditeurBarreProprietes;
import ca.polymtl.inf2990.vue.editeur.EditeurMenu;
import ca.polymtl.inf2990.vue.modeScoreVue.ModeScoreVue;
import ca.polymtl.inf2990.vues.Vue;

public class ModeJeuVue extends Vue {
		public Canvas canvas;
		public boolean estScore = false;
		private ModeScoreVue jdialog;
		public boolean pause = false;
		// Minuterie qui gère l'affichage constant du context OpenGL
		Timer minuterie;
		// Le temps souhaité entre 2 affichages, en millisecondes.
		static private final int TEMPS_INTER_AFFICHAGE = 30;
		
		GestionnaireEtatAction gestionEtatAction;
		
		public ModeJeuVue(Fenetre fenetre,
				GestionnaireEvenement gestionnaireDEvenement, Canvas canvas) {
			super(fenetre, gestionnaireDEvenement);
			typeVue = TypesVue.JEU;
			titreFenetre = "Éditeur - INF2990";
			largeurFenetre = 1600;
			hauteurFenetre = 900;
			
			this.canvas = canvas; 
			
		}

	
		public JPanel getJdialog()
		{
			return jdialog;
		}
		public void ActiverVue() {
			// Afficher le context OpenGL et activer la minuterie
			canvas.setVisible(true);
			this.activerMinuterie();
		}

		public void DetruireVue() {
			// Désactiver la minuterie et masquer le context OpenGL
			minuterie.cancel();
			canvas.setVisible(false);
			jdialog.setVisible(false);
			gestionnaireEvenement.deleteObserver(gestionEtatAction);
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
								afficherScore();
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
			return new BarreMenuModeJeu(gestionnaireEvenement);
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
			fenetrePrincipale.setResizable(true);
			gestionnaireEvenement.setResizeCanvas(true);
		}
		
		@Override
		protected void CreerComposants() {
			jdialog = new ModeScoreVue(gestionnaireEvenement);
		}

		@Override
		public void ChargerComposants() {
			// Obligé de faire ça sinon y veut pas se centrer criss!
			fenetrePrincipale.remove(canvas);
			fenetrePrincipale.add(canvas, BorderLayout.CENTER);
			
			// Initialiser le contexte opengl à l'affichage du mode éditeur
			FacadeCpp.fctC_initialiserOpenGL(canvas);
			fenetrePrincipale.add(jdialog,BorderLayout.NORTH);
		}

		public Dimension getCanvasSize() {
			return new Dimension(canvas.getSize());
		}
		 
		//methode pour afficher le score en pop up
		public void afficherScore(){
			estScore = FacadeCpp.fctC_isTermine();// on recupère si vrai c est terminé sinon faux
			
			//on met la fenetre enable si le pop up est declenché
			if(estScore)
				//fenetrePrincipale.setEnabled(false);
			
			//On met le pop up visible
			if(estScore && !pause){
				
				jdialog.setVisible(true);

				if(FacadeCpp.fctC_getIsGagne()){
					jdialog.getTextScore().setFont(new Font("TimesRoman", 
							Font.PLAIN, 25));
				jdialog.getTextScore().setText("La partie est finie. Bravo tu as gagné.");
				}else{
					jdialog.getTextScore().setFont(new Font("TimesRoman", 
							Font.PLAIN, 25));
					jdialog.getTextScore().setText("La partie est finie. Tu as perdu.");
				}
				jdialog.getBoutonMenuPrincipal().addActionListener(gestionnaireEvenement);
				jdialog.getBoutonRejouer().addActionListener(gestionnaireEvenement);
				pause = true;
				
			}else if(!estScore){
				pause = false;
			}else 
				pause = false;
		}
			
}

