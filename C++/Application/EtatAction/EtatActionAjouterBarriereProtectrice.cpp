#include "EtatActionAjouterBarriereProtectrice.h"

#include "Vue.h"

EtatActionAjouterBarriereProtectrice::EtatActionAjouterBarriereProtectrice()
{
	this->id_ = 8;
	this->utiliseRectangleElastique_ = false;
}

void EtatActionAjouterBarriereProtectrice::Activer()
{
	barriereCree_ = NULL;
}

void EtatActionAjouterBarriereProtectrice::Desactiver()
{
	if(compteClique_ == 1)
	{
		// Effacer la barrière créée et réinitialiser le compteur de cliques
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(barriereCree_);
		compteClique_ = 0;
	}
}

void EtatActionAjouterBarriereProtectrice::mouseMoved(int x, int y, bool ctrlPressed, bool altPressed)
{
	// Recupère la position virtuelle de la souris
	Vecteur3 position;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, position);

	// Affiche la barrière protectrice depuis le premier clique jusqu'au curseur
	if(compteClique_ == 1)
	{
		Vecteur3 pointDebut, pointFin;
		static_cast<NoeudBarriereProtectrice*>(barriereCree_)->obtenirExtremites(pointDebut, pointFin);

		static_cast<NoeudBarriereProtectrice*>(barriereCree_)->finaliserBarriere(premierClique_, position);
	}
}

void EtatActionAjouterBarriereProtectrice::mousePressed(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
}

void EtatActionAjouterBarriereProtectrice::mouseClicked(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
	if (compteClique_ == 0)
	{
		//Vecteur3 position;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, premierClique_);

		// Créer le noeud à la position cliquée
		barriereCree_ = FacadeModele::obtenirInstance()->creerNoeud(premierClique_[0], premierClique_[1], ArbreRenduINF2990::NOM_BARRIEREPROTECTRICE);

		// Vérifie si le clique est correcte
		if (barriereCree_ != NULL)
		{
			// Incrémenter compteur
			compteClique_++;
		}
	} 
	else if(compteClique_ == 1) 
	{
		Vecteur3 position;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, position);

		static_cast<NoeudBarriereProtectrice*>(barriereCree_)->finaliserBarriere(premierClique_, position);

		Vecteur3 minXY, maxXY;
		barriereCree_->obtenirBoiteEnglobante(minXY, maxXY);

		if (!FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->estDansZoneJeu(minXY, maxXY)) {
			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(barriereCree_);
			
		} 

		compteClique_= 0;
	}
}

void EtatActionAjouterBarriereProtectrice::mouseDragged(int x, int y, int dx, int dy, bool ctrlPressed, bool altPressed)
{
}

void EtatActionAjouterBarriereProtectrice::mouseReleased(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
}

void EtatActionAjouterBarriereProtectrice::buttonPressed(string action)
{
	if (action == "Annuler" && compteClique_ == 1)
	{
		// Effacer la barrière créée et réinitialiser le compteur de cliques
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(barriereCree_);
		compteClique_ = 0;
	}
}