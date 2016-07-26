///////////////////////////////////////////////////////////////////////////////
/// @file NoeudAbstrait.h
/// @author DGI-INF2990
/// @date 2007-01-24
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDABSTRAIT_H__
#define __ARBRE_NOEUDS_NOEUDABSTRAIT_H__


#include <windows.h>
#include <GL/gl.h>
#include <string>

#pragma once
#include "Vecteur.h"
#include "Visiteurs\VisiteurAbstrait.h"
#include "tinyxml.h"
//#include "Visiteurs\VisiteurXml.h"

class VisiteurXml;
//class VisiteurAbstrait;
///////////////////////////////////////////////////////////////////////////
/// @class NoeudAbstrait
/// @brief Classe de base du patron composite utilis�e pour cr�er l'arbre
///        de rendu.
///
///        Cette classe abstraite comprend l'interface de base que doivent
///        implanter tous les noeuds pouvant �tre pr�sent dans l'arbre de
///        rendu.
///
/// @author DGI-2990
/// @date 2007-01-24
///////////////////////////////////////////////////////////////////////////
class NoeudAbstrait
{
public:
   /// Constructeur.
   NoeudAbstrait(
      const std::string& type = std::string( "" )
      );
   //////////////////
   /// Destructeur.
   virtual ~NoeudAbstrait();

   /// Obtient le parent de ce noeud.
   inline NoeudAbstrait* obtenirParent();

   /// Obtient le parent de ce noeud (version constante).
   inline const NoeudAbstrait* obtenirParent() const;

   /// Assigne le parent de ce noeud.
   inline void assignerParent( NoeudAbstrait* parent );
   
   /// Obtient la position relative du noeud.
   inline const Vecteur3& obtenirPositionRelative() const;

   /// Obtient la vitesse du noeud.
   inline const Vecteur3& obtenirVitesse() const;

   /// Assigne la vitesse du noeud.
   inline void assignerVitesse(const Vecteur3& vitesse);

   /// Assigne la position relative du noeud.
   inline void assignerPositionRelative(const Vecteur3& positionRelative);

   /// Obtient le type du noeud.
   inline const std::string& obtenirType() const;

   /// �crit l'�tat de l'affichage du du noeud.
   inline void assignerAffiche( bool affiche );
   /// V�rifie si le noeud se fait afficher.
   inline bool estAffiche() const;

   /// �crit l'�tat de la s�lection du noeud.
   inline void assignerSelection( bool selectionne );
   /// V�rifie si le noeud est s�lectionn�.
   inline bool estSelectionne() const;
   /// �crit si le noeud peut �tre s�lectionn� ou non.
   inline void assignerEstSelectionnable( bool selectionnable );
   /// V�rifie si le noeud est s�lectionnable.
   inline bool estSelectionnable() const;
   /// �crit si le noeud peut �tre enregistr� ou non.
   inline void assignerEstEnregistrable( bool enregistrable );
   /// V�rifie si le noeud est enregistrable.
   inline bool estEnregistrable() const;



   // Interface d'un noeud

   /// Calcule la profondeur de l'arbre sous le noeud courant.
   virtual unsigned int calculerProfondeur() const;

   /// Vide le noeud de ses enfants.
   virtual void vider();
   /// Efface le noeud pass� en param�tre.
   virtual void effacer( const NoeudAbstrait* noeud );

   /// Cherche un noeud par le type (sur un noeud constant).
   virtual const NoeudAbstrait* chercher( const std::string& typeNoeud ) const;
   /// Cherche un noeud par le type.
   virtual NoeudAbstrait* chercher( const std::string& typeNoeud );
   /// Cherche un noeud enfant selon l'indice (sur un noeud constant).
   virtual const NoeudAbstrait* chercher( unsigned int indice ) const;
   /// Cherche un noeud enfant selon l'indice.
   virtual NoeudAbstrait* chercher( unsigned int indice );

   /// Ajoute un noeud enfant.
   virtual bool ajouter( NoeudAbstrait* enfant );
   /// Obtient le nombre d'enfants du noeud.
   virtual unsigned int obtenirNombreEnfants() const;

