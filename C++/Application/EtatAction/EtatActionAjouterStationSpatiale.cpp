#include "EtatActionAjouterStationSpatiale.h"

#include "Vue.h"

EtatActionAjouterStationSpatiale::EtatActionAjouterStationSpatiale()
{
	this->id_ = 6;
	this->utiliseRectangleElastique_ = false;
}

void EtatActionAjouterStationSpatiale::Activer()
{
	// cr�er objet curseur 
	curseur_ = FacadeModele::obtenirInstance()->creerNoeud(0, 0, ArbreRenduINF2990::NOM_STATIONSPATIALE);
	curseur_->assignerAffiche(false);
	
	// cr�er objet croix
	croix_ = FacadeModele::obtenirInstance()->creerNoeud(0, 0, ArbreRenduINF2990::NOM_CURSEURCROIX);
	croix_->assignerAffiche(false);
}

void EtatActionAjouterStationSpatiale::Desactiver()
{
	 FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(curseur_);
	 FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(croix_);
}

void EtatActionAjouterStationSpatiale::mouseMoved(int x, int y, bool ctrlPressed, bool altPressed)
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

void EtatActionAjouterStationSpatiale::mousePressed(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
}

void EtatActionAjouterStationSpatiale::mouseClicked(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
	// Convertir les coordonn�es
	Vecteur3 position;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, position);

	// Cr�er le noeud � la position cliqu�e
	FacadeModele::obtenirInstance()->creerNoeud(position[0], position[1], ArbreRenduINF2990::NOM_STATIONSPATIALE);
}

void EtatActionAjouterStationSpatiale::mouseDragged(int x, int y, int dx, int dy, bool ctrlPressed, bool altPressed)
{
}

void EtatActionAjouterStationSpatiale::mouseReleased(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
}

void EtatActionAjouterStationSpatiale::buttonPressed(string action)
{
}