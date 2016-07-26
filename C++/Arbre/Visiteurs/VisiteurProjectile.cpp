///////////////////////////////////////////////////////////////////////////
/// @file VisiteurProjectile.cpp
/// @author Najib Arbaoui
/// @date 2014-03-20
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurProjectile.h"

VisiteurProjectile::VisiteurProjectile(NoeudProjectile* noeud)
{
	noeudProjectile = noeud;
}

VisiteurProjectile::~VisiteurProjectile()
{
}

bool VisiteurProjectile::verifierCollision(NoeudAbstrait &noeud)
{
	if (noeudProjectile->isEnabled())
	{
		Vecteur3 positionProjectile = noeudProjectile->obtenirPositionRelative();
		double rayonProjectile = noeudProjectile->obtenirSphereEnglobante();

		Vecteur3 positionObjet = noeud.obtenirPositionRelative();
		double rayonObjet = noeud.obtenirSphereEnglobante();

		if ((positionProjectile - positionObjet).norme() < (rayonProjectile + rayonObjet))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

void VisiteurProjectile::visiter(NoeudAbstrait& noeudAbstrait)
{
}

void VisiteurProjectile::visiter(NoeudComposite& noeudComposite)
{
	for(unsigned int i = 0; i < noeudComposite.obtenirNombreEnfants(); ++i)
	{
		noeudComposite.chercher(i)->accepter(*this);
	}
}

void VisiteurProjectile::visiter(NoeudAsteroide & noeudAsteroide)
{
	if (verifierCollision(noeudAsteroide))
	{
		// D�truire projectile
		noeudProjectile->detruire();

		// Perdre un point de vie � l'asteroide
		noeudAsteroide.baisserPointsDeVie();
	}
}

void VisiteurProjectile::visiter(NoeudBarriereProtectrice & noeudBarriereProtectrice)
{
	// Ne pas consid�rer.

	// �tant donn� la complexit� de v�rifier la collision entre le projectile et la barri�re protectrice,
	// c'est le VisiteurBarri�reProtectrice qui s'en occupe
}

void VisiteurProjectile::visiter(NoeudBonusAccelerateur & noeudBonusAccelerateur )
{
}

void VisiteurProjectile::visiter(NoeudPortail & noeudPortail)
{
}

void VisiteurProjectile::visiter(NoeudPositionDepart & noeudPositionDepart )
{
}

void VisiteurProjectile::visiter(NoeudProjectile & noeudProjectile ) 
{
}

void VisiteurProjectile::visiter(NoeudStationSpatiale & noeudStationSpatiale)
{
	if (noeudStationSpatiale.isEnabled())
	{
		if (verifierCollision(noeudStationSpatiale))
		{
			// D�truire projectile
			noeudProjectile->detruire();

			// Perdre un point de vie � la station spatiale
			noeudStationSpatiale.baisserPointsDeVie();
		}
	}
}

void VisiteurProjectile::visiter(NoeudVaisseau & noeudVaisseau)
{
	if (verifierCollision(noeudVaisseau))
	{
		// D�truire projectile
		noeudProjectile->detruire();

		// Etourdissement sur le vaisseau
		noeudVaisseau.toggleEtourdi();
	}
}

void VisiteurProjectile::visiter(NoeudZoneJeu & noeudZoneJeu )
{
}

void VisiteurProjectile::visiter(NoeudZonePassage & noeudZonePassage )
{
}

void VisiteurProjectile::visiter(NoeudAnimation & noeudAnimation )
{

}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////