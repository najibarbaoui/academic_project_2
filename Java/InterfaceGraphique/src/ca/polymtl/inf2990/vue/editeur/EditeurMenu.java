package ca.polymtl.inf2990.vue.editeur;

import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.KeyStroke;

import ca.polymtl.inf2990.gestionnaires.GestionnaireEvenement;

@SuppressWarnings("serial")
public class EditeurMenu extends JMenuBar {
	private GestionnaireEvenement ge;
	
	private JMenu menuFichier, menuEdition, menuOutils, menuVues,
			menuInformations;

	public EditeurMenu(GestionnaireEvenement gestionnaireEvenement) {
		this.ge = gestionnaireEvenement;

		// Cr�er le menu "Fichier"
		menuFichier = CreerMenuFichier();
		this.add(menuFichier);

		// Cr�er le menu "�dition"
		menuEdition = CreerMenuEdition();
		this.add(menuEdition);

		// Cr�er le menu "Outils"
		menuOutils = CreerMenuOutils();
		this.add(menuOutils);

		// Cr�er le menu "Vues"
		menuVues = CreerMenuVues();
		this.add(menuVues);

		// Cr�er le menu "Informations"
		menuInformations = CreerMenuInformations();
		this.add(menuInformations);
	}

	private JMenu CreerMenuFichier() {
		JMenu menu = new JMenu("Fichier");
		// On s'assure que les menus appara�tront par-dessus l'OpenGL
		menu.getPopupMenu().setLightWeightPopupEnabled(false);
		// On assigne un mn�monique.
		menu.setMnemonic('F');

		// Informations � propos de chaque menu items
		String texts[] = { "Nouveau", "Ouvrir", "Enregistrer",
				"Enregistrer sous", "Propri�t�s", "Mode test", "Menu principal" };
		char mnemonics[] = { 0, 0, 'S', 0, 0, 'T', 'Q' };
		String actionCommands[] = { "Nouveau", "Ouvrir", "Enregistrer",
				"Enregistrer sous", "Propri�t�s", "Changer vue: Mode test",
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

	private JMenu CreerMenuEdition() {
		JMenu menu = new JMenu("�dition");
		// On s'assure que les menus appara�tront par-dessus l'OpenGL
		menu.getPopupMenu().setLightWeightPopupEnabled(false);
		// On assigne un mn�monique.
		menu.setMnemonic('E');

		// Informations � propos de chaque menu items
		String texts[] = { "Supprimer" };
		char mnemonics[] = { 0 };
		String actionCommands[] = { "Supprimer" };

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

	private JMenu CreerMenuOutils() {
		JMenu menu = new JMenu("Outils");
		// On s'assure que les menus appara�tront par-dessus l'OpenGL
		menu.getPopupMenu().setLightWeightPopupEnabled(false);
		// On assigne un mn�monique.
		menu.setMnemonic('O');

		// Informations � propos de chaque menu items
		String texts[] = { "S�lection", "D�placement", "Rotation",
				"Mise � l'�chelle", "Duplication", "Cr�ation d'objets", "Zoom" };
		char mnemonics[] = { 's', 'd', 'r', 'e', 'c', 0, 'z' };
		String actionCommands[] = { "Action: S�lection", "Action: D�placement",
				"Action: Rotation", "Action: Mise � l'�chelle",
				"Action: Duplication", "null", "Action: Zoom" };

		for (int i = 0; i < texts.length; i++) {
			if (i == 5) {
				JMenu mi = new JMenu(texts[i]);

				mi.add(CreerMenuItem("Bonus acc�l�rateur", 'b',
						"b",
						"Action: Ajouter Noeud: bonusAccelerateur"));
				mi.add(CreerMenuItem("Portails", (char) 0, (String) null,
						"Action: Ajouter Noeud: portail"));
				mi.add(CreerMenuItem("Barri�re protectrice", (char) 0,
						(String) null,
						"Action: Ajouter Noeud: barriereProtectrice"));
				mi.add(CreerMenuItem("Station spatiale", (char) 0,
						(String) null, "Action: Ajouter Noeud: stationSpatiale"));

				menu.add(mi);
			} else {
				menu.add(CreerMenuItem(texts[i], mnemonics[i], ""
						+ mnemonics[i], actionCommands[i]));
			}
		}

		return menu;
	}

	private JMenu CreerMenuVues() {
		JMenu menu = new JMenu("Vues");
		// On s'assure que les menus appara�tront par-dessus l'OpenGL
		menu.getPopupMenu().setLightWeightPopupEnabled(false);
		// On assigne un mn�monique.
		menu.setMnemonic('V');

		// Informations � propos de chaque menu items
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

	private JMenu CreerMenuInformations() {
		JMenu menu = new JMenu("Informations");
		// On s'assure que les menus appara�tront par-dessus l'OpenGL
		menu.getPopupMenu().setLightWeightPopupEnabled(false);
		// On assigne un mn�monique.
		menu.setMnemonic('I');

		// Informations � propos de chaque menu items
		String texts[] = { "Aide" };
		char mnemonics[] = { 0 };
		String actionCommands[] = { "Aide" };

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
