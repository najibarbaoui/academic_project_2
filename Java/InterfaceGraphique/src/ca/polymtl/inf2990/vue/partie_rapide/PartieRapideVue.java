package ca.polymtl.inf2990.vue.partie_rapide;

import java.awt.BorderLayout;
import java.awt.Canvas;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.io.File;
import java.lang.reflect.InvocationTargetException;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.CancellationException;

import javax.swing.AbstractButton;
import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JMenuBar;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;
import javax.swing.border.Border;
import javax.swing.filechooser.FileNameExtensionFilter;

import ca.polymtl.inf2990.composants.Fenetre;
import ca.polymtl.inf2990.cpp.FacadeCpp;
import ca.polymtl.inf2990.gestionnaires.GestionnaireDeVue;
import ca.polymtl.inf2990.gestionnaires.GestionnaireEtatAction;
import ca.polymtl.inf2990.gestionnaires.GestionnaireEvenement;
import ca.polymtl.inf2990.gestionnaires.GestionnaireDeVue.TypesVue;
import ca.polymtl.inf2990.vue.editeur.EditeurBarreOutils;
import ca.polymtl.inf2990.vue.editeur.EditeurBarreProprietes;
import ca.polymtl.inf2990.vue.editeur.EditeurMenu;
import ca.polymtl.inf2990.vues.Vue;

public class PartieRapideVue extends Vue {
	GestionnaireDeVue gestionnaireDeVue;
	JPanel partie, zoneJeu;

	GestionnaireEtatAction gestionEtatAction;
	private JTextField userText_;
	private JButton bvalider_;
	private JRadioButton bsolo_;
	private JRadioButton bcooperative_;
	private JRadioButton bhumain_;
	private JRadioButton bvirtuel_;
	private ButtonGroup groupJoueur_;

	public JRadioButton getBoutonSolo() {
		return bsolo_;
	}

	public JRadioButton getBoutonCoop() {
		return bcooperative_;
	}

	public JRadioButton getBoutonHumain() {
		return bhumain_;
	}

	public JRadioButton getBoutonVirtuel() {
		return bvirtuel_;
	}

	public ButtonGroup getBoutonGroupJoueur() {
		return groupJoueur_;
	}

	public JButton getBoutonValider() {
		return bvalider_;
	}

	public JTextField getUserText_() {
		return userText_;
	}

	public void setUserText_(JTextField userText_) {
		this.userText_ = userText_;
	}

	public void setNomFichier(String text) {

		userText_.setText(text);
	}

	public JTextField getJTextField() {
		return userText_;
	}

	public PartieRapideVue(Fenetre fenetre,
			GestionnaireEvenement gestionnaireDEvenement) {
		super(fenetre, gestionnaireDEvenement);
		typeVue = TypesVue.PARTIERAPIDE;
		titreFenetre = "Partie rapide - INF2990";
		largeurFenetre = 600;
		hauteurFenetre = 200;

	}

	private JPanel creerChargerZoneJeu() {
		JPanel panelTransit = new JPanel();

		// faire un panel pour le bouton parcourir et le champ de saisis
		JPanel panelZoneJeu = new JPanel();
		Border border = BorderFactory
				.createTitledBorder("Selection de la zone de jeu");
		userText_ = new JTextField(42);// champ de saisi
		userText_.setActionCommand("Chemin du fichier");
		userText_.addActionListener(gestionnaireEvenement);
		JButton bparcourir = new JButton("Parcourir");// bouton parcourir et
														// charger le fichier
		bparcourir.setMnemonic(KeyEvent.VK_P);
		bparcourir.setActionCommand("Parcourir");

		panelZoneJeu.setBorder(border);
		panelZoneJeu.add(userText_);
		panelZoneJeu.add(bparcourir);

		// faire un panel pour le bouton valider passer en mode et le bouton
		// menu principal
		JPanel panelValider = new JPanel();
		panelValider.setLayout(new FlowLayout());
		Border borderValider = BorderFactory
				.createTitledBorder("Valider pour commencer le jeu");

		// bouton valider
		bvalider_ = new JButton("Valider");
		bvalider_.setPreferredSize(new Dimension(280, 30));
		bvalider_.setActionCommand("Changer vue: jeu");
		bvalider_.setEnabled(false);

		// bouton menu principal
		JButton bmenuPrincipal = new JButton("Menu principal");
		bmenuPrincipal.setPreferredSize(new Dimension(280, 30));
		bmenuPrincipal.setActionCommand("Changer vue: menu");

		bparcourir.addActionListener(gestionnaireEvenement);
		bvalider_.addActionListener(gestionnaireEvenement);
		bmenuPrincipal.addActionListener(gestionnaireEvenement);

		// on met le tout de le panel concerné
		panelValider.setBorder(borderValider);
		panelValider.add(bmenuPrincipal);
		panelValider.add(bvalider_);

		// panel qui regroupe les deux panels ci dessus juste pour le design
		panelTransit.setLayout(new GridLayout(2, 1));
		panelTransit.add(panelZoneJeu);
		panelTransit.add(panelValider);

		return panelTransit;
	}

