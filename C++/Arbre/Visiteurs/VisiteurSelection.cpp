///////////////////////////////////////////////////////////////////////////
/// @file VisiteurSelection.cpp
/// @author Najib Arbaoui
/// @date 2014-01-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurSelection.h"
#include "VisiteurBornesSelection.h"
#include "FacadeModele.h"
#include "Utilitaire.h"
#include <cmath>

///////////////////////////////////////////////////////////////////////////
/// @class  VisiteurSelection
/// @brief Classe de visiteur qui permet de selectionner les noeuds d un arbre
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::VisiteurSelection()
///
/// Constructeur par default
/// @param[in] :aucun
///
/// @return Aucune (constructeur).
///
//////////////////////////////////////////////////////////////////////////////////
VisiteurSelection::
	VisiteurSelection(Vecteur3 minXY, Vecteur3 maxXY, bool ctrlPressed) :
selectionMinXY_(minXY), selectionMaxXY_(maxXY), ctrlPressed_(ctrlPressed), unNoeudSelectionne_(false)
{
	if (selectionMinXY_ == selectionMaxXY_)
	{
		simpleClique_ = true;
	}
	else
	{
		simpleClique_ = false;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection:: ~ VisiteurSelection()
///
/// Destructeur par default
/// @param[in] :aucun
///
/// @return Aucune (destructeur).
///
//////////////////////////////////////////////////////////////////////////////////
VisiteurSelection::~VisiteurSelection()  
{
}

void VisiteurSelection::noeudSelection(NoeudAbstrait &noeud)
{
	if (noeud.estSelectionnable())
	{
		// Obtenir bornes boite englobante
		Vecteur3 bornesMinXY, bornesMaxXY;
		noeud.obtenirBoiteEnglobante(bornesMinXY, bornesMaxXY);

		// V�rifie si le noeud touche au rectangle de s�lection
		if (this->toucheRectangleSelection(bornesMinXY, bornesMaxXY))
		{
			// Si le bouton contr�le est enfonc�, on inverse la s�lection pour tous les noeud qui touchent le rectangle elastique
			if (ctrlPressed_)
			{
				noeud.inverserSelection();
			}
			else
			{
				// Il s'agit d'une s�lection o� le bouton contr�le n'est pas activ�
				selectionSansCtrlPressed(noeud);
			}
		}
		else
		{
			// Si le bouton contr�le n'est pas enfonc�, on d�s�lectionne le noeud
			if (!ctrlPressed_)
			{
				noeud.assignerSelection(false);
			}
		}
	}
}

void VisiteurSelection::noeudCompositeSelection(NoeudComposite &noeud)
{
	noeudSelection(noeud);

	for (unsigned int i=0; i<noeud.obtenirNombreEnfants(); i++)
	{
		noeud.chercher(i)->accepter(*this);
	}
}

void VisiteurSelection::selectionSansCtrlPressed(NoeudAbstrait &noeud)
{
	// S'il s'agit d'un simple clique, on limite le nombre de noeud s�lectionn� � 1
	if (simpleClique_)
	{
		// Si aucun noeud n'est s�lectionn� encore
		if (!unNoeudSelectionne_)
		{
			selectionUniqueNoeud(noeud);
		}
		// Un noeud � d�j� �t� s�lectionn�
		else
		{
			// Si la distance de la position du clique au noeud est inf�rieur � celle du noeud s�lectionn�, on s�lectionne ce noeud
			double distance = distanceEntreDeuxPoints(noeud.obtenirPositionRelative(), selectionMaxXY_);
			if (distance < distanceNoeudClique_)
			{
				selectionUniqueNoeud(noeud);
			}
			else
			{
				noeud.assignerSelection(false);
			}
		}
	}
	else
	{
		// Sinon on s�lectionne toujours
		noeud.assignerSelection(true);
	}
}


void VisiteurSelection::selectionUniqueNoeud(NoeudAbstrait &noeud)
{
	// Si un noeud est d�j� s�lectionn�
	if (unNoeudSelectionne_)
	{
		// On le d�s�lectionne
		noeudSelectionne_->assignerSelection(false);
	}
	
	// Un noeud est maintenant s�lectionn�
	unNoeudSelectionne_ = true;

	// Calculer la distance entre le noeud et le clique
	distanceNoeudClique_ = distanceEntreDeuxPoints(noeud.obtenirPositionRelative(), selectionMaxXY_);

	// Se rappeler du noeud s�lectionn�
	noeudSelectionne_ = &noeud;

	// Assigner la s�lection
	noeud.assignerSelection(true);
}

bool VisiteurSelection::toucheRectangleSelection(Vecteur3 minXY, Vecteur3 maxXY)
{
	// V�rifier � la gauche du rectangle de s�lection
	if (maxXY[0] < selectionMinXY_[0])
		return false;

	// V�rifier vers le bas du rectangle de s�lection
	if (maxXY[1] < selectionMinXY_[1])
		return false;
	
	// V�rifier � la droite du rectangle de s�lection
	if (minXY[0] > selectionMaxXY_[0])
		return false;
	
	// V�rifier vers le haut du rectangle de s�lection
	if (minXY[1] > selectionMaxXY_[1])
		return false;

	// Si tout est faux, l'objet touche le rectangle de s�lection
	return true;
}

double VisiteurSelection::distanceEntreDeuxPoints(Vecteur3 position1, Vecteur3 position2)
{
	return sqrt(pow(position2[0] - position1[0], 2) + pow(position2[1] - position1[1], 2));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::visiter( NoeudAsteroide& noeudAsteroide)
///
///  Fonction qui permet au visiteur d'acceder au noeudAsteroide et faire son traitement
///
/// @param[in]: NoeudAsteroide & noeudAsteroide
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudAsteroide & noeudAsteroide)
{
	noeudSelection(noeudAsteroide);
}

void VisiteurSelection::visiter(NoeudAbstrait & noeudAbstrait)
{
	noeudSelection(noeudAbstrait);
}

void VisiteurSelection::visiter(NoeudBarriereProtectrice & noeudBarriereProtectrice)
{
	noeudSelection(noeudBarriereProtectrice);
}

void VisiteurSelection::visiter(NoeudBonusAccelerateur & noeudBonusAccelerateur )
{
	noeudSelection(noeudBonusAccelerateur);
}

void VisiteurSelection:: visiter(NoeudComposite & noeudComposite)
{
	noeudCompositeSelection(noeudComposite);
}

void VisiteurSelection::visiter(NoeudPortail & noeudPortail)
{			
	noeudSelection(noeudPortail);
}

void VisiteurSelection::visiter(NoeudPositionDepart & noeudPositionDepart )
{
	noeudSelection(noeudPositionDepart);
}

void VisiteurSelection::visiter(NoeudProjectile & noeudProjectile ) 
{
	noeudSelection(noeudProjectile);
}

void VisiteurSelection::visiter(NoeudStationSpatiale & noeudStationSpatiale)
{
	noeudSelection(noeudStationSpatiale);
}

void VisiteurSelection::visiter(NoeudVaisseau & noeudVaisseau)
{
	noeudSelection(noeudVaisseau);
}

void VisiteurSelection::visiter(NoeudZoneJeu & noeudZoneJeu )
{
	noeudSelection(noeudZoneJeu);
}

void VisiteurSelection::visiter(NoeudZonePassage & noeudZonePassage )
{
	noeudSelection(noeudZonePassage);
}
 void VisiteurSelection::visiter(NoeudAnimation & noeudAnimation )
{

}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
