///////////////////////////////////////////////////////////////////////////
/// @file VisiteurCollisionSphereSphere.cpp
/// @author Najib Arbaoui
/// @date 2014-03-17
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurCollisionSphereSphere.h"

#include "ArbreRenduINF2990.h"
#include "utilitaire.h"
#include "GestionnaireAudio.h"

VisiteurCollisionSphereSphere::VisiteurCollisionSphereSphere(NoeudAbstrait* noeud)
{
	this->noeudSphere = noeud;
}

VisiteurCollisionSphereSphere::~VisiteurCollisionSphereSphere()
{
}

void VisiteurCollisionSphereSphere::verifierCollision(NoeudAbstrait &noeud)
{
	if (&noeud != noeudSphere)
	{
		double distance2 = (noeudSphere->obtenirPositionRelative() - noeud.obtenirPositionRelative()).norme2();
		double rayon = noeud.obtenirSphereEnglobante() + noeudSphere->obtenirSphereEnglobante();

		if (rayon * rayon > distance2)
		{
			Vecteur3 position1 = noeudSphere->obtenirPositionRelative();
			Vecteur3 position2 = noeud.obtenirPositionRelative();

			aidecollision::DetailsCollision* details = new aidecollision::DetailsCollision();

			aidecollision::calculerCollisionSphere(
				position1,
				noeudSphere->obtenirSphereEnglobante(),
				position2,
				noeud.obtenirSphereEnglobante(),
				1,
				1,
				noeudSphere->obtenirVitesse(),
				details
			);

			if (details->type != aidecollision::COLLISION_AUCUNE)
			{
				resoudreCollisionElastique(noeudSphere, &noeud, details);
			}
		}
	}
}

void VisiteurCollisionSphereSphere::resoudreCollisionElastique(NoeudAbstrait* noeud1, NoeudAbstrait* noeud2, aidecollision::DetailsCollision* detail)
{
	assert(noeud1->obtenirMasse() != 0);
	assert(noeud2->obtenirMasse() != 0);

	double somme = noeud1->obtenirMasse() + noeud2->obtenirMasse();
	double ratio1 = noeud2->obtenirMasse()/somme;
	double ratio2 = noeud1->obtenirMasse()/somme;

	Vecteur3 direction = detail->direction;
	direction.normaliser();

	noeud1->assignerPositionRelative(noeud1->obtenirPositionRelative() - direction*detail->enfoncement*ratio1);
	noeud2->assignerPositionRelative(noeud2->obtenirPositionRelative() + direction*detail->enfoncement*ratio2);

	// Si collision contre station spatiale
	if (noeud2->obtenirMasse() == DBL_MAX)
	{
		if (noeud1->obtenirType() == ArbreRenduINF2990::NOM_ASTEROIDE)
		{
			static_cast<NoeudAsteroide*>(noeud1)->devierTrajectoire(direction);
			static_cast<NoeudStationSpatiale*>(noeud2)->baisserPointsDeVie();
		}
		else if (noeud1->obtenirType() == ArbreRenduINF2990::NOM_VAISSEAU)
		{
			static_cast<NoeudVaisseau*>(noeud1)->devierTrajectoire(direction);
		}
	}
	else
	{
		// Calcul de la base orthonorm�e (n,g)
		// n est perpendiculaire au plan de collision, g est tangent
		Vecteur3 position1 = noeud1->obtenirPositionRelative();
		Vecteur3 position2 = noeud2->obtenirPositionRelative();
		Vecteur3 vitesse1 = noeud1->obtenirVitesse();
		Vecteur3 vitesse2 = noeud2->obtenirVitesse();

		double nx = (position2[0] - position1[0])/(noeud1->obtenirSphereEnglobante() + noeud2->obtenirSphereEnglobante());
		double ny = (position2[1] - position1[1])/(noeud1->obtenirSphereEnglobante() + noeud2->obtenirSphereEnglobante());
		double gx = -ny;
		double gy = nx;
 
		// Calcul des vitesses dans cette base
		double v1n = nx*vitesse1[0] + ny*vitesse1[1];
		double v1g = gx*vitesse1[0] + gy*vitesse1[1];
		double v2n = nx*vitesse2[0] + ny*vitesse2[1];
		double v2g = gx*vitesse2[0] + gy*vitesse2[1];
 
		// Permute les coordonn�es n et conserve la vitesse tangentielle
		// Ex�cute la transformation inverse (base orthonorm�e => matrice transpos�e)
		vitesse1[0] = nx*v2n +  gx*v1g;
		vitesse1[1] = ny*v2n +  gy*v1g;
		vitesse2[0] = nx*v1n +  gx*v2g;
		vitesse2[1] = ny*v1n +  gy*v2g;

		if (!utilitaire::ALMOST_EQUALS(ratio1, ratio2))
		{
			if (ratio2 > ratio1)
			{
				vitesse1 *= 0.8;
				vitesse2 *= 1.4;
			}
			else
			{
				vitesse1 *= 1.4;
				vitesse2 *= 0.8;
			}
		}

		noeud1->assignerVitesse(vitesse1);
		noeud2->assignerVitesse(vitesse2);

		if (noeud1->obtenirType() == ArbreRenduINF2990::NOM_VAISSEAU && noeud2->obtenirType() != ArbreRenduINF2990::NOM_VAISSEAU)
		{
			static_cast<NoeudVaisseau*>(noeud1)->toggleEtourdi();
		}
		else if (noeud2->obtenirType() == ArbreRenduINF2990::NOM_VAISSEAU && noeud1->obtenirType() != ArbreRenduINF2990::NOM_VAISSEAU)
		{
			static_cast<NoeudVaisseau*>(noeud2)->toggleEtourdi();
		}
	}

	// jouer son de collision
	GestionnaireAudio::obtenirInstance()->jouerAudioCollision();
}

