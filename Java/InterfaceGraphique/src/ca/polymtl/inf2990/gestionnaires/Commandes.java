package ca.polymtl.inf2990.gestionnaires;

public class Commandes {
	enum Commande {
		/// Menu principal
		CAMPAGNE, PARTIERAPIDE, CONFIGURATION, EDITEUR, QUITTER,
		
		/// Éditeur
		// Menu Fichier
		NOUVEAU, OUVRIR, ENREGISTRER, ENREGISTRERSOUS, PROPRIETES, MODETEST, MENUPRINCIPAL,
		
		// Menu Édition
		SUPPRIMER,
		
		// Menu Outils
		SELECTION, DEPLACEMENT, ROTATION, MISEAECHELLE, DUPLICATION, ZOOM,
		
		// Sous-menu Creation d'objets
		AJOUTERBONUSACCELERATEUR, AJOUTERPORTAILS, AJOUTERBARRIEREPROTECTRICE, AJOUTERSTATIONSPATIALE,
		
		// Menu Vues
		ORTHOGRAPHIQUE, ORBITE,
		
		// Menu Informations
		Aide
	};
}
