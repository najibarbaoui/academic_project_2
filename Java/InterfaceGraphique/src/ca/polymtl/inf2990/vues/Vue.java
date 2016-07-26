package ca.polymtl.inf2990.vues;

import java.util.ArrayList;

import javax.swing.JComponent;
import javax.swing.JMenuBar;

import ca.polymtl.inf2990.composants.Fenetre;
import ca.polymtl.inf2990.gestionnaires.GestionnaireDeVue.TypesVue;
import ca.polymtl.inf2990.gestionnaires.GestionnaireEvenement;

public abstract class Vue {
	protected GestionnaireEvenement gestionnaireEvenement;
	protected Fenetre fenetrePrincipale;

	protected TypesVue typeVue;
	
	protected ArrayList<JComponent> listeComposants;

	protected String titreFenetre;
	protected int largeurFenetre;
	protected int hauteurFenetre;
	public Vue(Fenetre fenetre, GestionnaireEvenement gestionnaireDEvenement) {
		this.fenetrePrincipale = fenetre;
		this.gestionnaireEvenement = gestionnaireDEvenement;

		listeComposants = new ArrayList<JComponent>();

		CreerComposants();
	}

	abstract public void ActiverVue();

	abstract public void DetruireVue();

	abstract public JMenuBar construireMenu();

	abstract public void setProprietesFenetre();

	abstract public void ChargerComposants();

	abstract protected void CreerComposants();

	public ArrayList<JComponent> getListeComposants() {
		return listeComposants;
	}

	public String getTitreFenetre() {
		return titreFenetre;
	}

	public int getLargeurFenetre() {
		return largeurFenetre;
	}

	public int getHauteurFenetre() {
		return hauteurFenetre;
	}
	
	public TypesVue getTypeVue() {
		return typeVue;
	}
	
	
}