   /// Changer la s�lection du noeud.
   virtual void inverserSelection();

   /// Efface les enfants s�lectionn�s.
   virtual void effacerSelection();

   /// S�lectionne tous les enfants de m�me que le noeud.
   virtual void selectionnerTout();

   /// D�s�lectionne tous les enfants de m�me que le noeud.
   virtual void deselectionnerTout();

   /// V�rifier si le noeud ou un de ses enfants est s�lectionn�.
   virtual bool selectionExiste() const;
  
   /// Change le mode d'affichage des polygones.
   virtual void changerModePolygones( bool estForce );

   /// Assigne le mode d'affichage des polygones.
   virtual void assignerModePolygones( GLenum modePolygones );

   /// Affiche le noeud.
   virtual void afficher() const;

   /// Affiche le noeud de mani�re concr�te.
   virtual void afficherConcret() const;

   /// Anime le noeud.
   virtual void animer( float temps );

    // Accepter visiteur
   virtual void accepter(VisiteurAbstrait& unVisiteur);
   void accepterXML(VisiteurXml& visiteur, TiXmlElement* parentactu);
   //facteur echelle modificateur
   virtual void setEchelle(double e);
  
   //obtenir l'echelle de l'objet
   virtual double getEchelle() const;

   //obtenir la position relative de l'objet
   virtual Vecteur3 getPosition() const;

   // modifie l'angle de l'angle de rotation
   virtual void setAngleRotation(double angleRotation);

   //obtenir l'angle de rotation
   virtual double getAngleRotation() const;

   // obtenir la boite qui englobe l'objet
   virtual void obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY) const;
   virtual double obtenirSphereEnglobante() const;

   // R�initialise le noeud pour l'�tat initiale apr�s le jeu
   virtual void reinitialiser();

   // Appliquer une force � l'objet
   void appliquerForce(Vecteur3 force);

   double obtenirMasse();
	void assignerMasse(double masse);



protected:
   /// Type du noeud.
   std::string      type_;

   /// Mode d'affichage des polygones.
   GLenum           modePolygones_;

   /// Position relative du noeud.
   Vecteur3         positionRelative_;
   Vecteur3 vitesse_;
   Vecteur3 acceleration_;
   // vitesse maximale
   double vitesseMax_;

   //Forces appliqu� au noeud
   Vecteur3 forces_;

   /// Vrai si on doit afficher le noeud.
   bool             affiche_;

   /// S�lection du noeud.
   bool             selectionne_;

   /// Vrai si le noeud est s�lectionnable.
   bool             selectionnable_;

   /// D�termine si l'objet peut �tre sauvegard� en XML.
   bool             enregistrable_;

   // D�termine si l'objet est statique ou dynamique (bouge ou non)
   bool dynamique_;

   //le facteur echelle
   double			echelle_;

   // La masse de l'objet
   double masse_;

   /// Pointeur vers le parent.
   NoeudAbstrait*   parent_;

   ///l'angle de rotation
   double angleRotation_;

   virtual void appliquerPhysique(float temps);
};




