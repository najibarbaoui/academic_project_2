///////////////////////////////////////////////////////////////////////////
/// @file VisiteurSelection.h
/// @author Najib Arbaoui
/// @date 2014-01-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_VISITOR_VisiteurSuppression_H__
#define  __ARBRE_VISITOR_VisiteurSuppression_H__



#include "Visiteurs\VisiteurAbstrait.h"
#include "ArbreRenduINF2990.h"

#include "Modele3D.h"
#include <GL/gl.h>

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
/// @class  VisiteurSelection
/// @brief Classe de visiteur qui permet de selectionner les noeuds d un arbre
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class VisiteurSuppression : public VisiteurAbstrait
{
	public:

	// Constructeur
		VisiteurSuppression();

	// Destructeur
		~VisiteurSuppression();
		///////////////////

	// fonctions visiter pour chaque noeud

		virtual void visiter(NoeudAsteroide & noeudAsteroide);
		virtual void visiter(NoeudAbstrait & noeudAbstrait);
		virtual void visiter(NoeudBarriereProtectrice & noeudBarriereProtectrice);
		virtual void visiter(NoeudBonusAccelerateur & noeudBonusAccelerateur );
		virtual void visiter(NoeudComposite & noeudComposite);
		virtual void visiter(NoeudPortail & noeudPortail);
		virtual void visiter(NoeudPositionDepart & noeudPositionDepart );
		virtual void visiter(NoeudProjectile & noeudProjectile );
		virtual void visiter(NoeudStationSpatiale & noeudStationSpatiale);
		virtual void visiter(NoeudVaisseau & noeudVaisseau);
		virtual void visiter(NoeudZoneJeu & noeudZoneJeu );
		virtual void visiter(NoeudZonePassage & noeudZonePassage );
		virtual void visiter(NoeudAnimation & noeudAnimation );
		void SupprimerNoeudSelectione(NoeudAbstrait & noeudAbstrait);
		
};


#endif //  __ARBRE_VISITOR_VisiteurSuppression_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////