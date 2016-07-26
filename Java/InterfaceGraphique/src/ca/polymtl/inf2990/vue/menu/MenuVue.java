package ca.polymtl.inf2990.vue.menu;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.Image;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JMenuBar;
import javax.swing.JPanel;
import javax.swing.SwingConstants;

import ca.polymtl.inf2990.composants.Fenetre;
import ca.polymtl.inf2990.composants.JImagePanel;
import ca.polymtl.inf2990.gestionnaires.GestionnaireDeVue.TypesVue;
import ca.polymtl.inf2990.gestionnaires.GestionnaireEvenement;
import ca.polymtl.inf2990.vues.Vue;

public class MenuVue extends Vue {

	JLabel lAsteroid;
	JButton bCampagne, bPartieRapide, bConfiguration, bEditeur, bQuitter;
	private JLabel loadingLabel;
	JPanel menuPanel;
	public MenuVue(Fenetre fenetre, GestionnaireEvenement gestionnaireDEvenement) {
		super(fenetre, gestionnaireDEvenement);
		typeVue = TypesVue.MENU;
		titreFenetre = "Menu - INF2990";
		largeurFenetre = 270;
		hauteurFenetre = 370;
	}

	@Override
	protected void CreerComposants() {
		// Le premier composant est un JPanel qui sert de fond d'écran à la
		// fenêtre. Il contient les autres composants
		JPanel backgroundPanel = null;
		try {
			backgroundPanel = new JImagePanel(
					ImageIO.read(getClass()
							.getResource(
									"/ca/polymtl/inf2990/images/AsteroidBackground.png")));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		// / Ce panel est centré et reste de taille fixe. Il contient les
		// boutons du menu.
		menuPanel = new JPanel();

		// Rend le background du panel de menu transparent
		menuPanel.setBackground(new Color(0f, 0f, 0f, 0f));

		// La bordure est créée avec des marges de 20 pixels
		// menuPanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

		// Le layout pour les boutons. Il y a un label et cinq boutons et il y a
		// 5 pixels entre chaque
		menuPanel.setLayout(new GridLayout (7, 1, 0, 10));
		menuPanel.setPreferredSize(new Dimension(200, 315));

		lAsteroid = new JLabel();
		lAsteroid.setText("ASTEROID GAME");
		lAsteroid.setForeground(Color.white);
		lAsteroid.setHorizontalAlignment(SwingConstants.CENTER);

		bCampagne = new JButton(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/images/compagne.png")));
		bCampagne.setActionCommand("Changer vue: campagne");
		bCampagne.addActionListener(gestionnaireEvenement);
		bCampagne.setRolloverIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/images/compagneR.png")));
		//bCampagne.setPreferredSize(new Dimension(190, 45));
		bCampagne.setOpaque(false);
		bCampagne.setContentAreaFilled(false);
		bCampagne.setBorderPainted(false);
		
		bPartieRapide = new JButton(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/images/partierapide.png")));
		bPartieRapide.setActionCommand("Changer vue: partie rapide");
		bPartieRapide.addActionListener(gestionnaireEvenement);
		bPartieRapide.setRolloverIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/images/partierapideR.png")));
		bPartieRapide.setOpaque(false);
		bPartieRapide.setContentAreaFilled(false);
		bPartieRapide.setBorderPainted(false);
		
		
		
		bConfiguration = new JButton(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/images/configuration.png")));
		bConfiguration.setActionCommand("Changer vue: configuration");
		bConfiguration.addActionListener(gestionnaireEvenement);
		bConfiguration.setRolloverIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/images/configurationR.png")));
		bConfiguration.setOpaque(false);
		bConfiguration.setContentAreaFilled(false);
		bConfiguration.setBorderPainted(false);
		
		
		bEditeur = new JButton(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/images/edit.png")));
		bEditeur.setActionCommand("Changer vue: editeur");
		bEditeur.addActionListener(gestionnaireEvenement);
		bEditeur.setRolloverIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/images/editR.png")));
		bEditeur.setPressedIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/images/editP.png")));
		bEditeur.setOpaque(false);
		bEditeur.setContentAreaFilled(false);
		bEditeur.setBorderPainted(false);
		//bEditeur.setText("Éditeur");

		bQuitter = new JButton(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/images/quitter.png")));
		bQuitter.setActionCommand("Quitter");
		bQuitter.addActionListener(gestionnaireEvenement);
		bQuitter.setRolloverIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/images/quitterR.png")));
		bQuitter.setOpaque(false);
		bQuitter.setContentAreaFilled(false);
		bQuitter.setBorderPainted(false);
		
		menuPanel.add(lAsteroid);
		menuPanel.add(bCampagne);
		menuPanel.add(bPartieRapide);
		menuPanel.add(bConfiguration);
		menuPanel.add(bEditeur);
		menuPanel.add(bQuitter);
		backgroundPanel.add(menuPanel);

		listeComposants.add(backgroundPanel);
	}

	@Override
	public void DetruireVue() {
	}

	@Override
	public void ActiverVue() {
	}

	public void setLabelWait(){
		bEditeur.setText("Wait");
	}
	
	@Override
	public JMenuBar construireMenu() {
		// Pas de barre de menu dans le menu principal
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

		// Ajouter les composants de la vue à la fenêtre principale
		for (JComponent composant : listeComposants) {
			fenetrePrincipale.add(composant);
		}
		System.out.println("w" + bEditeur.getWidth()  + "h" +  bEditeur.getHeight());
	}
}
