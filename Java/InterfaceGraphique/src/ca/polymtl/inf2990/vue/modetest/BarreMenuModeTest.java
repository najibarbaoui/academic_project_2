package ca.polymtl.inf2990.vue.modetest;

import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.KeyStroke;

import ca.polymtl.inf2990.gestionnaires.GestionnaireEvenement;

public class BarreMenuModeTest extends JMenuBar {
	private GestionnaireEvenement ge;

	private JMenu menuFichier, menuVue;

	public BarreMenuModeTest(GestionnaireEvenement gestionnaireEvenement) {
		this.ge = gestionnaireEvenement;
		//creer les menus
		menuFichier = CreerMenuFichier();
		menuVue = CreerMenuVues();
	
		this.add(menuFichier);
		this.add(menuVue);
	}

	private JMenu CreerMenuFichier() {
		JMenu menu = new JMenu("Fichier");
		// On s'assure que les menus apparaîtront par-dessus l'OpenGL
		menu.getPopupMenu().setLightWeightPopupEnabled(false);
		// On assigne un mnémonique.
		menu.setMnemonic('F');

		// Informations à propos de chaque menu items
		String texts[] = { "Éditeur", "Menu principal" };
		char mnemonics[] = { 0, 'Q' };
		String actionCommands[] = { "Changer vue: editeur", 
				"Changer vue: menu" };

		for (int i = 0; i < texts.length; i++) {
			JMenuItem mi = new JMenuItem(texts[i]);
			if (mnemonics[i] != 0) {
				mi.setMnemonic(mnemonics[i]);
				mi.setAccelerator(KeyStroke
						.getKeyStroke("ctrl " + mnemonics[i]));
			}
			mi.setActionCommand(actionCommands[i]);
			mi.addActionListener(ge);
			menu.add(mi);
		}

		return menu;
	}
	private JMenu CreerMenuVues() {
		JMenu menu = new JMenu("Vues");
		// On s'assure que les menus apparaîtront par-dessus l'OpenGL
		menu.getPopupMenu().setLightWeightPopupEnabled(false);
		// On assigne un mnémonique.
		menu.setMnemonic('V');

		// Informations à propos de chaque menu items
		String texts[] = { "Orthographique", "Orbite" };
		char mnemonics[] = { 0, 0 };
		String actionCommands[] = { "Orthographique", "Orbite" };

		for (int i = 0; i < texts.length; i++) {
			JMenuItem mi = new JMenuItem(texts[i]);
			if (mnemonics[i] != 0) {
				mi.setMnemonic(mnemonics[i]);
				mi.setAccelerator(KeyStroke.getKeyStroke(mnemonics[i]));
			}
			mi.setActionCommand(actionCommands[i]);
			mi.addActionListener(ge);
			menu.add(mi);
		}
		return menu;
	}

	private JMenuItem CreerMenuItem(String text, char mnemonic,
			String accelerator, String actionCommand) {
		JMenuItem menuItem = new JMenuItem();

		menuItem.setText(text);
		if (mnemonic != 0) {
			menuItem.setMnemonic(mnemonic);
		}
		if (accelerator != null) {
			menuItem.setAccelerator(KeyStroke.getKeyStroke(accelerator));
		}
		menuItem.setActionCommand(actionCommand);
		menuItem.addActionListener(ge);

		return menuItem;
	}

}

/*
 * 
 * public class BarreMenuModeTest extends JPanel { JButton bEditeur = new
 * JButton(); JButton bCamera = new JButton(); JButton bMenuPrincipal = new
 * JButton();
 * 
 * 
 * private GestionnaireEvenement ge;
 * 
 * public BarreMenuModeTest(GestionnaireEvenement gestionnaireEvenement) {
 * this.ge = gestionnaireEvenement; this.setBackground(new Color(0f, 0f, 0f,
 * 0f)); //this.setBackground(Color.DARK_GRAY); //this.setPreferredSize(new
 * Dimension(0, 50)); this.setLayout(new GridLayout(3, 1, 0, 20));
 * this.setPreferredSize(new Dimension(200, 300));
 * 
 * this.setLayout(new FlowLayout(FlowLayout.CENTER));
 * bEditeur.setPreferredSize(new Dimension(170, 30));
 * bEditeur.setActionCommand("Changer vue: editeur");
 * bEditeur.addActionListener(ge); bEditeur.setText("Éditeur");
 * 
 * 
 * this.setLayout(new FlowLayout(FlowLayout.CENTER));
 * bCamera.setPreferredSize(new Dimension(170, 30));
 * bCamera.setActionCommand(""); bCamera.addActionListener(ge);
 * bCamera.setText("Caméra");
 * 
 * this.setLayout(new FlowLayout(FlowLayout.CENTER));
 * bMenuPrincipal.setPreferredSize(new Dimension(170, 30));
 * bMenuPrincipal.setActionCommand("Changer vue: menu");
 * bMenuPrincipal.addActionListener(ge);
 * bMenuPrincipal.setText("Menu principale");
 * 
 * 
 * 
 * this.add(bEditeur); this.add(bCamera); this.add(bMenuPrincipal);
 * 
 * }
 * 
 * }
 */
