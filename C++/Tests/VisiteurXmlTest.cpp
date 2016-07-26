//////////////////////////////////////////////////////////////////////////////
/// @file VisiteurXmlTest.cpp
/// @author Najib Arbaoui
/// @date 2014-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "VisiteurXmlTest.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION( VisiteurXmlTest );

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurXmlTest::setUp()
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
void VisiteurXmlTest::setUp()
{
	m_oArbreRenduINF2990 = new ArbreRenduINF2990();

	/// Cr�ation des noeuds
	m_mapInstanceNoeud.insert(pair<string, NoeudAbstrait*>(ArbreRenduINF2990::NOM_ASTEROIDE, m_oArbreRenduINF2990->creerNoeud(ArbreRenduINF2990::NOM_ASTEROIDE)));
	m_mapInstanceNoeud.insert(pair<string, NoeudAbstrait*>(ArbreRenduINF2990::NOM_BARRIEREPROTECTRICE, m_oArbreRenduINF2990->creerNoeud(ArbreRenduINF2990::NOM_BARRIEREPROTECTRICE)));
	m_mapInstanceNoeud.insert(pair<string, NoeudAbstrait*>(ArbreRenduINF2990::NOM_BONUSACCELERATEUR, m_oArbreRenduINF2990->creerNoeud(ArbreRenduINF2990::NOM_BONUSACCELERATEUR)));
	m_mapInstanceNoeud.insert(pair<string, NoeudAbstrait*>(ArbreRenduINF2990::NOM_PORTAIL, m_oArbreRenduINF2990->creerNoeud(ArbreRenduINF2990::NOM_PORTAIL)));
	m_mapInstanceNoeud.insert(pair<string, NoeudAbstrait*>(ArbreRenduINF2990::NOM_POSITIONDEPART, m_oArbreRenduINF2990->creerNoeud(ArbreRenduINF2990::NOM_POSITIONDEPART)));
	m_mapInstanceNoeud.insert(pair<string, NoeudAbstrait*>(ArbreRenduINF2990::NOM_PROJECTILE, m_oArbreRenduINF2990->creerNoeud(ArbreRenduINF2990::NOM_PROJECTILE)));
	m_mapInstanceNoeud.insert(pair<string, NoeudAbstrait*>(ArbreRenduINF2990::NOM_STATIONSPATIALE, m_oArbreRenduINF2990->creerNoeud(ArbreRenduINF2990::NOM_STATIONSPATIALE)));
	m_mapInstanceNoeud.insert(pair<string, NoeudAbstrait*>(ArbreRenduINF2990::NOM_VAISSEAU, m_oArbreRenduINF2990->creerNoeud(ArbreRenduINF2990::NOM_VAISSEAU)));
	m_mapInstanceNoeud.insert(pair<string, NoeudAbstrait*>(ArbreRenduINF2990::NOM_ZONEJEU, m_oArbreRenduINF2990->creerNoeud(ArbreRenduINF2990::NOM_ZONEJEU)));
	m_mapInstanceNoeud.insert(pair<string, NoeudAbstrait*>(ArbreRenduINF2990::NOM_ZONEPASSAGE, m_oArbreRenduINF2990->creerNoeud(ArbreRenduINF2990::NOM_ZONEPASSAGE)));

	// On ajoute chaque noeud � l'arbre
	m_oArbreRenduINF2990->ajouter(m_mapInstanceNoeud[ArbreRenduINF2990::NOM_ASTEROIDE]);
	m_oArbreRenduINF2990->ajouter(m_mapInstanceNoeud[ArbreRenduINF2990::NOM_BARRIEREPROTECTRICE]);
	m_oArbreRenduINF2990->ajouter(m_mapInstanceNoeud[ArbreRenduINF2990::NOM_BONUSACCELERATEUR]);
	m_oArbreRenduINF2990->ajouter(m_mapInstanceNoeud[ArbreRenduINF2990::NOM_PORTAIL]);
	m_oArbreRenduINF2990->ajouter(m_mapInstanceNoeud[ArbreRenduINF2990::NOM_POSITIONDEPART]);
	m_oArbreRenduINF2990->ajouter(m_mapInstanceNoeud[ArbreRenduINF2990::NOM_PROJECTILE]);
	m_oArbreRenduINF2990->ajouter(m_mapInstanceNoeud[ArbreRenduINF2990::NOM_STATIONSPATIALE]);
	m_oArbreRenduINF2990->ajouter(m_mapInstanceNoeud[ArbreRenduINF2990::NOM_VAISSEAU]);
	m_oArbreRenduINF2990->ajouter(m_mapInstanceNoeud[ArbreRenduINF2990::NOM_ZONEJEU]);
	m_oArbreRenduINF2990->ajouter(m_mapInstanceNoeud[ArbreRenduINF2990::NOM_ZONEPASSAGE]);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurXmlTest::tearDown()
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
void VisiteurXmlTest::tearDown()
{
	delete m_oArbreRenduINF2990;
	typedef std::map<std::string, NoeudAbstrait*>::iterator it_type;
	for(it_type iterator = m_mapInstanceNoeud.begin(); iterator != m_mapInstanceNoeud.end(); iterator++) {
		// Lorsque l'arbre de rendu se fait d�tuire, il se fait vider de tous ses enfants
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurXmlTest::test_saveXML()
///
/// Cas de test: La sauvegarde d'un fichier xml est-elle fonctionelle.
/// Dans notre cas, le visiteur devrait s�rialiser les 10 noeuds que nous avons ajout� � l'arbre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurXmlTest::test_saveXML()
{
	VisiteurXml* visiteurXML = VisiteurXml::obtenirInstance();
	visiteurXML->creerFichXml(m_oArbreRenduINF2990, "VisiteurXmlTest.xml");
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurXmlTest::test_loadXML()
///
/// Cas de test: Peut-on reconstruire une arbre de rendu avec un fichier XML sauveard�.
/// Dans notre cas, on conna�t d�j� l'arbre, donc on peut v�rifier que tout les types de noeuds sont pr�sents et bien configur�s.
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurXmlTest::test_loadXML()
{
	m_oArbreRenduINF2990->vider();
	VisiteurXml* visiteurXML = VisiteurXml::obtenirInstance();
	visiteurXML->lireFichXml(m_oArbreRenduINF2990, "VisiteurXmlTest.xml");

	// � t-on pu reonstruire l'arbre de rendu exactement comme avant de l'avoir sauv�
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->obtenirNombreEnfants () == 9);

	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ASTEROIDE));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_BARRIEREPROTECTRICE));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_BONUSACCELERATEUR));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_PORTAIL));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_POSITIONDEPART));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_PROJECTILE));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_STATIONSPATIALE));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_VAISSEAU));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ZONEPASSAGE));

	// On v�rifie que les deux arbres sont identiques � l'arbres configur� lors de l'initialisation du test
	_VerifierNoeud(m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ASTEROIDE));
	_VerifierNoeud(m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_BARRIEREPROTECTRICE));
	_VerifierNoeud(m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_BONUSACCELERATEUR));
	_VerifierNoeud(m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_PORTAIL));
	_VerifierNoeud(m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_POSITIONDEPART));
	_VerifierNoeud(m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_PROJECTILE));
	_VerifierNoeud(m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_STATIONSPATIALE));
	_VerifierNoeud(m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_VAISSEAU));
	_VerifierNoeud(m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ZONEPASSAGE));
}

void  VisiteurXmlTest::_VerifierNoeud(NoeudAbstrait *noeud)
{
	CPPUNIT_ASSERT (noeud->getEchelle() == 1);
	CPPUNIT_ASSERT (noeud->getAngleRotation() == 0);
	CPPUNIT_ASSERT (noeud->estAffiche() == 1);
	if(noeud->obtenirType() == ArbreRenduINF2990::NOM_ZONEJEU) {
		CPPUNIT_ASSERT (!noeud->estSelectionnable());
	} else {
		CPPUNIT_ASSERT (noeud->estSelectionnable());
	}
	CPPUNIT_ASSERT (!noeud->estSelectionne());
	CPPUNIT_ASSERT (noeud->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT (noeud->obtenirPositionRelative()[0] == 0.0);
	CPPUNIT_ASSERT (noeud->obtenirPositionRelative()[1] == 0.0);
	CPPUNIT_ASSERT (noeud->obtenirPositionRelative()[2] == 0.0);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////