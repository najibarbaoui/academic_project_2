package ca.polymtl.inf2990.composants;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.text.DecimalFormat;

import javax.swing.JTextField;

import ca.polymtl.inf2990.gestionnaires.GestionnaireEvenement;

@SuppressWarnings("serial")
public class JValueField extends JTextField {
	GestionnaireEvenement ge;
	double val;
	int indexPropriete;

	public JValueField(GestionnaireEvenement gestionnaireEvenement, int indexPropriete, double val) {
		this.ge = gestionnaireEvenement;
		this.indexPropriete = indexPropriete;
		this.val = val;

		// Value is rounded only in display
		this.setText(new DecimalFormat("#.##").format(val));

		this.addFocusListener(new FocusListener() {

			@Override
			public void focusGained(FocusEvent arg0) {
				// Do nothing on focus gained
			}

			@Override
			public void focusLost(FocusEvent arg0) {
				VerifierValeur();
			}

		});

		this.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				VerifierValeur();
			}

		});
	}
	
	private void VerifierValeur() {
		try {
			double newVal = Double.parseDouble(this.getText());
			
			ge.UpdateProprietesNoeudSelectionne(indexPropriete, newVal);
		} catch (NumberFormatException e) {
			// Erreur
			this.setText(new DecimalFormat("#.##").format(val));
		}
		System.out.println("Verifier valeur");
	}
}
