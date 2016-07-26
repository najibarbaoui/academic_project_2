package ca.polymtl.inf2990.vue.jeu;

import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.KeyStroke;

import ca.polymtl.inf2990.gestionnaires.GestionnaireEvenement;

public class BarreMenuModeJeu extends JMenuBar {
		private GestionnaireEvenement ge;

		private JMenu menuVue,menuFichier;

		public BarreMenuModeJeu(GestionnaireEvenement gestionnaireEvenement) {
			this.ge = gestionnaireEvenement;
			menuFichier = CreerMenuFichier();
			// Créer le menu "Options"
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
			String texts[] = { "Menu principal" };
			char mnemonics[] = { 'Q' };
			String actionCommands[] = { 
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



