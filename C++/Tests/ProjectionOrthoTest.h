//////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrthoTest.h
/// @author Najib Arbaoui
/// @date 2014-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_PROJECTIONORTHOTEST_H
#define _TESTS_PROJECTIONORTHOTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "ProjectionOrtho.h"

///////////////////////////////////////////////////////////////////////////
/// @class ProjectionOrthoTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        m�thodes de la classe ProjectionOrtho
///
/// @author Najib Arbaoui
/// @date 2014-02
///////////////////////////////////////////////////////////////////////////
class ProjectionOrthoTest : public CppUnit::TestFixture
{
	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
   CPPUNIT_TEST_SUITE( ProjectionOrthoTest );
   CPPUNIT_TEST( test_rapportAspect );
   CPPUNIT_TEST( test_zoomerIn );
   CPPUNIT_TEST( test_zoomerOut );
   CPPUNIT_TEST( test_redimensionnerFenetre );
   CPPUNIT_TEST( test_zoomerInElastique );
   CPPUNIT_TEST( test_zoomerOutElastique );
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

	/// Cas de test: Il faut alors que la projection corrige le rapport d'aspect de la fen�tre virtuelle en fonction de la cl�ture.
	void test_rapportAspect();
	/// Cas de test: Zoom in sur la fen�tre virtuelle. Regarde le rapport d'aspect final.
	void test_zoomerIn();
	/// Cas de test: la r�gion du monde virtuel visible dans la fen�tre avant l�application du zoom doit �tre compl�tement contenue, apr�s l�application du zoom, dans la r�gion d�finie par le rectangle �lastique
	void test_zoomerOut();
	/// Cas de test: Redimensionne la fen�tre avec un autre rapport d'aspect pour la cl�ture.
	void test_redimensionnerFenetre();
	/// Cas de test: La nouvelle fen�tre virtuelle sp�cifi� devient la fen�tre virtuelle. On v�rifie le rapport d'aspect.
	void test_zoomerInElastique();
	/// Cas de test: Choisit une nouvelle fen�tre virtuelle avec un rapport diff�rent de la derni�re pour un zoom out.
	void test_zoomerOutElastique();

	private:
		void obtenirInformationsFenetreVirtuelle(
			Vecteur2& vec2Min, Vecteur2& vec2Max,
			double& dAspectRatio
			);

		void obtenirInformationsCloture(
			Vecteur2i& vec2iDimensionCloture,
			Vecteur2i& vec2iMin, Vecteur2i& vec2iMax,
			double& dAspectRatio
			);
		
		void validerRapportAspect(
			const Vecteur2i& vec2iDimensionCloture,
			const Vecteur2& vec2FenetreMin, const Vecteur2& vec2FenetreMax
			);

	/// Instance d'une projection orthogonale.
	vue::ProjectionOrtho *m_oProjectionOrtho;
	double m_dIncrementZoom;
};

#endif // _TESTS_PROJECTIONORTHOTEST_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
