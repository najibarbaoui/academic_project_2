////////////////////////////////////////////////
/// @file   NoeudAbstrait.cpp
/// @author DGI-2990
/// @date   2007-01-24
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#include "NoeudAbstrait.h"
#include "Utilitaire.h"
#include "Visiteurs/VisiteurAbstrait.h"
#include"Modele3D.h"
#include <Visiteurs\VisiteurXml.h>

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait::NoeudAbstrait(const std::string& type)
///
/// Ne fait qu'initialiser les variables membres de la classe.
///
/// @param[in] type               : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait::NoeudAbstrait(
   const std::string& type //= std::string( "" )
   ) :
   type_(type) ,
   modePolygones_(GL_FILL),
   positionRelative_(0),
   affiche_(true),
   selectionne_(false),
   selectionnable_(true),
   enregistrable_(true),
   dynamique_(false),
   parent_(0),
   echelle_(1.0),
   angleRotation_(0.0),
   masse_(0.0)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait::~NoeudAbstrait()
///
/// Destructeur vide d�clar� virtuel pour les classes d�riv�es.  La
/// lib�ration des afficheurs n'est pas la responsabilit� de cette
/// classe.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait::~NoeudAbstrait()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudAbstrait::calculerProfondeur() const
///
/// Cette fonction calcule la profondeur de l'arbre incluant le noeud
/// courant ainsi que tous ses enfants.
///
/// Cette fonction retourne toujours 1 pour un noeud sans enfant.
///
/// @return La profondeur de l'arbre sous ce noeud, donc toujours 1.
///
////////////////////////////////////////////////////////////////////////
unsigned int NoeudAbstrait::calculerProfondeur() const
{
   return 1;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::vider()
///
/// Cette fonction vide le noeud de tous ses enfants.
///
/// Cette fonction ne fait rien pour un noeud sans enfant, elle ne fait
/// donc rien dans cette implantation par d�faut de la classe de base.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::vider()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::effacer( const NoeudAbstrait* noeud )
///
/// Cette fonction efface le noeud s'il fait partie des enfants de
/// ce noeud.
///
/// Cette fonction ne fait rien pour un noeud sans enfant, elle ne fait
/// donc rien dans cette implantation par d�faut de la classe de base.
///
/// @param[in] noeud : Le noeud � effacer.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::effacer( const NoeudAbstrait* noeud )
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn const NoeudAbstrait* NoeudAbstrait::chercher( const std::string& typeNoeud ) const
///
/// Cette fonction cherche un noeud d'un type donn� parmi le noeud
/// lui-m�me et ses enfants.
///
/// Elle retourne donc le noeud lui-m�me si son type est celui pass� en
/// param�tre, ou 0 sinon.
///
/// @param[in] typeNoeud : Le type du noeud � trouver.
///
/// @return Le pointeur vers le noeud s'il est trouv�.
///
////////////////////////////////////////////////////////////////////////
const NoeudAbstrait* NoeudAbstrait::chercher( const std::string& typeNoeud ) const
{
   if (typeNoeud == type_)
      return this;
   else
      return 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::chercher( const std::string& typeNoeud )
///
/// Cette fonction cherche un noeud d'un type donn� parmi le noeud
/// lui-m�me et ses enfants.
///
/// Elle retourne donc le noeud lui-m�me si son type est celui pass� en
/// param�tre, ou 0 sinon.
///
/// @param[in] typeNoeud : Le type du noeud � trouver.
///
/// @return Le pointeur vers le noeud s'il est trouv�.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudAbstrait::chercher( const std::string& typeNoeud )
{
   if (typeNoeud == type_)
      return this;
   else
      return 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn const NoeudAbstrait* NoeudAbstrait::chercher( unsigned int indice ) const
///
/// Cette fonction cherche le i-�me enfant d'un noeud.
///
/// Elle retourne toujours 0 pour la classe de base, car cette
/// derni�re ne poss�de pas d'enfant.
///
/// @param[in] indice : L'indice du noeud � trouver.
///
/// @return Le pointeur vers le noeud s'il est trouv�.
///
////////////////////////////////////////////////////////////////////////
const NoeudAbstrait* NoeudAbstrait::chercher( unsigned int indice ) const
{
   return 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::chercher( unsigned int indice )
///
/// Cette fonction cherche le i-�me enfant d'un noeud.
///
/// Elle retourne toujours 0 pour la classe de base, car cette
/// derni�re ne poss�de pas d'enfant.
///
/// @param[in] indice : L'indice du noeud � trouver.
///
/// @return Le pointeur vers le noeud s'il est trouv�.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudAbstrait::chercher( unsigned int indice )
{
   return 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::ajouter(NoeudAbstrait* enfant)
///
/// Cette fonction ajoute un enfant � ce noeud.
///
/// Elle retourne toujours faux et ne fait rien, car ce type de noeud
/// abstrait ne peut pas avoir d'enfant.
///
/// @param[in] enfant: Le noeud � ajouter.
///
/// @return Vrai si l'ajout a bien �t� effectu�, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::ajouter(NoeudAbstrait* enfant)
{
   return false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudAbstrait::obtenirNombreEnfants() const
///
/// Cette fonction retourne le nombre d'enfants de ce noeud.
///
/// Elle retourne toujours 0, car ce type de noeud abstrait ne peut pas
/// avoir d'enfant.
///
/// @return Vrai si l'ajout a bien �t� effectu�, faux autrement.
///
////////////////////////////////////////////////////////////////////////
unsigned int NoeudAbstrait::obtenirNombreEnfants() const
{
   return 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::inverserSelection()
///
/// Cette fonction inverse l'�tat de s�lection de ce noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::inverserSelection()
{
   selectionne_ = !selectionne_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::effacerSelection()
///
/// Cette fonction efface les noeuds qui sont s�lectionn�s parmi les
/// enfants de ce noeud.
///
/// Elle ne fait rien, car ce type de noeud abstrait ne peut pas avoir
/// d'enfant.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::effacerSelection()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::selectionnerTout()
///
/// Cette fonction s�lectionne le noeud et ses enfants.
///
/// Elle ne fait que s�lectionner le noeud pour cette classe, car ce
/// type de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::selectionnerTout()
{
   assignerSelection(true);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::deselectionnerTout()
///
/// Cette fonction d�s�lectionne le noeud et ses enfants.
///
/// Elle ne fait que d�s�lectionner le noeud pour cette classe, car ce
/// type de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::deselectionnerTout()
{
   selectionne_ = false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::selectionExiste() const
///
/// Cette fonction v�rifie si le noeud ou un de ses enfants est
/// s�lectionn�.
///
/// Elle ne fait que regarder si le noeud est s�lectionn�, car ce type
/// de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Vrai s'il existe un noeud s�lectionn�, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::selectionExiste() const
{
   return selectionne_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::changerModePolygones( bool estForce )
///
/// Cette fonction change le mode de rendu des polygones du noeud s'il
/// est s�lectionn� ou si on le force.
///
/// @param[in] estForce: Vrai si on veut changer le mode m�me si le
///                      noeud n'est pas s�lectionn�.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::changerModePolygones( bool estForce )
{
   if ( ( estForce ) || ( estSelectionne() ) ) {
      if ( modePolygones_ == GL_FILL )
         modePolygones_ =  GL_LINE;
      else if ( modePolygones_ == GL_LINE )
         modePolygones_ = GL_POINT;
      else
         modePolygones_ = GL_FILL;
   }
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerModePolygones( GLenum modePolygones )
///
/// Cette fonction assigne le mode de rendu des polygones du noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerModePolygones( GLenum modePolygones )
{
   // Le mode par d�faut si on passe une mauvaise valeur est GL_FILL
   if ( (modePolygones != GL_FILL) &&
        (modePolygones != GL_LINE) &&
        (modePolygones != GL_POINT) ) {
      modePolygones = GL_FILL;
   }

   modePolygones_ = modePolygones;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::afficher() const
///
/// Cette fonction affiche le noeud comme tel.
///
/// Elle consiste en une template method (dans le sens du patron de
/// conception, et non les template C++) qui effectue ce qui est
/// g�n�ralement � faire pour l'affichage, c'est-�-dire:
/// - Mise en pile de la matrice de transformation
/// - Translation du noeud pour qu'il soit � sa position relative
/// - Utilisation du mode d'affichage des polygones
/// - ...
/// - Restauration de l'�tat.
///
/// L'affichage comme tel est confi� � la fonction afficherConcret(),
/// appel�e par la fonction afficher().
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::afficher() const
{
	if (affiche_) {
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT | GL_POLYGON_BIT);

		// La translation de la position relative
		glTranslated(
			positionRelative_[0], positionRelative_[1], positionRelative_[2]
		);
	  
		// La rotation et l'�chelle sont g�r�es ici, pas dans afficherConcret()
		glRotated(angleRotation_, 0, 0, 1);
		glScaled(echelle_, echelle_, echelle_);

		// Assignation du mode d'affichage des polygones
		glPolygonMode( GL_FRONT_AND_BACK, modePolygones_ );
     
		// Affichage concret
		afficherConcret();
      
		// Restauration
		glPopAttrib();
		glPopMatrix();
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.  Elle est
/// appel�e par la template method (dans le sens du patron de conception,
/// et non des template C++) afficher() de la classe de base.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::afficherConcret() const
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::animer( float dt )
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// Elle ne fait rien pour cette classe et vise � �tre surcharger par
/// les classes d�riv�es.
///
/// @param[in] dt : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::animer( float temps )
{
	appliquerPhysique(temps);
}

void NoeudAbstrait::appliquerPhysique(float temps)
{
	if (this->dynamique_)
	{
		// Appliquer l'accel�ration � la vitesse
		this->vitesse_ += this->acceleration_ * temps;

		// Appliquer la vitesse � la position
		this->positionRelative_ += this->vitesse_ * temps;
	}
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
void NoeudAbstrait::accepter(VisiteurAbstrait& visiteur)
{
	visiteur.visiter(*this);
}



////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::accepterXML(VisiteurXml& visiteur,TiXmlElement* parentactu)
///
///
/// Cette fonction accepter le visiteur xml et lui permettre de faire son traitement 
/// sur l'objet appellant 
///
///
/// @param[in] visiteur : un objet visiteur
/// @param[in] visiteur : �l�ment xml parent
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::accepterXML(VisiteurXml& visiteur,TiXmlElement* parentactu)
{
	visiteur.visitNoeudAbstrait(this,parentactu);
}

void NoeudAbstrait::obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY) const
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudAbstrait::obtenirSphereEnglobante()
///
/// Cette fonction retourne la sphere englobante
///
/// @return (double) Rayon de la sph�re.
///
////////////////////////////////////////////////////////////////////////
double NoeudAbstrait::obtenirSphereEnglobante() const
{
	return 0.0f;
}


void NoeudAbstrait::reinitialiser()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::setEchelle(double e)
///
/// Cette fonction modifie la valeur de l'echelle
///
/// @param[in] e : la nouvelle valeur de l'echelle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::setEchelle(double e)
{
	this->echelle_ = e;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::setAngleRotation(double angleRotation)
///
/// Cette fonction modifie la valeur de l'angle
/// 
/// @param[in] angleRotation : nouvelle angle de rotation
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::setAngleRotation(double angleRotation)
{
	 angleRotation_ = fmod(angleRotation + 360, 360);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudAbstrait::getAngleRotation()
///
/// Cette fonction retourne l'angle de rotation
/// 
/// @param[in] : aucune
///
/// @return l'angle de rotation.
///
////////////////////////////////////////////////////////////////////////
double NoeudAbstrait::getAngleRotation() const
{
	return angleRotation_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn Vecteur3 NoeudAbstrait::getPosition() const 
///
/// Cette fonction retourne  les cordonn�es de la position relative
/// 
/// @param[in] : aucune
///
/// @return positionRelative_ : les cordonn�es de la position relative
///
////////////////////////////////////////////////////////////////////////
Vecteur3 NoeudAbstrait::getPosition() const 
{
	return positionRelative_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudAbstrait::getEchelle() const
///
/// Cette fonction retourne la valeur de l'echelle
/// 
/// @param[in] : aucune
///
/// @return echelle_ : la taille de l'objet
///
////////////////////////////////////////////////////////////////////////
double NoeudAbstrait::getEchelle() const
{
	return echelle_;
}


void NoeudAbstrait::appliquerForce(Vecteur3 force)
{
	this->forces_ += force;
}


double NoeudAbstrait::obtenirMasse()
{
	return masse_;
}

void NoeudAbstrait::assignerMasse(double masse)
{
	masse_ = masse;
}

////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////
