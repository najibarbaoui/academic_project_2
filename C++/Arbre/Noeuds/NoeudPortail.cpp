///////////////////////////////////////////////////////////////////////////////
/// @file NoeudPortail.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudPortail.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#define M_PI       3.14159265358979323846

#include "GestionnaireJeu.h"
#include "FacadeModele.h"
#include "Jeu\ModelManager.h"

#include "Visiteurs\VisiteurChampAttraction.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPortail::NoeudPortail(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPortail::NoeudPortail(const std::string& typeNoeud)
   : NoeudAbstrait(typeNoeud)
{
	modele_ = ModelManager::obtenirInstance()->getModel(typeNoeud);
	liste_ = ModelManager::obtenirInstance()->getDisplayList(typeNoeud);
	
	modele_->obtenirBoiteEnglobante(boiteMinXY_, boiteMaxXY_);

	enabled_ = true;
	noeudTeleporte_ = NULL;
	frere_ = 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPortail::~NoeudPortail()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPortail::~NoeudPortail()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPortail::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPortail::afficherConcret() const
{
	if (this->selectionne_)
	{
		// Modifie la couleur si sélectionné
		// Rose (Le glPopAttrib remettra l'ancienne couleur)
		glColor3f(1, 0, 1);
	}
	else
	{
		// Bleu
		glColor3f(0, 0, 1);
	}

	// Affichage du modèle.
	glCallList(liste_);

	// Affichage du lien entre les deux portails associés
	if (this->selectionne_)
	{
		// Pop matrix parce que nous ne voulons pas modifier son orientation avec la rotation du portail
		glPopMatrix();

		// Affiche une ligne qui montre à quel autre portail ce portail est associé
		Vecteur3 positionPortailFrere = this->frere_->obtenirPositionRelative();

		glLineWidth(5);
		glLineStipple(2, 0xAAAA);
		glEnable(GL_LINE_STIPPLE);
		glBegin(GL_LINES);
			// Ligne rouge
			glColor3f(1.0, 0.0, 0.0);

			glVertex3d(positionPortailFrere[0], positionPortailFrere[1], 0);
			glVertex3d(this->positionRelative_[0], this->positionRelative_[1], 0);
		glEnd();
		glDisable(GL_LINE_STIPPLE);
		glLineWidth(1);

		glPushMatrix();
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCube::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPortail::animer(float temps)
{
	// Appliquer champ d'attraction
	if (enabled_)
	{
		appliquerChampAttraction();
	}
	else
	{
		assert(noeudTeleporte_ != NULL);
		// Si disabled, on calcule la distance au noeud qui vient de sortir pour voir s'il faut le réactiver
		double distance2 = (this->noeudTeleporte_->obtenirPositionRelative() - this->positionRelative_).norme2();
		if (distance2 > 1000)
		{
			this->enabled_ = true;
			noeudTeleporte_ = NULL;
		}
	}
}

void NoeudPortail::appliquerChampAttraction()
{
	VisiteurChampAttraction v(this);

	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(v);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::accepter(VisiteurAbstrait& visiteur)
///
/// Cette fonction accepter le visiteur et lui permettre de faire son traitement 
/// sur l'objet appellant 
///
///
/// @param[in] visiteur : un objet visiteur
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPortail::accepter(VisiteurAbstrait& visiteur)
{
	visiteur.visiter(*this);
}

void NoeudPortail::setEnabled(bool value)
{
	this->enabled_ = value;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPortail::obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY)
///
/// Cette fonction permet les coins min et max de la boite qui englobe l'objet
///
///
/// @param[in] minXY : le vecteur du coin min de l'objet
///	@param[in] maxXY : le vecteur du coin max de l'objet
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPortail::obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY) const
{
	minXY = boiteMinXY_;
	maxXY = boiteMaxXY_;

	// Appliquer échelle
	minXY *= echelle_;
	maxXY *= echelle_;

	// Appliquer rotation
	// On assume que la boite est centrée sur x, y
	double sinus = sin(angleRotation_*M_PI/180);
	double cosinus = cos(angleRotation_*M_PI/180);
	double width = maxXY[0] - minXY[0];
	double height = maxXY[1] - minXY[1];
	if (sinus < 0) sinus = -sinus;
	if (cosinus < 0) cosinus = -cosinus;

	double newWidth = height*sinus + width*cosinus;
	double newHeight = height*cosinus + width*sinus;
	
	minXY[0] = -newWidth/2;
	maxXY[0] = newWidth/2;
	minXY[1] = -newHeight/2;
	maxXY[1] = newHeight/2;

	// Appliquer translation
	minXY += this->positionRelative_;
	maxXY += this->positionRelative_;
}

double NoeudPortail::obtenirSphereEnglobante() const
{
	// Applique l'échelle
	double rayon = modele_->obtenirSphereEnglobante() * this->echelle_;

	// Facteur constant pour que les extrémités du modèle ne compte pas dans la détection des collisions
	return rayon;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPortail::assignerPortailFrere(NoeudAbstrait* frere)
///
/// Cette fonction permet d'assigner le portail qui est relié à celui-ci
///
///
/// @param[in] frere : Un pointeur sur le portail relié à celui-ci.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPortail::assignerPortailFrere(NoeudAbstrait* frere)
{
	frere_ = frere;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPortail::obtenirPortailFrere()
///
/// Cette fonction permet d'obtenir le portail qui est relié à celui-ci
///
/// @return NoeudAbstrait* : Un pointeur sur le portail relié à celui-ci.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudPortail::obtenirPortailFrere()
{
	return frere_;
}

void NoeudPortail::teleporterNoeud(NoeudAbstrait* noeud)
{
	noeud->assignerPositionRelative(this->obtenirPositionRelative());
	enabled_ = false;

	noeudTeleporte_ = noeud;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPortail::obtenirPortailFrere()
///
/// Cette fonction permet d'obtenir le portail qui est relié à celui-ci
///
/// @return NoeudAbstrait* : Un pointeur sur le portail relié à celui-ci.
///
////////////////////////////////////////////////////////////////////////
void NoeudPortail::effacerSelection()
{
	if (this->estSelectionne() && frere_ != 0)
		frere_->assignerSelection(true);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
