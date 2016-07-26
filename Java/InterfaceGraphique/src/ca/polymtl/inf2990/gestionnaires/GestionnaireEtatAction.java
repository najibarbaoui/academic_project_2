package ca.polymtl.inf2990.gestionnaires;

import java.util.ArrayList;
import java.util.Observable;
import java.util.Observer;

import javax.swing.JToggleButton;

public class GestionnaireEtatAction implements Observer {
	ArrayList<JToggleButton> boutonsBarreOutils;

	public GestionnaireEtatAction() {
		boutonsBarreOutils = new ArrayList<JToggleButton>();
	}

	public void addButton(JToggleButton button) {
		boutonsBarreOutils.add(button);
	}

	@Override
	public void update(Observable o, Object arg1) {
		int etatActionIndex = ((GestionnaireEvenement) o).getEtatActionCourant();

		for (int i = 0; i < boutonsBarreOutils.size(); i++) {
			if (i == etatActionIndex) {
				boutonsBarreOutils.get(i).setSelected(true);
			} else {
				boutonsBarreOutils.get(i).setSelected(false);
			}
		}
	}
}
