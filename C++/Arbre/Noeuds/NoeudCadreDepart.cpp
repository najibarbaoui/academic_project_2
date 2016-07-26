///////////////////////////////////////////////////////////////////////////////
/// @file NoeudCadreDepart.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudCadreDepart.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudCadreDepart::NoeudCadreDepart(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudCadreDepart::NoeudCadreDepart(const std::string& typeNoeud)
   : NoeudAbstrait(typeNoeud), minXY_(-325,-195, 0),maxXY_(325, 195, 0) 
{
	selectionnable_ = false;
	enregistrable_ = false;

   // Création d'une liste d'affichage.  ATTENTION, CECI N'EST PAS UN
   // USAGE CORRECT DES LISTES D'AFFICHAGE, puisque la même liste serait
   // recréée pour chaque instance d'un noeud, alors que la même pourrait
   // être partagée par toutes les instances d'un même type de noeud.
	liste_ = glGenLists(1);
	glNewList(liste_, GL_COMPILE);
		glPushMatrix();
			glLineWidth(2);
			glEnable(GL_LINE_STIPPLE);
			glLineStipple(2, 0xAAAA);
			glBegin(GL_LINE_STRIP);
	
				glColor3f(1.0, 1.0, 0.0);

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
/// @fn NoeudCadreDepart::~NoeudCadreDepart()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudCadreDepart::~NoeudCadreDepart()
{
   glDeleteLists(liste_, 1);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCadreDepart::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCadreDepart::afficherConcret() const
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
void NoeudCadreDepart::animer(float temps)
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
void NoeudCadreDepart::accepter(VisiteurAbstrait& visiteur)
{
	visiteur.visiter(*this);
}

void NoeudCadreDepart::obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY) const
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
