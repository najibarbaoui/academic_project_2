//////////////////////////////////////////////////////////////////////////////
/// @file NoeudCompositeTest.h
/// @author Najib Arbaoui
/// @date 2014-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_NOEUDCOMPOSITETEST_H
#define _TESTS_NOEUDCOMPOSITETEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "ArbreRenduINF2990.h"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurSelectionTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        m�thodes de la classe VisiteurSelection
///
/// @author Najib Arbaoui
/// @date 2014-02
///////////////////////////////////////////////////////////////////////////
class NoeudCompositeTest : public CppUnit::TestFixture
{
	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
   CPPUNIT_TEST_SUITE( NoeudCompositeTest );
   CPPUNIT_TEST( test_effacer );
   CPPUNIT_TEST( test_selectionnerTout );
   CPPUNIT_TEST( test_deselectionnerTout );
   CPPUNIT_TEST( test_obtenirNombreEnfants );
   CPPUNIT_TEST( test_effacerSelection );
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
	// Cas de tests...
	// =================================================================

	/// On efface les noeuds une � un dans l'arbre
	void test_effacer();

	/// Cas de test: On s�lectionne l'arbre en entier. Certains noeuds ne sont pas s�lectionnable.
	void test_selectionnerTout();

	/// Cas de test: On s�lectionne l'arbre en entier, et on le d�s�lectionne. Certains noeuds sont non-s�lectionnable.
	void test_deselectionnerTout();

	/// Cas de test: Le noeud composite (l'arbre de rendu inf2990) contient les 10 enfants que nous lui avons rajout�.
	void test_obtenirNombreEnfants();

	/// Cas de test: On vide l'arbre gr�ce � la s�lection. Puisque la zone de jeu ne peut pas �tre s�lectionn�, c'est le seul noeud restant.
	void test_effacerSelection();

	private:
		/// Instance d'un arbre de rendu sp�cifique au projet INF2990 que le visiteur parcourera
		ArbreRenduINF2990 *m_oArbreRenduINF2990;
		/// Tient compte des instances de tous les noeuds possible
		std::map<std::string, NoeudAbstrait*> m_mapInstanceNoeud;
};


#endif // _TESTS_NOEUDCOMPOSITETEST_H