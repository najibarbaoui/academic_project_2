///////////////////////////////////////////////////////////////////////////
/// @file VisiteurAIChercheCible.h
/// @author Najib Arbaoui
/// @date 2014-03-24
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_VISITOR_VISITEURAICHERCHECIBLE_H__
#define  __ARBRE_VISITOR_VISITEURAICHERCHECIBLE_H__

#include "Visiteurs\VisiteurAbstrait.h"

#include "Noeuds/NoeudAbstrait.h"
#include "Noeuds/NoeudAsteroide.h"
#include "Noeuds/NoeudBarriereProtectrice.h"
#include "Noeuds/NoeudBonusAccelerateur.h"
#include "Noeuds/NoeudComposite.h"
#include "Noeuds/NoeudPortail.h"
#include "Noeuds/NoeudPositionDepart.h"
#include "Noeuds/NoeudProjectile.h"
#include "Noeuds/NoeudStationSpatiale.h"
#include "Noeuds/NoeudVaisseau.h"
#include "Noeuds/NoeudZoneJeu.h"
#include "Noeuds/NoeudZonePassage.h"
#include "Noeuds/NoeudAnimation.h"

///////////////////////////////////////////////////////////////////////////
/// @class  VisiteurAIChercheCible
/// @brief Classe de visiteur qui permet de rechercher une cible
///
/// @author Najib Arbaoui
/// @date 2014-03-24
///////////////////////////////////////////////////////////////////////////
class VisiteurAIChercheCible : public VisiteurAbstrait
{
protected:
	NoeudVaisseau* vaisseau_;
	NoeudAsteroide* cible_;

	double distanceCible_;

public:
	// Constructeur
	VisiteurAIChercheCible(NoeudVaisseau* noeud);

	// Destructeur
	~VisiteurAIChercheCible();

	NoeudAsteroide* obtenirCible();

	virtual void visiter(NoeudAbstrait & noeudAbstrait);
	virtual void visiter(NoeudComposite & noeudComposite);

	virtual void visiter(NoeudAsteroide & noeudAsteroide);
	virtual void visiter(NoeudBarriereProtectrice & noeudBarriereProtectrice);
	virtual void visiter(NoeudBonusAccelerateur & noeudBonusAccelerateur );
	virtual void visiter(NoeudPortail & noeudPortail);
	virtual void visiter(NoeudPositionDepart & noeudPositionDepart );
	virtual void visiter(NoeudProjectile & noeudProjectile );
	virtual void visiter(NoeudStationSpatiale & noeudStationSpatiale);
	virtual void visiter(NoeudVaisseau & noeudVaisseau);
	virtual void visiter(NoeudZoneJeu & noeudZoneJeu );
	virtual void visiter(NoeudZonePassage & noeudZonePassage );
	virtual void visiter(NoeudAnimation & noeudAnimation );
};


#endif //  __ARBRE_VISITOR_VISITEURAICHERCHECIBLE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
