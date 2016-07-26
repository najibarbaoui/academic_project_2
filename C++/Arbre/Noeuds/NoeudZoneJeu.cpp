///////////////////////////////////////////////////////////////////////////////
/// @file NoeudZoneJeu.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudZoneJeu.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "FacadeModele.h"
#include "GestionnaireJeu.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudZoneJeu::NoeudZoneJeu(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudZoneJeu::NoeudZoneJeu(const std::string& typeNoeud)
   : NoeudAbstrait(typeNoeud), minXY_(-250,-120, 0),maxXY_(250, 120, 0) 
{
	selectionnable_ = false;
	enregistrable_ = false;
	afficheSiVaisseauLoin_ = true;

   // Cr�ation d'une liste d'affichage.  ATTENTION, CECI N'EST PAS UN
   // USAGE CORRECT DES LISTES D'AFFICHAGE, puisque la m�me liste serait
   // recr��e pour chaque instance d'un noeud, alors que la m�me pourrait
   // �tre partag�e par toutes les instances d'un m�me type de noeud.
   liste_ = glGenLists(1);
   glNewList(liste_, GL_COMPILE);
   
    glPushMatrix();
	glLineWidth(1);
 
	glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
	glVertex3d(minXY_[0], minXY_[1], 0);
	glVertex3d(minXY_[0], maxXY_[1], 0);
	glVertex3d(maxXY_[0], maxXY_[1], 0);
	glVertex3d(maxXY_[0], minXY_[1], 0);
	glVertex3d(minXY_[0], minXY_[1], 0);

	glEnd();
	glPopMatrix();
   glEndList();
   //
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudZoneJeu::~NoeudZoneJeu()
///
/// Ce destructeur d�sallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudZoneJeu::~NoeudZoneJeu()
{
   glDeleteLists(liste_, 1);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudZoneJeu::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudZoneJeu::afficherConcret() const
{
	
	bool afficher = true;
	if (!afficheSiVaisseauLoin_)
	{
		// Ne devrait jamais �tre faux si pas en mode jeu
		assert(GestionnaireJeu::obtenirInstance()->getPlayer(1) != NULL);
		
		afficher = false;
		NoeudVaisseau* vaisseau1 = GestionnaireJeu::obtenirInstance()->getPlayer(1)->getVaisseau();
		if (vaisseau1 != NULL)
		{
			afficher = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->estProcheZoneJeu(vaisseau1);
		}
		
		// Si en mode Solo
		if (GestionnaireJeu::obtenirInstance()->getPlayer(2) != NULL)
		{
			NoeudVaisseau* vaisseau2 = GestionnaireJeu::obtenirInstance()->getPlayer(2)->getVaisseau();
			if (vaisseau2 != NULL)
			{
				afficher = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->estProcheZoneJeu(vaisseau2);
			}
		}
	}

	if (afficher)
	{

		glPushMatrix();
		//glDisable(GL_TEXTURE_2D);

		// Affichage du mod�le.
		glCallList(liste_);

		glPopMatrix();
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
void NoeudZoneJeu::animer(float temps)
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
void NoeudZoneJeu::accepter(VisiteurAbstrait& visiteur)
{
	visiteur.visiter(*this);
}
   
void NoeudZoneJeu::obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY) const
{
	minXY = minXY_;
	maxXY = maxXY_;
}

void NoeudZoneJeu::assignerAfficherSiVaisseauLoin(bool value)
{
	afficheSiVaisseauLoin_ = value;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
