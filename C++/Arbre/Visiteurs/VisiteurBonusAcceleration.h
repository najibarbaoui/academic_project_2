///////////////////////////////////////////////////////////////////////////
/// @file VisiteurBonusAcceleration.h
/// @author Najib Arbaoui
/// @date 2014-03-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_VISITOR_VISITEURBONUSACCELERATION_H__
#define  __ARBRE_VISITOR_VISITEURBONUSACCELERATION_H__

#include "Visiteurs\VisiteurAbstrait.h"
#include "ArbreRenduINF2990.h"

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
/// @class  VisiteurBonusAcceleration
/// @brief Classe de visiteur qui permet d'appliquer le bonus d'acceleration aux vaisseaux
///
/// @author Najib Arbaoui
/// @date 2014-03-15
///////////////////////////////////////////////////////////////////////////
class VisiteurBonusAcceleration : public VisiteurAbstrait
{
protected:
	NoeudBonusAccelerateur* noeudBonusAccelerateur;
public:
	// Constructeur
	VisiteurBonusAcceleration(NoeudBonusAccelerateur* noeud);

	// Destructeur
	~VisiteurBonusAcceleration();
	
	void appliquerBonusAcceleration(NoeudVaisseau &noeud);

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


#endif //  __ARBRE_VISITOR_VISITEURBONUSACCELERATION_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
