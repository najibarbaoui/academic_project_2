package ca.polymtl.inf2990.vue.editeur;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;

import javax.swing.ImageIcon;
import javax.swing.JPanel;
import javax.swing.JToggleButton;

import ca.polymtl.inf2990.gestionnaires.GestionnaireEtatAction;
import ca.polymtl.inf2990.gestionnaires.GestionnaireEvenement;

@SuppressWarnings("serial")
public class EditeurBarreOutils extends JPanel {
	private GestionnaireEvenement ge;
	private GestionnaireEtatAction gea;

	String[] nomOutils = { 
			"S�lection", 
			"D�placement", 
			"Rotation",
			"Mise � �chelle", 
			"Duplication", 
			"Zoom",
			"Cr�ation de stations spatiales",
			"Cr�ation de bonus acc�l�rateurs",
			"Cr�ation de barri�res protectrices", 
			"Cr�ation de portails"
			};

	String[] actionCommands = { 
			"Action: S�lection", 
			"Action: D�placement",
			"Action: Rotation", 
			"Action: Mise � l'�chelle",
			"Action: Duplication", 
			"Action: Zoom",
			"Action: Ajouter Noeud: stationSpatiale",
			"Action: Ajouter Noeud: bonusAccelerateur",
			"Action: Ajouter Noeud: barriereProtectrice",
			"Action: Ajouter Noeud: portail"
	};
	
	String[] iconPaths = {
		"Selection.png",
		"Deplacement.png",
		"Rotation.png",
		"Resize.png",
		"Duplicate.png",
		"Zoom.png",
		"AjouterStationSpatiale.png",
		"AjouterBonusAccelerateur.png",
		"AjouterBarriereProtectrice.png",
		"AjouterPortail.png"
	};

	String[] ToolTipText = {
			"S�lection",
			"D�placement",
			"Rotation",
			"Redimensionner",
			"Dupliquer",
			"Zoom",
			"Ajouter Station Spatiale",
			"Ajouter Bonus Accelerateur",
			"Ajouter Barriere Protectrice",
			"Ajouter Portail"
		};
	
	public EditeurBarreOutils(GestionnaireEvenement gestionnaireEvenement,
			GestionnaireEtatAction gestionnaireEtatAction) {
		this.ge = gestionnaireEvenement;
		this.gea = gestionnaireEtatAction;

		this.setBackground(Color.DARK_GRAY);
		this.setPreferredSize(new Dimension(0, 50));

		this.setLayout(new FlowLayout(FlowLayout.LEFT));

		for (int i = 0; i < nomOutils.length; i++) {
			JToggleButton bOutil;
			if (iconPaths[i] != null) {
				ImageIcon icon = new ImageIcon(getClass()
				.getResource(
						"/ca/polymtl/inf2990/images/" + iconPaths[i]));
			
				bOutil = new JToggleButton(icon);
			} else {
				bOutil = new JToggleButton();
			}
			bOutil.setToolTipText(ToolTipText[i]!=null ? ToolTipText[i] : "No tool tip text found for this button" );
			bOutil.setPreferredSize(new Dimension(40, 40));
			bOutil.setActionCommand(actionCommands[i]);

			bOutil.setBackground(Color.WHITE);

			bOutil.addActionListener(ge);
			gea.addButton(bOutil);

			this.add(bOutil);
		}
	}
}
