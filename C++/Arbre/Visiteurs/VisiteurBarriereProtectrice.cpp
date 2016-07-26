///////////////////////////////////////////////////////////////////////////
/// @file VisiteurBarriereProtectrice.cpp
/// @author Najib Arbaoui
/// @date 2014-03-17
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurBarriereProtectrice.h"

#include "Utilitaire.h"
#include "ArbreRenduINF2990.h"

VisiteurBarriereProtectrice::VisiteurBarriereProtectrice(NoeudBarriereProtectrice* noeud)
{
	noeudBarriereProtectrice = noeud;
	noeudBarriereProtectrice->obtenirVertices(vertices_, size_);

	// Calculer les projections imm�diatement
	Vecteur3 axe1, axe2;
	noeudBarriereProtectrice->obtenirAxes(axe1, axe2);

	double min = utilitaire::appliquerProjection(axe1, vertices_[0]);
	double max = min;

	for (int i=1; i<size_; i++)
	{
		double val = utilitaire::appliquerProjection(axe1, vertices_[i]);
		if (val < min) {
			min = val;
		} else if (val > max) {
			max = val;
		}
	}

	minAxe1_ = min;
	maxAxe1_ = max;

	min = utilitaire::appliquerProjection(axe2, vertices_[0]);
	max = min;

	for (int i=1; i<size_; i++)
	{
		double val = utilitaire::appliquerProjection(axe2, vertices_[i]);
		if (val < min) {
			min = val;
		} else if (val > max) {
			max = val;
		}
	}

	minAxe2_ = min;
	maxAxe2_ = max;
}

VisiteurBarriereProtectrice::~VisiteurBarriereProtectrice()
{
}

void VisiteurBarriereProtectrice::verifierCollision(NoeudAbstrait &noeud)
{
	// Ne rien faire si une collision AABB n'est pas d�tect�
	if (this->collisionAABB(noeud))
	{
		/// Separating Axis Theorem
		// Obtient les axes de projection � tester
		Vecteur3 axes[2];
		noeudBarriereProtectrice->obtenirAxes(axes[0], axes[1]);

		double penetrationResponse[2];

		// Obtient les deux points du noeud auxquels appliquer la projection. On prend toujours la sph�re englobante.
		Vecteur3 position = noeud.obtenirPositionRelative();

		double rayon = noeud.obtenirSphereEnglobante();

		// Pour les deux axes
		for (int i=0; i<2; i++)
		{
			Vecteur3 point1 = position - rayon*axes[i];
			Vecteur3 point2 = position + rayon*axes[i];
	
			double min = utilitaire::appliquerProjection(axes[i], point1);
			double max = min;

			double val = utilitaire::appliquerProjection(axes[i], point2);
			if (val < min)
				min = val;
			else if (val > max)
				max = val;
		
			double minAxe, maxAxe;
			if (i == 0)
			{
				minAxe = minAxe1_;
				maxAxe = maxAxe1_;
			}
			else
			{
				minAxe = minAxe2_;
				maxAxe = maxAxe2_;
			}
				
			double penetrationGauche = max - minAxe;
			double penetrationDroite = maxAxe - min;

			if ( !(penetrationGauche > 0 && penetrationDroite > 0) )
			{
				return;
			}

			if (penetrationGauche == min(penetrationGauche, penetrationDroite))
			{
				penetrationResponse[i] = -penetrationGauche;
			}
			else
			{
				penetrationResponse[i] = penetrationDroite;

			}
		}

		// On se rend ici, �a veut dire que les objets se touchent
		if (noeud.obtenirType() == ArbreRenduINF2990::NOM_PROJECTILE)
		{
			static_cast<NoeudProjectile*>(&noeud)->detruire();
		}
		else if (noeud.obtenirType() == ArbreRenduINF2990::NOM_VAISSEAU || noeud.obtenirType() == ArbreRenduINF2990::NOM_ASTEROIDE)
		{
			Vecteur3 axe;
			double enfoncement;

			// S�lectionne la plus petite p�n�tration. C'est celle-ci qu'on consid�rera
			if (min(abs(penetrationResponse[0]), abs(penetrationResponse[1])) == abs(penetrationResponse[0]))
			{
				axe = axes[0];
				enfoncement = penetrationResponse[0];
			}
			else
			{
				axe = axes[1];
				enfoncement = penetrationResponse[1];
			}

			// Si la r�ponse est n�gative, �a veut dire que la collision s'est retrouv�e de l'autre c�t� de la barri�re protectrice
			if (enfoncement < 0)
			{
				// On inverse l'axe et remet la r�ponse positive
				axe *= -1;
				enfoncement = -enfoncement;
			}

			// On applique l'inverse de la p�n�tration
			noeud.assignerPositionRelative(noeud.obtenirPositionRelative() + enfoncement*axe);

			// Appliquer la r�ponse � la collision
			if (noeud.obtenirType() == ArbreRenduINF2990::NOM_ASTEROIDE)
			{
				static_cast<NoeudAsteroide*>(&noeud)->devierTrajectoire(axe);
			}
			else
			{
				static_cast<NoeudVaisseau*>(&noeud)->devierTrajectoire(axe);
			}
		}
	}
}


bool VisiteurBarriereProtectrice::collisionAABB(NoeudAbstrait &noeud)
{
	// Ne pas faire si une collision AABB n'est pas d�tect�
	Vecteur3 minXY, maxXY, barriereMinXY, barriereMaxXY;
	noeud.obtenirBoiteEnglobante(minXY, maxXY);
	noeudBarriereProtectrice->obtenirBoiteEnglobante(barriereMinXY, barriereMaxXY);

	return utilitaire::AABB_COLLISION(minXY, maxXY, barriereMinXY, barriereMaxXY);
}

void VisiteurBarriereProtectrice::visiter(NoeudAbstrait& noeudAbstrait)
{
}

void VisiteurBarriereProtectrice::visiter(NoeudComposite& noeudComposite)
{
	for(unsigned int i = 0; i < noeudComposite.obtenirNombreEnfants(); ++i)
	{
		noeudComposite.chercher(i)->accepter(*this);
	}
}

void VisiteurBarriereProtectrice::visiter(NoeudAsteroide & noeudAsteroide)
{
	verifierCollision(noeudAsteroide);
}

void VisiteurBarriereProtectrice::visiter(NoeudBarriereProtectrice & noeudBarriereProtectrice)
{
}

void VisiteurBarriereProtectrice::visiter(NoeudBonusAccelerateur & noeudBonusAccelerateur )
{
}

void VisiteurBarriereProtectrice::visiter(NoeudPortail & noeudPortail)
{		
}

void VisiteurBarriereProtectrice::visiter(NoeudPositionDepart & noeudPositionDepart )
{
}

void VisiteurBarriereProtectrice::visiter(NoeudProjectile & noeudProjectile ) 
{
	verifierCollision(noeudProjectile);
}

void VisiteurBarriereProtectrice::visiter(NoeudStationSpatiale & noeudStationSpatiale)
{
}

void VisiteurBarriereProtectrice::visiter(NoeudVaisseau & noeudVaisseau)
{
	verifierCollision(noeudVaisseau);
}

void VisiteurBarriereProtectrice::visiter(NoeudZoneJeu & noeudZoneJeu )
{
}

void VisiteurBarriereProtectrice::visiter(NoeudZonePassage & noeudZonePassage )
{
}


void VisiteurBarriereProtectrice::visiter(NoeudAnimation & noeudAnimation )
{

}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////