///////////////////////////////////////////////////////////////////////////////
/// @file NoeudZonePassage.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudZonePassage.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudZonePassage::NoeudZonePassage(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudZonePassage::NoeudZonePassage(const std::string& typeNoeud)
   : NoeudAbstrait(typeNoeud), minXY_(-175,-45, 0),maxXY_(175, 45, 0) 
{
	selectionnable_ = false;
	enregistrable_ = false;

   // Création d'une liste d'affichage.  ATTENTION, CECI N'EST PAS UN
   // USAGE CORRECT DES LISTES D'AFFICHAGE, puisque la même liste serait
   // recréée pour chaque instance d'un noeud, alors que la même pourrait
   //// être partagée par toutes les instances d'un même type de noeud.
   liste_ = glGenLists(1);
   glNewList(liste_, GL_COMPILE);
	glLineWidth(1);
   glPushMatrix();
    glEnable(GL_LINE_STIPPLE);
	glLineStipple(2, 0xAAAA);
    glBegin(GL_LINE_STRIP);
	
	glColor3f(0.0f, 1.0f, 0.0f);

	glVertex3d(minXY_[0], minXY_[1], 0);
	glVertex3d(minXY_[0], maxXY_[1], 0);
	glVertex3d(maxXY_[0], maxXY_[1], 0);
	glVertex3d(maxXY_[0], minXY_[1], 0);
	glVertex3d(minXY_[0], minXY_[1], 0);

	glEnd();
	 glDisable(GL_LINE_STIPPLE);
	glPopMatrix();
   glEndList();
   //
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudZonePassage::~NoeudZonePassage()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudZonePassage::~NoeudZonePassage()
{
   glDeleteLists(liste_, 1);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudZonePassage::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudZonePassage::afficherConcret() const
{
   // Sauvegarde de la matrice.
   glPushMatrix();

   // Affichage du modèle.
   glCallList(liste_);
   // Restauration de la matrice.
   glPopMatrix();
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
void NoeudZonePassage::animer(float temps)
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
void NoeudZonePassage::accepter(VisiteurAbstrait& visiteur)
{
	visiteur.visiter(*this);
}

void NoeudZonePassage::obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY) const
{
	modele_.obtenirBoiteEnglobante(minXY, maxXY);

	// Appliquer échelle
	minXY *= echelle_;
	maxXY *= echelle_;

	// Appliquer rotation
	// On assume que la boite est centrée sur x, y
	double s = sin(angleRotation_);//Math.sin(a);
	double c = cos(angleRotation_);
	double width = maxXY[0] - minXY[0];
	double height = maxXY[1] - minXY[1];
	if (s < 0) s= -s;
	if (c < 0) c= -c;

	double newWidth = height*s + width*c; // width of AABB
	double newHeight = height*c + width*s; // height of AABB
	
	minXY[0] = -newWidth/2;
	maxXY[0] = newWidth/2;
	minXY[1] = -newHeight/2;
	maxXY[1] = newHeight/2;

	// Appliquer translation
	minXY += this->positionRelative_;
	maxXY += this->positionRelative_;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
