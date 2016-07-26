//////////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.h
/// @author Najib Arbaoui
/// @date 2014-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_ARBRERENDUTEST_H
#define _TESTS_ARBRERENDUTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "ArbreRenduINF2990.h"

class ArbreRenduINF2990Test : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
  CPPUNIT_TEST_SUITE( ArbreRenduINF2990Test );
  CPPUNIT_TEST( test_chercherUsine );
  CPPUNIT_TEST( test_creerNoeud );
  CPPUNIT_TEST( test_ajouter );
  CPPUNIT_TEST( test_ajouterNouveauNoeud );
  CPPUNIT_TEST( test_obtenirType );
  CPPUNIT_TEST_SUITE_END();
  public:

	// =================================================================
	// M�thodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement � effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement � effectuer pour 'finaliser' cette suite de tests
	void tearDown();


	// =================================================================
	// D�finissez ici les diff�rents cas de tests...
	// =================================================================

	/// Cas de test: On cr�er tous les types de noeuds possible. Si l'on est incapable de trouver l'usine pour le noeud, le noeud est NULL 
	void test_creerNoeud();

	/// Cas de test: V�rifie si toutes les usines possibles sont pr�sentent.
	void test_chercherUsine();

	/// Cas de test: Voir si tous les noeuds possibles cr�es peuvent �tre ajout� � l'arbre de rendu
	void test_ajouter();

	/// On va tent� d'ajouter des noeud � un noeud ne pouvant pas contenir d'enfants.
	void test_ajouterNouveauNoeud();

	/// Cas de test: Les noeuds cr�er � partir des usines sont-ils du bons type?
	void test_obtenirType();

private:
	/// Instance d'un arbre de rendu sp�cifique au projet INF2990
	ArbreRenduINF2990* m_oArbreRenduINF2990;
	/// Tient compte des instances de tous les noeuds possible
	std::map<std::string, NoeudAbstrait* > m_mapInstanceNoeud;
};

#endif // _TESTS_ARBRERENDUTEST_

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////