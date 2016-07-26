///////////////////////////////////////////////////////////////////////////
/// @file VisiteurAbstrait.h
/// @author Najib Arbaoui
/// @date 2014-01-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_VISITOR_VISITEURABSTRAIT_H__
#define __ARBRE_VISITOR_VISITEURABSTRAIT_H__

class NoeudAbstrait ;
class NoeudAsteroide ;
class NoeudBarriereProtectrice ;
class NoeudBonusAccelerateur ;
class NoeudComposite ;
class NoeudPortail ;
class NoeudPositionDepart ;
class NoeudProjectile ;
class NoeudStationSpatiale ;
class NoeudVaisseau ;
class NoeudZoneJeu;
class NoeudZonePassage;
class NoeudAnimation ;

#include "Modele3D.h"
#include <GL\gl.h>


///////////////////////////////////////////////////////////////////////////
/// @class NoeudProjectile
/// @brief Classe qui repr�sente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class VisiteurAbstrait
{
	public:

	// Constructeur
		VisiteurAbstrait(){};

	// Destructeur
		virtual ~VisiteurAbstrait() =0 {} ;

	// fonctions visiter pour chaque noeud

		virtual void visiter(NoeudAsteroide & noeudAsteroide)=0;
		virtual void visiter(NoeudAbstrait & noeudAbstrait)=0;
		virtual void visiter(NoeudBarriereProtectrice & noeudBarriereProtectrice)=0;
		virtual void visiter(NoeudBonusAccelerateur & noeudBonusAccelerateur )=0;
		virtual void visiter(NoeudComposite & noeudComposite)=0;
		virtual void visiter(NoeudPortail & noeudPortail)=0;
		virtual void visiter(NoeudPositionDepart & noeudPositionDepart )=0;
		virtual void visiter(NoeudProjectile & noeudProjectile )=0;
		virtual void visiter(NoeudStationSpatiale & noeudStationSpatiale)=0;
		virtual void visiter(NoeudVaisseau & noeudVaisseau)=0;
		virtual void visiter(NoeudZoneJeu & noeudZoneJeu )=0;
		virtual void visiter(NoeudZonePassage & noeudZonePassage )=0;
		virtual void visiter(NoeudAnimation & noeudAnimation )=0;
};


#endif // __ARBRE_VISITOR_VISITEURABSTRAIT_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
