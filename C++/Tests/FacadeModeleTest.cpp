////////////////////////////////////////////////////////////////////////////////////
/// @file FacadeModeleTest.cpp
/// @author Najib Arbaoui
/// @date 2011-07-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "FacadeModeleTest.h"
#include "FacadeModele.h"
#include "Utilitaire.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION( FacadeModeleTest );

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModeleTest::setUp()
///
/// Effectue l'initialisation pr�alable � l'ex�cution de l'ensemble des
/// cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets doivent �tre construits, il est conseill� de le
/// faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModeleTest::setUp()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModeleTest::tearDown()
///
/// Effectue les op�rations de finalisation n�cessaires suite � l'ex�cution
/// de l'ensemble des cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets ont �t� allou�s � l'initialisation, ils doivent �tre
/// d�sallou�s, et il est conseill� de le faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModeleTest::tearDown()
{
	FacadeModele::libererInstance();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModeleTest::testObtenirInstance()
///
/// Cas de test: On v�rifie que la requ�te d'une instance du singleton nous retourne bien un pointeur valide.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModeleTest::testObtenirInstance()
{
	CPPUNIT_ASSERT(FacadeModele::obtenirInstance());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModeleTest::testSelectionObjet()
///
/// Cas de test: On s�lectionner plusieurs noeuds cons�cutivement
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModeleTest::testSelectionObjet()
{
	// Par d�faut, l'arbre de rendu poss�de une zone de jeu (donc n'est pas vide). La zone de jeu est de profondeur 1.
	CPPUNIT_ASSERT (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(ArbreRenduINF2990::NOM_ZONEJEU));
	CPPUNIT_ASSERT(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->calculerProfondeur() == 2);
	CPPUNIT_ASSERT(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNombreEnfants() == 1);

	// Cr�er un noeud et l'ajoute � l'arbre
	FacadeModele::obtenirInstance()->creerNoeud(3, 3, ArbreRenduINF2990::NOM_ASTEROIDE);
	FacadeModele::obtenirInstance()->selectionObjet(Vecteur3(3, 3, 0), Vecteur3(5, 5, 0), false);
	
	// On a bien choisit un noeud, le nouveau noeud et pr�sent dans l'Arbre
	CPPUNIT_ASSERT (FacadeModele::obtenirInstance()->obtenirVectNoeudSelectione().size() == 1);
	CPPUNIT_ASSERT (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(ArbreRenduINF2990::NOM_ASTEROIDE));
	CPPUNIT_ASSERT (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(ArbreRenduINF2990::NOM_ZONEJEU));
	CPPUNIT_ASSERT (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->calculerProfondeur() == 2);
	CPPUNIT_ASSERT (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNombreEnfants() == 2);

	FacadeModele::obtenirInstance()->creerNoeud(10, 5, ArbreRenduINF2990::NOM_VAISSEAU);
	FacadeModele::obtenirInstance()->selectionObjet(Vecteur3(0, 0, 0), Vecteur3(15, 15, 0), false);
	CPPUNIT_ASSERT (FacadeModele::obtenirInstance()->obtenirVectNoeudSelectione().size() == 2);
	CPPUNIT_ASSERT (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(ArbreRenduINF2990::NOM_ASTEROIDE));
	CPPUNIT_ASSERT (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(ArbreRenduINF2990::NOM_VAISSEAU));
	CPPUNIT_ASSERT (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(ArbreRenduINF2990::NOM_ZONEJEU));
	CPPUNIT_ASSERT (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->calculerProfondeur() == 2);
	CPPUNIT_ASSERT (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNombreEnfants() == 3);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModeleTest::testsupprimerNoeudSelectione()
///
/// Cas de test: On supprime un noeud que l'on a s�lectionn�
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModeleTest::testsupprimerNoeudSelectione()
{
	// Un enfant de profondeur 1, donc une arbre profondeur de 2 (zone de jeu par d�faut).
	CPPUNIT_ASSERT (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(ArbreRenduINF2990::NOM_ZONEJEU));
	CPPUNIT_ASSERT(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->calculerProfondeur() == 2);
	CPPUNIT_ASSERT(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNombreEnfants() == 1);

	// Cr�er un noeud et l'ajoute � l'arbre
	FacadeModele::obtenirInstance()->creerNoeud(3, 3, ArbreRenduINF2990::NOM_ASTEROIDE);
	FacadeModele::obtenirInstance()->selectionObjet(Vecteur3(3, 3, 0), Vecteur3(5, 5, 0), false);

	// On supprime le noeud ast�roide (nous l'Avions cr�e � la position (4, 4)).
	FacadeModele::obtenirInstance()->selectionObjet(Vecteur3(2, 2, 0), Vecteur3(6, 6, 0), false);
	FacadeModele::obtenirInstance()->supprimerNoeudSelectione();

	// Un enfant de profondeur 1, donc une arbre profondeur de 2
	CPPUNIT_ASSERT (!FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(ArbreRenduINF2990::NOM_ASTEROIDE));
	CPPUNIT_ASSERT (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(ArbreRenduINF2990::NOM_ZONEJEU));
	CPPUNIT_ASSERT (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNombreEnfants() == 1);
	CPPUNIT_ASSERT (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->calculerProfondeur() == 2);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::testType()
///
/// Cas de test: On d�place le noeud et on le selectionne � sa nouvelle position.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModeleTest::testDeplacerObjet()
{
	FacadeModele::obtenirInstance()->creerNoeud(0, 0, ArbreRenduINF2990::NOM_VAISSEAU);
	FacadeModele::obtenirInstance()->deplacerObjet(Vecteur3(1, 1, 0));
	FacadeModele::obtenirInstance()->selectionObjet(Vecteur3(0, 0, 0), Vecteur3(2, 2, 0), false);
	CPPUNIT_ASSERT(FacadeModele::obtenirInstance()->obtenirVectNoeudSelectione().size() == 1);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
