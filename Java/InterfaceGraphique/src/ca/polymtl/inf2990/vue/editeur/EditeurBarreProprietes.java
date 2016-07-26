package ca.polymtl.inf2990.vue.editeur;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.util.Observable;
import java.util.Observer;

import javax.swing.JLabel;
import javax.swing.JPanel;

import ca.polymtl.inf2990.composants.JValueField;
import ca.polymtl.inf2990.gestionnaires.GestionnaireEvenement;
import ca.polymtl.inf2990.modele.ProprietesNoeud;

@SuppressWarnings("serial")
public class EditeurBarreProprietes extends JPanel implements Observer {
	private GestionnaireEvenement ge;

	private final int LARGEURBARRE = 120;
	private final int LARGEURPROPRIETES = LARGEURBARRE - 10;
	private final int LARGEURLABEL = 20;
	private final int LARGEURCHAMPTEXTE = LARGEURPROPRIETES - LARGEURLABEL - 15;

	public EditeurBarreProprietes(GestionnaireEvenement gestionnaireEvenement) {
		this.ge = gestionnaireEvenement;

		// Seulement la largeur importe
		this.setPreferredSize(new Dimension(LARGEURBARRE, 0));
	}

	public void AssignerProprietesNoeudChoisi(ProprietesNoeud proprietes) {
		this.removeAll();
		
		if (proprietes!= null) {
			JPanel panelType = CreerPanelType(proprietes.getType());
			JPanel panelPosition = CreerPanelPosition(
					proprietes.getPositionX(), proprietes.getPositionY());
			JPanel panelRotation = CreerPanelRotation(proprietes.getRotation());
			JPanel panelEchelle = CreerPanelEchelle(proprietes.getEchelle());

			this.add(panelType);
			this.add(panelPosition);
			this.add(panelRotation);
			this.add(panelEchelle);
		}
	}
	
	private JPanel CreerPanelProprietes(int Height) {
		JPanel panelProprietes = new JPanel();

		panelProprietes.setPreferredSize(new Dimension(LARGEURPROPRIETES,
				Height));
		panelProprietes.setBackground(Color.WHITE);

		FlowLayout fl = new FlowLayout();
		fl.setAlignment(FlowLayout.LEFT);

		panelProprietes.setLayout(fl);

		return panelProprietes;
	}
	
	private JPanel CreerPanelType(String type) {
		JPanel panelType = CreerPanelProprietes(55);

		// Afficher le mot Type
		JLabel text = new JLabel("Type :");
		text.setPreferredSize(new Dimension(LARGEURPROPRIETES, 20));

		// Afficher un espace vide pour aligner les champs de texte
		//JLabel space = new JLabel();
		//space.setPreferredSize(new Dimension(LARGEURLABEL, 20));
		
		// Afficher le type
		JLabel typeText = new JLabel(type);
		typeText.setPreferredSize(new Dimension(LARGEURCHAMPTEXTE + LARGEURLABEL, 20));

		// Ajouter composants pour le type
		panelType.add(text);
		//panelType.add(space);
		panelType.add(typeText);
		
		return panelType;
	}

	private JPanel CreerPanelPosition(double positionX, double positionY) {
		JPanel panelPosition = CreerPanelProprietes(80);

		// Afficher le mot Position
		JLabel text = new JLabel("Position :");
		text.setPreferredSize(new Dimension(LARGEURPROPRIETES, 20));

		// Affiche la lettre X
		JLabel xText = new JLabel(" X");
		xText.setPreferredSize(new Dimension(LARGEURLABEL, 20));

		// Affiche le champ de texte pour la variable X
		JValueField xValueField = new JValueField(ge, 0, positionX);
		xValueField.setPreferredSize(new Dimension(LARGEURCHAMPTEXTE, 20));

		// Affiche la lettre Y
		JLabel yText = new JLabel(" Y");
		yText.setPreferredSize(new Dimension(LARGEURLABEL, 20));

		// Affiche le champ de texte pour la variable Y
		JValueField yValueField = new JValueField(ge, 1, positionY);
		yValueField.setPreferredSize(new Dimension(LARGEURCHAMPTEXTE, 20));

		// Ajouter composants pour la position
		panelPosition.add(text);
		panelPosition.add(xText);
		panelPosition.add(xValueField);
		panelPosition.add(yText);
		panelPosition.add(yValueField);

		return panelPosition;
	}

	private JPanel CreerPanelRotation(double rotation) {
		JPanel panelRotation = CreerPanelProprietes(55);

		// Afficher le mot Rotation
		JLabel text = new JLabel("Rotation :");
		text.setPreferredSize(new Dimension(LARGEURPROPRIETES, 20));

		// Afficher un espace vide pour aligner les champs de texte
		JLabel space = new JLabel();
		space.setPreferredSize(new Dimension(LARGEURLABEL, 20));

		// Affiche le champ de texte pour la variable rotation
		JValueField rotationValueField = new JValueField(ge, 2, rotation);
		rotationValueField
				.setPreferredSize(new Dimension(LARGEURCHAMPTEXTE, 20));

		// Ajouter composants pour la rotation
		panelRotation.add(text);
		panelRotation.add(space);
		panelRotation.add(rotationValueField);

		return panelRotation;
	}

	private JPanel CreerPanelEchelle(double echelle) {
		JPanel panelRotation = CreerPanelProprietes(55);

		// Afficher le mot Échelle
		JLabel text = new JLabel("Échelle :");
		text.setPreferredSize(new Dimension(LARGEURPROPRIETES, 20));

		// Afficher un espace vide pour aligner les champs de texte
		JLabel space = new JLabel();
		space.setPreferredSize(new Dimension(LARGEURLABEL, 20));

		// Affiche le champ de texte pour la variable rotation
		JValueField echelleValueField = new JValueField(ge, 3, echelle);
		echelleValueField
				.setPreferredSize(new Dimension(LARGEURCHAMPTEXTE, 20));

		// Ajouter composants pour la rotation
		panelRotation.add(text);
		panelRotation.add(space);
		panelRotation.add(echelleValueField);

		return panelRotation;
	}

	@Override
	public void update(Observable arg0, Object arg1) {
		ProprietesNoeud proprietes = ((GestionnaireEvenement) arg0)
				.getSeulNoeudSelectionne();

		AssignerProprietesNoeudChoisi(proprietes);

		// Update les changements
		this.validate();
		this.repaint();
	}
}
