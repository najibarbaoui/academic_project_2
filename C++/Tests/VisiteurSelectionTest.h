//////////////////////////////////////////////////////////////////////////////
/// @file VisiteurSelectionTest.h
/// @author Najib Arbaoui
/// @date 2014-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_VISITEURSELECTIONTEST_H
#define _TESTS_VISITEURSELECTIONTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "..\Arbre\Visiteurs\VisiteurSelection.h"
#include "ArbreRenduINF2990.h"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurSelectionTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        m�thodes de la classe VisiteurSelection
///
/// @author Najib Arbaoui
/// @date 2014-02
///////////////////////////////////////////////////////////////////////////
class VisiteurSelectionTest : public CppUnit::TestFixture
{
	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
   CPPUNIT_TEST_SUITE( VisiteurSelectionTest );
   CPPUNIT_TEST( test_SelectionnableUnique );
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

	/// Cas de test: Test d'un objet s�lectionnable unique.
	void test_SelectionnableUnique();

	private:
		/// Instance d'un arbre de rendu sp�cifique au projet INF2990 que le visiteur parcourera
		ArbreRenduINF2990 *m_oArbreRenduINF2990;
		/// Instance du visieur qui parcourera l'arbre de rendu
		VisiteurSelection *m_oVisiteurSelection;
		/// Tient compte des instances de tous les noeuds possible
		std::map<std::string, NoeudAbstrait*> m_mapInstanceNoeud;
};

#endif // _TESTS_VISITEURSELECTIONTEST_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
