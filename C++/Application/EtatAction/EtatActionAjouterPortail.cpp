#include "EtatActionAjouterPortail.h"

#include "Vue.h"

EtatActionAjouterPortail::EtatActionAjouterPortail()
{
	this->id_ = 9;
	this->utiliseRectangleElastique_ = false;
}

void EtatActionAjouterPortail::Activer()
{
	premierPortail = NULL;
	// créer objet curseur 
	curseur_ = FacadeModele::obtenirInstance()->creerNoeud(0, 0, ArbreRenduINF2990::NOM_PORTAIL);
	curseur_->assignerAffiche(false);
	
	// créer objet croix
	croix_ = FacadeModele::obtenirInstance()->creerNoeud(0, 0, ArbreRenduINF2990::NOM_CURSEURCROIX);
	croix_->assignerAffiche(false);
}

void EtatActionAjouterPortail::Desactiver()
{
	if (compteClique_ == 1)
	{
		// Effacer le premier noeud et réinitialiser le compteur de cliques
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(premierPortail);
		compteClique_ = 0;
	}
	 
	
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(curseur_);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(croix_);
}

void EtatActionAjouterPortail::mouseMoved(int x, int y, bool ctrlPressed, bool altPressed)
{
	// recupperer la position virtuelle du curseur
	Vecteur3 position, minXY, maxXY ;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, position);
	curseur_->assignerPositionRelative(position);
	croix_->assignerPositionRelative(position);
	
	//Obtenir la boite englobante de l'objet
	curseur_->obtenirBoiteEnglobante(minXY, maxXY);
	
	//Afficher le curseur si il est dans la zone de jeu, sinon affiche la croix
	if(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->estDansZoneJeu( minXY, maxXY))
	{
		curseur_->assignerAffiche(true);
		croix_->assignerAffiche(false);
	}
	else
	{
		curseur_->assignerAffiche(false);
		croix_->assignerAffiche(true);
	}
}

void EtatActionAjouterPortail::mousePressed(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
}

void EtatActionAjouterPortail::mouseClicked(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
	if (compteClique_ == 0)
	{
		/// Création du premier portail
		Vecteur3 position;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, position);

		// Créer le noeud à la position cliquée
		premierPortail = FacadeModele::obtenirInstance()->creerNoeud(position[0], position[1], ArbreRenduINF2990::NOM_PORTAIL);

		// Vérifie si le clique est correcte
		if (premierPortail != NULL)
		{
			// Incrémenter compteur
			compteClique_++;
		}
	}
	else if (compteClique_ == 1)
	{
		/// Création du deuxième portail
		Vecteur3 position;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, position);

		// Créer le noeud à la position cliquée
		NoeudAbstrait* secondPortail = FacadeModele::obtenirInstance()->creerNoeud(position[0], position[1], ArbreRenduINF2990::NOM_PORTAIL);
		
		// Vérifie si le clique est correcte
		if (secondPortail != NULL)
		{
			// Réinitialiser compteur
			compteClique_ = 0;

			// Assigner les pointeurs des portails reliés
			((NoeudPortail*)secondPortail)->assignerPortailFrere(premierPortail);
			((NoeudPortail*)premierPortail)->assignerPortailFrere(secondPortail);
		}
	}
}

void EtatActionAjouterPortail::mouseDragged(int x, int y, int dx, int dy, bool ctrlPressed, bool altPressed)
{
}

void EtatActionAjouterPortail::mouseReleased(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
}

void EtatActionAjouterPortail::buttonPressed(string action)
{
	if (action == "Annuler" && compteClique_ == 1)
	{
		// Effacer le premier noeud et réinitialiser le compteur de cliques
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(premierPortail);
		compteClique_ = 0;
	}
}