	private JPanel creerPartieJoueur() {
		JPanel panelPartieJoueur = new JPanel();
		// texte pour le deuxième joueur a choisir sous forme de bouttons
		// arrondis à cocher
		Border borderPartie = BorderFactory
				.createTitledBorder("Type de partie");
		bsolo_ = new JRadioButton("Solo", true);
		bcooperative_ = new JRadioButton("Coopérative");

		// texte pour le deuxième joueur a choisir sous forme de boutons
		// arrondis à cocher
		Border borderJoueur = BorderFactory
				.createTitledBorder("Type de deuxième joueur");
		bhumain_ = new JRadioButton("Humain");
		bvirtuel_ = new JRadioButton("Virtuel");
		bhumain_.setEnabled(false);
		bvirtuel_.setEnabled(false);
		// les raccourcis de ces boutons aux touches du clavier
		bsolo_.setMnemonic(KeyEvent.VK_S);
		bcooperative_.setMnemonic(KeyEvent.VK_C);
		bhumain_.setMnemonic(KeyEvent.VK_H);
		bvirtuel_.setMnemonic(KeyEvent.VK_V);

		// les évènements attendus pour ces boutons
		bsolo_.setActionCommand("Solo");
		bcooperative_.setActionCommand("Cooperative");

		bhumain_.setActionCommand("Humain");
		bhumain_.addActionListener(gestionnaireEvenement);

		bvirtuel_.setActionCommand("Virtuel");
		bvirtuel_.addActionListener(gestionnaireEvenement);

		// on le met en groupe suivant leur appartenance
		ButtonGroup groupPartie = new ButtonGroup();
		groupJoueur_ = new ButtonGroup();

		groupPartie.add(bsolo_);
		groupPartie.add(bcooperative_);

		groupJoueur_.add(bhumain_);
		groupJoueur_.add(bvirtuel_);

		bsolo_.addActionListener(gestionnaireEvenement);
		bcooperative_.addActionListener(gestionnaireEvenement);

		// creation de deux panel pour les disposer sous deux lignes
		JPanel panelPartie = new JPanel();
		panelPartie.setBorder(borderPartie);
		panelPartie.add(bsolo_);
		panelPartie.add(bcooperative_);

		JPanel panelJoueur = new JPanel();
		panelJoueur.setBorder(borderJoueur);
		panelJoueur.add(bhumain_);
		panelJoueur.add(bvirtuel_);

		panelPartieJoueur.setLayout(new GridLayout(1, 2));
		panelPartieJoueur.add(panelPartie);
		panelPartieJoueur.add(panelJoueur);

		return panelPartieJoueur;

	}

	public void ActiverVue() {
		// Afficher le context OpenGL et activer la minuterie

	}

	public void DetruireVue() {
		// Désactiver la minuterie et masquer le context OpenGL
		gestionnaireEvenement.deleteObserver(gestionEtatAction);

	}

	public JMenuBar construireMenu() {
		return null;
	}

	@Override
	public void setProprietesFenetre() {
		// Affecter le titre de la fenêtre et sa taille à l'affichage
		fenetrePrincipale.setTitle(this.getTitreFenetre());
		fenetrePrincipale.setSize(this.getLargeurFenetre(),
				this.getHauteurFenetre());
		// Définir une taille minimale sur la fenêtre (Dimensions pour garder le
		// la barre de proprietes et la barre d'outils visible)
		fenetrePrincipale.setResizable(false);

		gestionnaireEvenement.setResizeCanvas(false);
	}

	@Override
	protected void CreerComposants() {

		partie = creerPartieJoueur();
		zoneJeu = creerChargerZoneJeu();

		listeComposants.add(partie);
		listeComposants.add(zoneJeu);

	}

	@Override
	public void ChargerComposants() {
		fenetrePrincipale.add(partie, BorderLayout.NORTH);
		fenetrePrincipale.add(zoneJeu, BorderLayout.CENTER);
	}

	public Dimension getCanvasSize() {
		return null;
	}

}
