///////////////////////////////////////////////////////////////////////////////
/// @file NoeudBarriereProtectrice.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudBarriereProtectrice.h"
#include "Utilitaire.h"
#include "FacadeModele.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#define M_PI       3.14159265358979323846

#include "Visiteurs\VisiteurBarriereProtectrice.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBarriereProtectrice::NoeudBarriereProtectrice(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBarriereProtectrice::NoeudBarriereProtectrice(const std::string& typeNoeud)
   : NoeudAbstrait(typeNoeud), width_(1)
{
	p1 = Vecteur3(width_/2, width_/2, 0);
	p2 = Vecteur3(-width_/2, width_/2, 0);
	p3 = Vecteur3(-width_/2, -width_/2, 0);
	p4 = Vecteur3(width_/2, -width_/2, 0);

	this->valide_ = true;
	masse_ = DBL_MAX;

	liste_ = glGenLists(1);
	glNewList(liste_, GL_COMPILE);
		glBegin(GL_POLYGON);
		{
			glVertex3d(p1[0], p1[1], 0);
			glVertex3d(p2[0], p2[1], 0);
			glVertex3d(p3[0], p3[1], 0);
			glVertex3d(p4[0], p4[1], 0);
			glVertex3d(p1[0], p1[1], 0);
		}
		glEnd();
	glEndList();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBarriereProtectrice::~NoeudBarriereProtectrice()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBarriereProtectrice::~NoeudBarriereProtectrice()
{
   glDeleteLists(liste_, 1);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBarriereProtectrice::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBarriereProtectrice::afficherConcret() const
{
	// Vert-bleu
	glColor3f(0.5, 1.0, 0.5);

	// Modifie la couleur si sélectionné
	if (this->selectionne_)
	{
		// Rose (Le glPopAttrib remettra l'ancienne couleur)
		glColor3f(1, 0, 1);
	}
	else if (!this->valide_)
	{
		glColor3f(1, 0, 0);
	}

	// On doit annuler l'effet de l'échelle pour la barrière protectrice
	glScaled(1/echelle_, 1/echelle_, 1/echelle_);

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
void NoeudBarriereProtectrice::animer(float temps)
{
	VisiteurBarriereProtectrice v(this);
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
void NoeudBarriereProtectrice::accepter(VisiteurAbstrait& visiteur)
{
	visiteur.visiter(*this);
}

void NoeudBarriereProtectrice::obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY) const
{
	// Trouver boite englobante
	minXY[0] = min(min(p1[0], p2[0]), min(p3[0], p4[0]));
	minXY[1] = min(min(p1[1], p2[1]), min(p3[1], p4[1]));
	maxXY[0] = max(max(p1[0], p2[0]), max(p3[0], p4[0]));
	maxXY[1] = max(max(p1[1], p2[1]), max(p3[1], p4[1]));

	// On n'applique pas l'échelle pour la barrière protectrique
	//minXY *= echelle_;
	//maxXY *= echelle_;

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


void NoeudBarriereProtectrice::setEchelle(double e)
{
	this->echelle_ = e;

	this->recalculerPoints();
}

// Basé sur: http://stackoverflow.com/questions/7854043/drawing-rectangle-between-two-points-with-arbitrary-width
void NoeudBarriereProtectrice::finaliserBarriere(Vecteur3 pointDebut, Vecteur3 pointFin)
{
	this->pointDebut_ = pointDebut;
	this->pointFin_ = pointFin;
	this->assignerPositionRelative( (pointDebut + pointFin)/2 );

	Vecteur3 deplacement = pointFin - pointDebut;
	this->echelle_ = deplacement.norme();
	this->angleRotation_ = deplacement.lireTheta()*180/M_PI;

	recalculerPoints();
}

void NoeudBarriereProtectrice::recalculerPoints()
{
	Vecteur3 pDebut, pFin;

	// On considère l'échelle que sur l'axe des X
	pDebut[0] = -this->echelle_/2;
	pFin[0] = this->echelle_/2;

	Vecteur3 vp;
	vp[1] = -(pFin[0] - pDebut[0]);
	vp.normaliser();

	p1[0] = pDebut[0] + vp[0] * width_ / 2;
	p1[1] = pDebut[1] + vp[1] * width_ / 2;
	p2[0] = pDebut[0] - vp[0] * width_ / 2;
	p2[1] = pDebut[1] - vp[1] * width_ / 2;
	p3[0] = pFin[0] + vp[0] * width_ / 2;
	p3[1] = pFin[1] + vp[1] * width_ / 2;
	p4[0] = pFin[0] - vp[0] * width_ / 2;
	p4[1] = pFin[1] - vp[1] * width_ / 2;

	// Redefinir la liste d'affichage
	glDeleteLists(liste_, 1);
	glNewList(liste_, GL_COMPILE);
		glBegin(GL_POLYGON);
		{
			glVertex3d(p1[0], p1[1], 0);
			glVertex3d(p3[0], p3[1], 0);
			glVertex3d(p4[0], p4[1], 0);
			glVertex3d(p2[0], p2[1], 0);
			glVertex3d(p1[0], p1[1], 0);
		}
		glEnd();
	glEndList();

	Vecteur3 minXY, maxXY;
	this->obtenirBoiteEnglobante(minXY, maxXY);

	// Si en dehors de la zone de jeu, on change sa couleur d'affichage
	if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->estDansZoneJeu(minXY, maxXY))
	{
		this->valide_ = true;
	}
	else
	{
		this->valide_ = false;
	}
}

void NoeudBarriereProtectrice::obtenirAxes(Vecteur3 &axe1, Vecteur3 &axe2)
{
	// les axes sont les axes X et Y avant la rotation
	axe1 = Vecteur3(1, 0, 0);
	axe2 = Vecteur3(0, 1, 0);

	// On applique la rotation
	axe1 = axe1.tourner(utilitaire::DEG_TO_RAD(this->angleRotation_), Vecteur3(0, 0, 1));
	axe2 = axe2.tourner(utilitaire::DEG_TO_RAD(this->angleRotation_), Vecteur3(0, 0, 1));
}


void NoeudBarriereProtectrice::obtenirVertices(Vecteur3* &vertices, int &size)
{
	size = 4;

	vertices = new Vecteur3[size];

	vertices[0] = Vecteur3(echelle_/2, (double)width_/2, 0);
	vertices[1] = Vecteur3(-echelle_/2, (double)width_/2, 0);
	vertices[2] = Vecteur3(-echelle_/2, -(double)width_/2, 0);
	vertices[3] = Vecteur3(echelle_/2, -(double)width_/2, 0);

	for (int i=0; i<size; i++)
	{
		vertices[i] = vertices[i].tourner(utilitaire::DEG_TO_RAD(angleRotation_), Vecteur3(0, 0, 1));
		vertices[i] += positionRelative_;
	}
}

void NoeudBarriereProtectrice::obtenirExtremites(Vecteur3 &pointDebut, Vecteur3 &pointFin)
{
	pointDebut = this->pointDebut_;
	pointFin = this->pointFin_;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