////////////////////////////////////////////////////////////////////////
///
/// @fn inline NoeudAbstrait* NoeudAbstrait::obtenirParent()
///
/// Cette fonction retourne le pointeur vers le parent de ce noeud.
///
/// @return Le pointeur vers le parent.
///
////////////////////////////////////////////////////////////////////////
inline NoeudAbstrait* NoeudAbstrait::obtenirParent()
{
   return parent_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const NoeudAbstrait* NoeudAbstrait::obtenirParent() const
///
/// Cette fonction retourne le pointeur constant vers le parent de ce noeud.
///
/// @return Le pointeur constant vers le parent.
///
////////////////////////////////////////////////////////////////////////
inline const NoeudAbstrait* NoeudAbstrait::obtenirParent() const
{
   return parent_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerParent( NoeudAbstrait* parent )
///
/// Cette fonction assigne le parent du noeud afin qu'il soit possible
/// de remonter dans l'arbre.
///
/// @param[in] parent : Le parent du noeud.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerParent(
   NoeudAbstrait* parent
   )
{
   parent_       = parent;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const Vecteur3& NoeudAbstrait::obtenirPositionRelative() const
///
/// Cette fonction retourne la position relative du noeud par rapport
/// � son parent.
///
/// @return La position relative.
///
////////////////////////////////////////////////////////////////////////
inline const Vecteur3& NoeudAbstrait::obtenirPositionRelative() const
{
   return positionRelative_;
}

/// Obtient la vitesse du noeud.
inline const Vecteur3& NoeudAbstrait::obtenirVitesse() const
{
	return vitesse_;
}

/// Assigne la vitesse du noeud.
inline void NoeudAbstrait::assignerVitesse(const Vecteur3& vitesse)
{
	vitesse_ = vitesse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerPositionRelative( const Vecteur3& positionRelative )
///
/// Cette fonction permet d'assigner la position relative du noeud par
/// rapport � son parent.
///
/// @param positionRelative : La position relative.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerPositionRelative(
   const Vecteur3& positionRelative
   )
{
   positionRelative_ = positionRelative;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const std::string& NoeudAbstrait::obtenirType() const
///
/// Cette fonction retourne une cha�ne repr�sentante le type du noeud.
///
/// @return Le type du noeud.
///
////////////////////////////////////////////////////////////////////////
inline const std::string& NoeudAbstrait::obtenirType() const
{
   return type_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerAffiche( bool affiche )
///
/// Cette fonction permet d'assigner si le noeud se fait afficher ou
/// non lorsque l'arbre de rendu se fait afficher.  Elle permet donc
/// de temporairement suspendre ou activer l'affichage d'un noeud.
///
/// @param affiche : L'�tat affich� ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerAffiche( bool affiche )
{
   affiche_ = affiche;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estAffiche() const
///
/// Cette fonction retourne l'�tat que le noeud se fait afficher ou non.
///
/// @return L'�tat affich� ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estAffiche() const
{
   return affiche_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerSelection( bool selectionne )
///
/// Cette fonction permet d'assigner l'�tat d'�tre s�lectionn� ou non du noeud.
///
/// @param selectionne : L'�tat s�lectionn� ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerSelection( bool selectionne )
{
   // Un objet non s�lectionnable n'est jamais s�lectionn�.
   selectionne_ = (selectionne && selectionnable_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estSelectionne() const
///
/// Cette fonction retourne l'�tat d'�tre s�lectionn� ou non du noeud.
///
/// @return L'�tat s�lectionn� ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estSelectionne() const
{
   // Un objet non s�lectionnable n'est jamais s�lectionn�.
   return (selectionne_ && selectionnable_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerEstSelectionnable( bool selectionnable )
///
/// Cette fonction permet d'assigner l'�tat d'�tre s�lectionnable ou non du noeud.
///
/// @param selectionnable : L'�tat s�lectionnable ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerEstSelectionnable( bool selectionnable )
{
   selectionnable_ = selectionnable;
   selectionne_    = selectionne_ && selectionnable_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estSelectionnable() const
///
/// Cette fonction retourne l'�tat d'�tre s�lectionnable ou non du noeud.
///
/// @return L'�tat s�lectionnable ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estSelectionnable() const
{
   return selectionnable_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerEstEnregistrable( bool enregistrable )
///
/// Cette fonction permet d'assigner l'�tat d'�tre entregistrable ou non du noeud.
///
/// @param enregistrable : L'�tat enregistrable ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerEstEnregistrable( bool enregistrable )
{
   enregistrable_ = enregistrable;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estEnregistrable() const
///
/// Cette fonction retourne l'�tat d'�tre enregistrable en XML ou non du
/// noeud.
///
/// @return L'�tat enregistrable ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estEnregistrable() const
{
   return enregistrable_;
}


#endif // __ARBRE_NOEUDS_NOEUDABSTRAIT_H__




///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
