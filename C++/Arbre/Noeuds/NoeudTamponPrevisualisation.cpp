///////////////////////////////////////////////////////////////////////////////
/// @file NoeudTamponPrevisualisation.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudTamponPrevisualisation.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#define M_PI       3.14159265358979323846

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTamponPrevisualisation::NoeudTamponPrevisualisation(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTamponPrevisualisation::NoeudTamponPrevisualisation(const std::string& typeNoeud)
   : NoeudAbstrait(typeNoeud)
{
	liste_ = glGenLists(1);
	glNewList(liste_, GL_COMPILE);
	glLineWidth(2);
		
		glBegin(GL_LINE_STRIP);
		{
			glVertex3f(-2, -2, 0);
			glVertex3f(-2, 2, 0);
			glVertex3f(2, 2, 0);
			glVertex3f(2, -2, 0);
			glVertex3f(-2, -2, 0);
		}

		glEnd();
	glEndList();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTamponPrevisualisation::~NoeudTamponPrevisualisation()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTamponPrevisualisation::~NoeudTamponPrevisualisation()
{
   glDeleteLists(liste_, 1);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTamponPrevisualisation::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTamponPrevisualisation::afficherConcret() const
{
	
	
	// Modifie la couleur si sélectionné
	if (this->selectionne_)
	{
		// Rose (Le glPopAttrib remettra l'ancienne couleur)
		glColor3f(1, 0, 0);
	}
	else
	{
		// Blanc
		glColor3f(1, 1, 1);
	}

	// Affichage du modèle.
	glCallList(liste_);
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
void NoeudTamponPrevisualisation::animer(float temps)
{
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
void NoeudTamponPrevisualisation::accepter(VisiteurAbstrait& visiteur)
{
	visiteur.visiter(*this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTamponPrevisualisation::tracerTampon(Vecteur3 minXY, Vecteur3 maxXY)
///
/// Cette fonction permet de tracer le tampon de visualisation sous forme d'un cadre
///  
///
///
/// @param[in] Vecteur3 minXY, Vecteur3 maxXY : les bornes minimum et maximum du cadre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////



void NoeudTamponPrevisualisation::tracerTampon(Vecteur3 minXY, Vecteur3 maxXY)
{
	this->borneMinXY_ =   minXY ;
	
	this->borneMaxXY_ = maxXY ;
	
	glDeleteLists(liste_, 1);
	glNewList(liste_, GL_COMPILE);
	glLineWidth(2);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(2, 0xAAAA);
		glBegin(GL_LINE_STRIP);
		{
			glVertex3d(minXY[0], maxXY[1], 0);
			glVertex3d(maxXY[0], maxXY[1], 0);
			glVertex3d(maxXY[0], minXY[1], 0);
			glVertex3d(minXY[0], minXY[1], 0);
			glVertex3d(minXY[0], maxXY[1], 0);
		}
		glEnd();
	glDisable(GL_LINE_STIPPLE);
	glEndList();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTamponPrevisualisation::obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY)
///
/// Cette fonction permet les coins min et max de la boite qui englobe l'objet
///
///
/// @param[in] minXY : le vecteur du coin min de l'objet
///	@param[in] maxXY : le vecteur du coin max de l'objet
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void NoeudTamponPrevisualisation::obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY) const
{
		// Trouver boite englobante
	minXY = this->borneMinXY_;
	
	maxXY = this->borneMaxXY_ ;
	

	// On n'applique pas l'échelle pour la barrière protectrique
	minXY *= echelle_;
	maxXY *= echelle_;


	//// Appliquer translation
	minXY -= this->positionRelative_;
	maxXY -= this->positionRelative_;

}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
