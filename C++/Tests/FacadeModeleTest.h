//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModeleTest.h
/// @author Najib Arbaoui
/// @date 2014-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_FACADEMODELTEST_H
#define _TESTS_FACADEMODELTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"

class FacadeModeleTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
  CPPUNIT_TEST_SUITE( FacadeModeleTest );
  CPPUNIT_TEST( testObtenirInstance );
  CPPUNIT_TEST( testSelectionObjet );
  CPPUNIT_TEST( testsupprimerNoeudSelectione );
  CPPUNIT_TEST( testDeplacerObjet );
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

	/// Cas de test: On v�rifie que la requ�te d'une instance du singleton nous retourne bien un pointeur valide.
	void testObtenirInstance();

	/// Cas de test: type de noeud
	void testLibererInstance();

	/// Cas de test: On s�lectionner plusieurs noeuds cons�cutivement.
	void testSelectionObjet();

	/// Cas de test: On supprime un noeud que l'on a s�lectionn�
	void testsupprimerNoeudSelectione();

	/// Cas de test: On d�place le noeud et on le selectionne � sa nouvelle position.
	void testDeplacerObjet();
};

#endif // _TESTS_FACADEMODELTEST_

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