void VisiteurCollisionSphereSphere::visiter(NoeudAbstrait& noeudAbstrait)
{
}

void VisiteurCollisionSphereSphere::visiter(NoeudComposite& noeudComposite)
{
	for(unsigned int i = 0; i < noeudComposite.obtenirNombreEnfants(); ++i)
	{
		noeudComposite.chercher(i)->accepter(*this);
	}
}

void VisiteurCollisionSphereSphere::visiter(NoeudAsteroide & noeudAsteroide)
{
	verifierCollision(noeudAsteroide);
}

void VisiteurCollisionSphereSphere::visiter(NoeudBarriereProtectrice & noeudBarriereProtectrice)
{
}

void VisiteurCollisionSphereSphere::visiter(NoeudBonusAccelerateur & noeudBonusAccelerateur )
{
}

void VisiteurCollisionSphereSphere::visiter(NoeudPortail & noeudPortail)
{		
}

void VisiteurCollisionSphereSphere::visiter(NoeudPositionDepart & noeudPositionDepart )
{
}

void VisiteurCollisionSphereSphere::visiter(NoeudProjectile & noeudProjectile ) 
{
}

void VisiteurCollisionSphereSphere::visiter(NoeudStationSpatiale & noeudStationSpatiale)
{
	if (noeudStationSpatiale.isEnabled())
	{
		verifierCollision(noeudStationSpatiale);
	}
}

void VisiteurCollisionSphereSphere::visiter(NoeudVaisseau & noeudVaisseau)
{
	verifierCollision(noeudVaisseau);
}

void VisiteurCollisionSphereSphere::visiter(NoeudZoneJeu & noeudZoneJeu )
{
}

void VisiteurCollisionSphereSphere::visiter(NoeudZonePassage & noeudZonePassage )
{
}

void VisiteurCollisionSphereSphere::visiter(NoeudAnimation & noeudAnimation )
{

}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////