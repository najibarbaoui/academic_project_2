#include "EtatActionDuplication.h"

#include "Vue.h"

EtatActionDuplication::EtatActionDuplication()
{
	this->id_ = 4;
	this->utiliseRectangleElastique_ = false;
}

void EtatActionDuplication::Activer()
{
	// créer objet curseur 
	curseur_ = static_cast<NoeudTamponPrevisualisation*> (FacadeModele::obtenirInstance()->creerNoeud(0, 0,ArbreRenduINF2990::NOM_TAMPONPREVISUALISATION ));
	
	curseur_->assignerAffiche(false);
	// créer objet croix
	croix_ = FacadeModele::obtenirInstance()->creerNoeud(0, 0, ArbreRenduINF2990::NOM_CURSEURCROIX);
	croix_->assignerAffiche(false);
}

void EtatActionDuplication::Desactiver()
{
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(curseur_);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(croix_);
}

void EtatActionDuplication::mouseMoved(int x, int y, bool ctrlPressed, bool altPressed)
{
		// Obtenir les bornes de sélection
	Vecteur3 bornesMinXY, bornesMaxXY;
    FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->trouverBornesSelection(bornesMinXY, bornesMaxXY);
	curseur_->tracerTampon(bornesMinXY,bornesMaxXY);

	// recupperer la position virtuelle du curseur
	Vecteur3 position, minXY, maxXY ;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, position);
	curseur_->assignerPositionRelative(position);
	
	curseur_->obtenirBoiteEnglobante(minXY, maxXY);
	
	//Afficher  le curseur si elle est  dans la zone de jeu
	if(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->estDansZoneJeu( minXY, maxXY))
		curseur_->assignerAffiche(true);
	else
	{
		curseur_->assignerAffiche(false);
		croix_->assignerAffiche(true);
	}


	// Gestion de l'objet croix qui apparaît si l'objet est à l'extérieur

	// recupperer la position virtuelle du curseur
	Vecteur3 positionCroix, minXYCroix, maxXYCroix ;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionCroix);
	croix_->assignerPositionRelative(positionCroix);

	//Obtenir la boite englobante de la croix
	croix_->obtenirBoiteEnglobante(minXYCroix, maxXYCroix);
	
	//Afficher la croix si elle est à l'extérieur de  la zone de jeu
	if(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->estDansZoneJeu( maxXYCroix, maxXYCroix))
	{
		if(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->estDansZoneJeu( minXY, maxXY))
		croix_->assignerAffiche(false);
	}
	else
	{
		croix_->assignerAffiche(true);
	}
}

void EtatActionDuplication::mousePressed(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
}

void EtatActionDuplication::mouseClicked(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
	// Convertir les coordonnées
	Vecteur3 position;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, position);

	// Dupliquer les noeuds
	FacadeModele::obtenirInstance()->dupliquerNoeuds(position);
}

void EtatActionDuplication::mouseDragged(int x, int y, int dx, int dy, bool ctrlPressed, bool altPressed)
{
}

void EtatActionDuplication::mouseReleased(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
}

void EtatActionDuplication::buttonPressed(string action)
{
}