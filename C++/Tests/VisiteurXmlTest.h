//////////////////////////////////////////////////////////////////////////////
/// @file VisiteurXmlTest.h
/// @author Najib Arbaoui
/// @date 2014-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_VISITEURXMLTEST_H
#define _TESTS_VISITEURXMLTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "ArbreRenduINF2990.h"
#include "../Arbre/Visiteurs/VisiteurXml.h"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurXmlTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        m�thodes de la classe VisiteurXml
///
/// @author Najib Arbaoui
/// @date 2014-02
///////////////////////////////////////////////////////////////////////////
class VisiteurXmlTest : public CppUnit::TestFixture
{
	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
   CPPUNIT_TEST_SUITE( VisiteurXmlTest );
   CPPUNIT_TEST( test_saveXML );
   CPPUNIT_TEST( test_loadXML );
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

	/// Cas de test: La sauvegarde d'un fichier xml est-elle fonctionelle.
	void test_saveXML();

	/// Cas de test: Peut-on reconstruire une arbre de rendu avec un fichier XML sauveard�.
	void test_loadXML();

	private:
		/// Instance d'un arbre de rendu sp�cifique au projet INF2990 que le visiteur parcourera
		ArbreRenduINF2990 *m_oArbreRenduINF2990;
		/// Tient compte des instances de tous les noeuds possible
		std::map<std::string, NoeudAbstrait*> m_mapInstanceNoeud;

		void _VerifierNoeud(NoeudAbstrait *noeud);
};

#endif // _TESTS_VISITEURXMLTEST_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
