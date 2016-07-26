///////////////////////////////////////////////////////////////////////////
/// @file VisiteurAIStationDansFace.cpp
/// @author Najib Arbaoui
/// @date 2014-03-24
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurAIStationDansFace.h"

#include "ArbreRenduINF2990.h"
#include "FacadeModele.h"

VisiteurAIStationDansFace::VisiteurAIStationDansFace(NoeudVaisseau* noeud)
{
	vaisseau_ = noeud;

	stationDansFace_ = false;
}

VisiteurAIStationDansFace::~VisiteurAIStationDansFace()
{
}

void VisiteurAIStationDansFace::verifierSiDansFace(NoeudAbstrait* noeudAbstrait)
{
	// Calcule la diff�rence d'angle, et s'assure que l'angle est entre -180 et 180 degr�s
	Vecteur3 direction = (noeudAbstrait->obtenirPositionRelative() - vaisseau_->obtenirPositionRelative());
	double angleVersCible = utilitaire::RAD_TO_DEG(direction.lireTheta());
	double angleVaisseau = vaisseau_->getAngleRotation();
	double differenceAngle = angleVersCible - angleVaisseau;// + 90;
	differenceAngle = fmod(differenceAngle, 360);
	if (differenceAngle > 180)
	{
		differenceAngle -= 360;
	}
	else if (differenceAngle < -180)
	{
		differenceAngle += 360;
	}

	if (differenceAngle < 10 && differenceAngle > -10)
	{
		stationDansFace_ = true;
	}
}

bool VisiteurAIStationDansFace::obtenirStationDansFace()
{
	return stationDansFace_;
}

void VisiteurAIStationDansFace::visiter(NoeudAbstrait& noeudAbstrait)
{
}

void VisiteurAIStationDansFace::visiter(NoeudComposite& noeudComposite)
{
	for(unsigned int i = 0; i < noeudComposite.obtenirNombreEnfants(); ++i)
	{
		noeudComposite.chercher(i)->accepter(*this);
	}
}

void VisiteurAIStationDansFace::visiter(NoeudAsteroide & noeudAsteroide)
{
}

void VisiteurAIStationDansFace::visiter(NoeudBarriereProtectrice & noeudBarriereProtectrice)
{
}

void VisiteurAIStationDansFace::visiter(NoeudBonusAccelerateur & noeudBonusAccelerateur )
{
}

void VisiteurAIStationDansFace::visiter(NoeudPortail & noeudPortail)
{		
}

void VisiteurAIStationDansFace::visiter(NoeudPositionDepart & noeudPositionDepart )
{
}

void VisiteurAIStationDansFace::visiter(NoeudProjectile & noeudProjectile ) 
{
}

void VisiteurAIStationDansFace::visiter(NoeudStationSpatiale & noeudStationSpatiale)
{
	this->verifierSiDansFace(&noeudStationSpatiale);
}

void VisiteurAIStationDansFace::visiter(NoeudVaisseau & noeudVaisseau)
{
	if (vaisseau_ != &noeudVaisseau)
	{
		this->verifierSiDansFace(&noeudVaisseau);
	}
}

void VisiteurAIStationDansFace::visiter(NoeudZoneJeu & noeudZoneJeu )
{
}

void VisiteurAIStationDansFace::visiter(NoeudZonePassage & noeudZonePassage )
{
}

void VisiteurAIStationDansFace::visiter(NoeudAnimation & noeudAnimation )
{

}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////