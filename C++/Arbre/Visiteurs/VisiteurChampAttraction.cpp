///////////////////////////////////////////////////////////////////////////
/// @file VisiteurChampAttraction.cpp
/// @author Najib Arbaoui
/// @date 2014-03-14
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurChampAttraction.h"
#include "GestionnaireAudio.h"

VisiteurChampAttraction::VisiteurChampAttraction(NoeudPortail* portail)
{
	portail_ = portail;
}

VisiteurChampAttraction::~VisiteurChampAttraction()
{
}

void VisiteurChampAttraction::appliquerChampAttraction(NoeudAbstrait &noeudAbstrait)
{
	// Distance vaisseau/portail
	double distance = (noeudAbstrait.getPosition() - this->portail_->getPosition()).norme();

	// Teleporter
	if (distance < portail_->obtenirSphereEnglobante()/2)
	{
		// T�l�porte et d�sactive le portail de destination
		static_cast<NoeudPortail*>(this->portail_->obtenirPortailFrere())->teleporterNoeud(&noeudAbstrait);
		GestionnaireAudio::obtenirInstance()->jouerAudioUtilisationPortail();
	}
	// Champ d'attraction
	else if (distance < 3*portail_->obtenirSphereEnglobante())
	{
		// Calcule une force et une orientation de la force
		double force = 300000/(noeudAbstrait.obtenirMasse()*distance);
		Vecteur3 orientation = this->portail_->getPosition() - noeudAbstrait.getPosition();
		orientation.normaliser();

		noeudAbstrait.appliquerForce(orientation * force);
	}
}

void VisiteurChampAttraction::visiter(NoeudAbstrait& noeudAbstrait)
{
}

void VisiteurChampAttraction::visiter(NoeudComposite& noeudComposite)
{
	for(unsigned int i = 0; i < noeudComposite.obtenirNombreEnfants(); ++i)
	{
		noeudComposite.chercher(i)->accepter(*this);
	}
}

void VisiteurChampAttraction::visiter(NoeudAsteroide & noeudAsteroide)
{
	appliquerChampAttraction(noeudAsteroide);
	noeudAsteroide.setCoteOuCree(0);
}

void VisiteurChampAttraction::visiter(NoeudBarriereProtectrice & noeudBarriereProtectrice)
{
}

void VisiteurChampAttraction::visiter(NoeudBonusAccelerateur & noeudBonusAccelerateur )
{
}

void VisiteurChampAttraction::visiter(NoeudPortail & noeudPortail)
{			
}

void VisiteurChampAttraction::visiter(NoeudPositionDepart & noeudPositionDepart )
{
}

void VisiteurChampAttraction::visiter(NoeudProjectile & noeudProjectile ) 
{
	appliquerChampAttraction(noeudProjectile);
}

void VisiteurChampAttraction::visiter(NoeudStationSpatiale & noeudStationSpatiale)
{
}

void VisiteurChampAttraction::visiter(NoeudVaisseau & noeudVaisseau)
{
	appliquerChampAttraction(noeudVaisseau);
}

void VisiteurChampAttraction::visiter(NoeudZoneJeu & noeudZoneJeu )
{
}

void VisiteurChampAttraction::visiter(NoeudZonePassage & noeudZonePassage )
{
}
void VisiteurChampAttraction::visiter(NoeudAnimation & noeudAnimation )
{

}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////