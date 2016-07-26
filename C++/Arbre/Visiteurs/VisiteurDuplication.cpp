#include "VisiteurDuplication.h"

#include "FacadeModele.h"

VisiteurDuplication::VisiteurDuplication(Vecteur3 deplacement)
{
	deplacement_ = deplacement;
	premierNoeudPortail = NULL;
}

VisiteurDuplication::~VisiteurDuplication()
{
}

void VisiteurDuplication::assignerDeplacement(Vecteur3 deplacement)
{
	deplacement_ = deplacement;
}

void VisiteurDuplication::noeudAbstraitDupliquer(NoeudAbstrait &noeud)
{
	Vecteur3 nouvellePosition = noeud.obtenirPositionRelative() + deplacement_;
	NoeudAbstrait* nouveauNoeud = FacadeModele::obtenirInstance()->dupliquerNoeud(&noeud, nouvellePosition);

	// Si c'est un portail, on doit gérer les freres
	if (noeud.obtenirType() == ArbreRenduINF2990::NOM_PORTAIL)
	{
		// Si le premier noeud portail n'est pas défini, on est en train de créer le premier noeud d'une paire
		if (premierNoeudPortail == NULL)
		{
			premierNoeudPortail = (NoeudPortail*)nouveauNoeud;
		}
		else
		{
			// On vient de créer le deuxième noeud d'une paire, on assigne les frères 
			premierNoeudPortail->assignerPortailFrere(nouveauNoeud);
			((NoeudPortail*)nouveauNoeud)->assignerPortailFrere(premierNoeudPortail);

			// Réinitialise le premier noeud portail
			premierNoeudPortail = NULL;
		}
	}
}

void VisiteurDuplication::noeudCompositeDupliquer(NoeudComposite &noeud)
{
	if (noeud.estSelectionne())
	{
		Vecteur3 nouvellePosition = noeud.obtenirPositionRelative() + deplacement_;
		NoeudAbstrait* nouveauNoeud = FacadeModele::obtenirInstance()->dupliquerNoeud(&noeud, nouvellePosition);
	}

	for (unsigned int i=0; i<noeud.obtenirNombreEnfants(); i++)
	{
		noeud.chercher(i)->accepter(*this);
	}
}

void VisiteurDuplication::visiter(NoeudAbstrait &noeudAbstrait)
{
	if (noeudAbstrait.estSelectionne())
	{
		noeudAbstraitDupliquer(noeudAbstrait);
	}
}

void VisiteurDuplication::visiter(NoeudComposite &noeudComposite)
{
	noeudCompositeDupliquer(noeudComposite);
}

void VisiteurDuplication::visiter(NoeudBarriereProtectrice &noeudBarriereProtectrice)
{
	if (noeudBarriereProtectrice.estSelectionne())
	{
		noeudAbstraitDupliquer(noeudBarriereProtectrice);
	}
}

void VisiteurDuplication::visiter(NoeudBonusAccelerateur &noeudBonusAccelerateur )
{
	if (noeudBonusAccelerateur.estSelectionne())
	{
		noeudAbstraitDupliquer(noeudBonusAccelerateur);
	}
}

void VisiteurDuplication::visiter(NoeudAsteroide &noeudAsteroide)
{
	if (noeudAsteroide.estSelectionne())
	{
		noeudAbstraitDupliquer(noeudAsteroide);
	}
}

void VisiteurDuplication::visiter(NoeudPortail &noeudPortail)
{
	if (noeudPortail.estSelectionne())
	{
		// Le frere du portail doit être sélectionné pour être dupliqué
		if (noeudPortail.obtenirPortailFrere()->estSelectionne())
		{
			noeudAbstraitDupliquer(noeudPortail);
		}
	}
}

void VisiteurDuplication::visiter(NoeudPositionDepart &noeudPositionDepart )
{
	if (noeudPositionDepart.estSelectionne())
	{
		noeudAbstraitDupliquer(noeudPositionDepart);
	}
}

void VisiteurDuplication::visiter(NoeudProjectile &noeudProjectile )
{
	if (noeudProjectile.estSelectionne())
	{
		noeudAbstraitDupliquer(noeudProjectile);
	}
}

void VisiteurDuplication::visiter(NoeudStationSpatiale &noeudStationSpatiale)
{
	if (noeudStationSpatiale.estSelectionne())
	{
		noeudAbstraitDupliquer(noeudStationSpatiale);
	}
}

void VisiteurDuplication::visiter(NoeudVaisseau &noeudVaisseau)
{
	if (noeudVaisseau.estSelectionne())
	{
		noeudAbstraitDupliquer(noeudVaisseau);
	}
}

void VisiteurDuplication::visiter(NoeudZoneJeu &noeudZoneJeu )
{
	if (noeudZoneJeu.estSelectionne())
	{
		noeudAbstraitDupliquer(noeudZoneJeu);
	}
}

void VisiteurDuplication::visiter(NoeudZonePassage &noeudZonePassage )
{
	if (noeudZonePassage.estSelectionne())
	{
		noeudAbstraitDupliquer(noeudZonePassage);
	}
}

 void VisiteurDuplication::visiter(NoeudAnimation & noeudAnimation )
{

}