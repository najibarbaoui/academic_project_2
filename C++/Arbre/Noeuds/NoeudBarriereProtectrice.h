///////////////////////////////////////////////////////////////////////////
/// @file NoeudBarriereProtectrice.h
/// @author Najib Arbaoui
/// @date 2014-01-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDBARRIEREPROTECTRICE_H__
#define __ARBRE_NOEUDS_NOEUDBARRIEREPROTECTRICE_H__

#include "NoeudAbstrait.h"
#include "Modele3D.h"
#include <GL/gl.h>
#include"NoeudPositionDepart.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudBarriereProtectrice
/// @brief Classe qui repr�sente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudBarriereProtectrice : public NoeudAbstrait
{
public:
	/// Constructeur � partir du type du noeud.
	NoeudBarriereProtectrice(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudBarriereProtectrice();

	/// Affiche le cube.
	virtual void afficherConcret() const;
	/// Effectue l'animation du cube.
	virtual void animer( float temps );
	// Accepter visiteur
	virtual void accepter(VisiteurAbstrait& unVisiteur);

	virtual void obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY) const;
   
	//facteur echelle modificateur
	virtual void setEchelle(double e);

	void finaliserBarriere(Vecteur3 pointDebut, Vecteur3 pointFin);

	void obtenirExtremites(Vecteur3 &pointDebut, Vecteur3 &pointFin);

	void recalculerPoints();

	void obtenirAxes(Vecteur3 &axe1, Vecteur3 &axe2);

	void obtenirVertices(Vecteur3* &vertices, int &size);

	//list<Vecteur3*>* obtenirVertices();
private:
   /// Liste d'affichage pour l'affichage de ce noeud.
   GLuint liste_;

   int width_;
   bool pointDebutDefini;
   bool valide_;
   Vecteur3 pointDebut_, pointFin_;
   Vecteur3 p1, p2, p3, p4;
};


#endif // __ARBRE_NOEUDS_NoeudBarriereProtectrice_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
