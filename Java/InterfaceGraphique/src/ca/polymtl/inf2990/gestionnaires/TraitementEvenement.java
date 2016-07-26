package ca.polymtl.inf2990.gestionnaires;

import java.awt.event.KeyEvent;

import ca.polymtl.inf2990.cpp.FacadeCpp;
import ca.polymtl.inf2990.gestionnaires.Commandes.Commande;

public class TraitementEvenement {
	public void NouvelleZone() {

	}

	public void Quitter() {

	}

	public void ChangerVueMenu() {

	}

	public void ChangerVueEditeur() {

	}

	public void OuvrirZone() {

	}

	public void EnregistrerZone() {

	}

	public void EnregistrerSousZone() {

	}

	public void EnvoyerAction(String action) {

	}

	public void TraiterCommande(Commande c) {

		/*
		 * 
		 * if (commande == "Quitter") { System.exit(0); } else if
		 * (commande.contains("Nouveau")) { //FacadeCpp.fctC_ } else if
		 * (commande.contains("Changer vue")) { if (commande.contains("menu")) {
		 * FacadeCpp.fctC_changerEtat(FacadeCpp.EtatModele.MENU.ordinal());
		 * gestionnaireDeVue.ChangerVue(TypesVue.MENU); } else if
		 * (commande.contains("editeur")) {
		 * FacadeCpp.fctC_changerEtat(FacadeCpp.EtatModele.EDITEUR .ordinal());
		 * gestionnaireDeVue.ChangerVue(TypesVue.EDITEUR); } } else if
		 * (commande.contains("Ouvrir")) { try { String completePath =
		 * selectFile();
		 * 
		 * if (!FacadeCpp.fctC_ouvrirFichier(completePath)) { // S'il y a eu une
		 * erreur JOptionPane.showMessageDialog( gestionnaireDeVue.getFenetre(),
		 * "Le fichier " + completePath + " n'a pas pu être ouvert.",
		 * "Erreur d'ouverture du fichier.", JOptionPane.ERROR_MESSAGE); } }
		 * catch (CancellationException exception) { // L'action a été annulé }
		 * 
		 * 
		 * } else if (commande.contains("Enregistrer sous")) {
		 * FacadeCpp.fctC_buttonPressed("Escape"); try { String completePath =
		 * selectFile();
		 * 
		 * if (completePath.equals(fichierSauvegardeParDefaut)) {
		 * JOptionPane.showMessageDialog( gestionnaireDeVue.getFenetre(),
		 * "Le fichier " + completePath +
		 * " ne peut être écrasé. Choisissez un autre fichier.",
		 * "Erreur d'ouverture du fichier.", JOptionPane.ERROR_MESSAGE); } else
		 * if (!FacadeCpp.fctC_sauvegarderFichier(completePath)) { // S'il y a
		 * eu une erreur JOptionPane.showMessageDialog(
		 * gestionnaireDeVue.getFenetre(), "Le fichier " + completePath +
		 * " n'a pas pu être enregistré.",
		 * "Erreur d'enregistrement du fichier.", JOptionPane.ERROR_MESSAGE); }
		 * } catch (CancellationException exception) { // L'action a été annulé
		 * } } else if (commande.contains("Enregistrer")) {
		 * FacadeCpp.fctC_buttonPressed("Escape"); if
		 * (FacadeCpp.fctC_fichierSauvegardeEstDefini()) {
		 * FacadeCpp.fctC_sauvegarderFichier(""); } else { try { String
		 * completePath = selectFile();
		 * 
		 * if (completePath.equals(fichierSauvegardeParDefaut)) {
		 * JOptionPane.showMessageDialog( gestionnaireDeVue.getFenetre(),
		 * "Le fichier " + completePath +
		 * " ne peut être écrasé. Choisissez un autre fichier.",
		 * "Erreur d'ouverture du fichier.", JOptionPane.ERROR_MESSAGE); } else
		 * if (!FacadeCpp.fctC_sauvegarderFichier(completePath)) { // S'il y a
		 * eu une erreur JOptionPane.showMessageDialog(
		 * gestionnaireDeVue.getFenetre(), "Le fichier " + completePath +
		 * " n'a pas pu être enregistré.",
		 * "Erreur d'enregistrement du fichier.", JOptionPane.ERROR_MESSAGE); }
		 * } catch (CancellationException exception) { // L'action a été annulé
		 * } } } else if (commande.contains("Action: ")) { commande =
		 * commande.substring("Action: ".length());
		 * 
		 * // Envoyer commande FacadeCpp.fctC_buttonPressed(commande); } else if
		 * (commande.contains("Supprimer")) {
		 * FacadeCpp.fctC_buttonPressed(commande); }
		 */
	}
	
	public void keyPressed(int keyCode) {
		FacadeCpp.keyPressed(keyCode);
	}
	
	public void keyReleased(int keyCode) {
		switch (keyCode) {
		//case KeyEvent.VK_ESCAPE:
		//	FacadeCpp.fctC_changerEtat(FacadeCpp.EtatModele.EDITEUR.ordinal());
		//	break;
		default:
			FacadeCpp.keyReleased(keyCode);
			break;
		}
	}
}
