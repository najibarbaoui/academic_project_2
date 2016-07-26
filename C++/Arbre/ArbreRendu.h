///////////////////////////////////////////////////////////////////////////////
/// @file ArbreRendu.h
/// @author Martin Bisson
/// @date 2007-01-28
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_ARBRERENDU_H__
#define __ARBRE_ARBRERENDU_H__


#include "NoeudComposite.h"

#include <string>
#include <map>


class NoeudAbstrait;
class UsineNoeud;


///////////////////////////////////////////////////////////////////////////
/// @class ArbreRendu
/// @brief Classe d'arbre de rendu qui contient la racine de l'arbre de
///        rendu avec les usines qui permettent d'ajouter des noeuds �
///        cet arbre.
///
///        La profondeur de cet arbre est limit�e par la taille de la pile
///        des matrices et la taille de la pile des noms pour la s�lection
///        OpenGL, �tant donn� que chaque niveau de l'arbre effectue un
///        "push" sur chacune de ces piles lors du rendu.  L'arbre ne
///        v�rifie pas que la profondeur reste sous la limite, mais il
///        offre des fonctions permettant de le v�rifier ais�ment.
///
/// @author Martin Bisson
/// @date 2007-01-28
///////////////////////////////////////////////////////////////////////////
class ArbreRendu : public NoeudComposite
{
public:
   /// Constructeur par d�faut.
   ArbreRendu();
   /// Destructeur.
   virtual ~ArbreRendu();

   /// Ajoute une usine associ�e � un type de noeud.
   inline void ajouterUsine(
      const std::string& type, const UsineNoeud* usine
      );

   /// Cr�e un nouveau noeud.
   NoeudAbstrait* creerNoeud(
      const std::string& typeNouveauNoeud
      ) const;

   /// Cr�e et ajoute un nouveau noeud � l'arbre.
   NoeudAbstrait* ajouterNouveauNoeud(
      const std::string& nomParent,
      const std::string& typeNouveauNoeud
      );

   /// Calcule la profondeur maximale possible pour l'arbre de rendu.
   static unsigned int calculerProfondeurMaximale();

   inline const UsineNoeud* chercherUsine(const std::string& type);

   
   virtual void setAsterpsec(int asterpsec);

   virtual void setAccelbonus(int accel);

   virtual void setNbstatsauv(int nb);

   virtual void setDifficulte(int diff);

   virtual int getAsterpsec() const;

   virtual int getAccelbonus() const;

   virtual int getNbstatsauv() const;

   virtual int getDifficulte() const;

private:
   /// D�finition du type pour l'association du nom d'un type vers l'usine
   /// correspondante.
   typedef std::map< std::string, const UsineNoeud* > RegistreUsines;
   /// Association du nom d'un type vers l'usine correspondante.
   RegistreUsines usines_;
      int asteroidepsec_;

  int accelbonus_ ;

   int nbstatsauv_;

   int difficulte_;

};


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void ArbreRendu::ajouterUsine(const std::string& type, const UsineNoeud* usine)
///
/// Cette fonction permet d'ajouter une usine qui sera ensuite utilis�e
/// pour cr�er de nouveaux noeuds.
///
/// @param[in] type  : La cha�ne qui identifie le type de noeuds � cr�er
///                    avec cette usine.
/// @param[in] usine : L'usine ajout�e.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void ArbreRendu::ajouterUsine(
   const std::string& type, const UsineNoeud* usine
   )
{
   usines_[type] = usine;
}

inline const UsineNoeud* ArbreRendu::chercherUsine(const std::string& type)
{
	RegistreUsines::const_iterator it;
	it = usines_.find(type);
	if(it != usines_.end()) {
		return usines_[type];
	}
	return NULL;
}


#endif // __ARBRE_ARBRERENDU_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
