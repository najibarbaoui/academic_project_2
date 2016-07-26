package ca.polymtl.inf2990.vue.configuration;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JMenuBar;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;

import ca.polymtl.inf2990.composants.Fenetre;
import ca.polymtl.inf2990.composants.JKeybindButton;
import ca.polymtl.inf2990.gestionnaires.GestionnaireEvenement;
import ca.polymtl.inf2990.gestionnaires.GestionnaireDeVue.TypesVue;
import ca.polymtl.inf2990.vues.Vue;

public class ConfigurationVue extends Vue {

	List<Character> usedKeybinds;

	JTabbedPane tabbedPane;
	JPanel buttonsPanel;

	public ConfigurationVue(Fenetre fenetre,
			GestionnaireEvenement gestionnaireDEvenement) {
		super(fenetre, gestionnaireDEvenement);
		typeVue = TypesVue.CONFIGURATION;
		titreFenetre = "Configuration - INF2990";
		largeurFenetre = 700;
		hauteurFenetre = 370;

		usedKeybinds = new ArrayList<Character>();
	}

	@Override
	protected void CreerComposants() {
		// Le panneau contenant les configurations
		tabbedPane = CreerTabbedPane();
		listeComposants.add(tabbedPane);

		// Les boutons dans le bas
		buttonsPanel = CreerButtonsPanel();
		listeComposants.add(buttonsPanel);
	}

	private JTabbedPane CreerTabbedPane() {
		JTabbedPane pane = new JTabbedPane();

		//// Premier tab, la configuration des touches du clavier
		JPanel keybindPanel = new JPanel(new GridLayout(0, 2));
		keybindPanel.setBackground(Color.RED);
		keybindPanel.setPreferredSize(new Dimension(200, 0));
		pane.addTab("Configuration des touches", keybindPanel);
		
		// UP PLAYER1
		keybindPanel.add(new JLabel("Accélerer"));
		JButton player1AccelerateKeybindButton = new JKeybindButton(usedKeybinds, 'W');
		keybindPanel.add(player1AccelerateKeybindButton);
		
		// DOWN PLAYER1
		keybindPanel.add(new JLabel("Effectuer un 180"));
		JButton player1UTurnKeybindButton = new JKeybindButton(usedKeybinds, 'S');
		keybindPanel.add(player1UTurnKeybindButton);

		// LEFT PLAYER1
		keybindPanel.add(new JLabel("Tourner à gauche"));
		JButton player1LeftKeybindButton = new JKeybindButton(usedKeybinds, 'A');
		keybindPanel.add(player1LeftKeybindButton);

		// RIGHT PLAYER1
		keybindPanel.add(new JLabel("Tourner à droite"));
		JButton player1RightKeybindButton = new JKeybindButton(usedKeybinds, 'D');
		keybindPanel.add(player1RightKeybindButton);
		
		// SHOOT PLAYER1
		keybindPanel.add(new JLabel("Tirer"));
		JButton player1ShootKeybindButton = new JKeybindButton(usedKeybinds, ' ');
		keybindPanel.add(player1ShootKeybindButton);

		// LEFT PLAYER2
		// RIGHT PLAYER2
		// UP PLAYER2
		// DOWN PLAYER2
		// SHOOT PLAYER2

		// Deuxième tab, la configuration des règles du jeu
		JPanel rulesPanel = new JPanel();
		rulesPanel.setBackground(Color.BLUE);
		pane.addTab("Règles du jeu", rulesPanel);

		// Troisième tab, la configuration des options de débogage
		JPanel debugPanel = new JPanel();
		debugPanel.setBackground(Color.YELLOW);
		pane.addTab("Options de débogage", debugPanel);

		return pane;
	}

	private JPanel CreerButtonsPanel() {
		JPanel panel = new JPanel();

		JButton bQuitter = new JButton();
		bQuitter.setActionCommand("Changer vue: menu");
		bQuitter.addActionListener(gestionnaireEvenement);
		bQuitter.setText("Quitter");
		panel.add(bQuitter);

		return panel;
	}

	@Override
	public void ActiverVue() {
		// TODO Auto-generated method stub

	}

	@Override
	public void DetruireVue() {
		// TODO Auto-generated method stub

	}

	@Override
	public JMenuBar construireMenu() {
		// Pas de barre de menu dans la fenêtre de configuration
		return null;
	}

	@Override
	public void setProprietesFenetre() {
		gestionnaireEvenement.setResizeCanvas(false);

		// Affecter le titre de la fenêtre et sa taille à l'affichage
		fenetrePrincipale.setTitle(this.getTitreFenetre());
		fenetrePrincipale.setSize(this.getLargeurFenetre(),
				this.getHauteurFenetre());

		// Définir une taille minimale sur la fenêtre
		fenetrePrincipale.setMinimumSize(new Dimension(270, 370));
	}

	@Override
	public void ChargerComposants() {
		fenetrePrincipale.setLayout(new BorderLayout());

		fenetrePrincipale.add(tabbedPane, BorderLayout.CENTER);
		fenetrePrincipale.add(buttonsPanel, BorderLayout.SOUTH);
	}

}
