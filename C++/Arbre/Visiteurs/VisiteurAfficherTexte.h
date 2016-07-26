///////////////////////////////////////////////////////////////////////////
/// @file VisiteurAfficherTexte.h
/// @author Najib Arbaoui
/// @date 2014-04-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_VISITOR_VISITEURAFFICHERTEXTE_H__
#define __ARBRE_VISITOR_VISITEURAFFICHERTEXTE_H__

#include "Visiteurs\VisiteurAbstrait.h"

#include "AfficherTexte.h"

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
/// @class  VisiteurAfficherTexte
/// @brief Classe de visiteur qui permet d afficher du texte sur les noeuds 
/// stations spatiales
///
/// @author Najib Arbaoui
/// @date 2014-04-11
///////////////////////////////////////////////////////////////////////////
class VisiteurAfficherTexte : public VisiteurAbstrait
{
protected:
	AfficherTexte* afficherTexte_;

public:
	// Constructeur
	VisiteurAfficherTexte();

	// Destructeur
	~VisiteurAfficherTexte();


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


#endif //  __ARBRE_VISITOR_VISITEURAFFICHERTEXTE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
