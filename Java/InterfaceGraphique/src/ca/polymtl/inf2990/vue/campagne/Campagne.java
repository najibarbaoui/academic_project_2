package ca.polymtl.inf2990.vue.campagne;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.KeyEvent;
import java.io.File;
import java.io.IOException;
import java.util.Vector;

import javax.swing.BorderFactory;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JMenuBar;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;
import javax.swing.border.Border;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Attr;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import ca.polymtl.inf2990.composants.Fenetre;
import ca.polymtl.inf2990.gestionnaires.GestionnaireDeVue;
import ca.polymtl.inf2990.gestionnaires.GestionnaireEtatAction;
import ca.polymtl.inf2990.gestionnaires.GestionnaireEvenement;
import ca.polymtl.inf2990.gestionnaires.GestionnaireDeVue.TypesVue;
import ca.polymtl.inf2990.vues.Vue;

public class Campagne extends Vue {
	GestionnaireDeVue gestionnaireDeVue;
	private JFrame fenetre_;
	
	private Vector<String> m_vecFilePath = new Vector<String>();
	private Vector<String> m_vecFilename = new Vector<String>();
	
	GestionnaireEtatAction gestionEtatAction;
	private JTextField userText_;
	private JButton m_buttonMenuPrincipal, m_buttonQuitter;
	private JRadioButton m_buttonSolo;
	private JRadioButton m_buttonCooperative;
	private JRadioButton m_bHumain;
	private JRadioButton m_bVirtuel;
	private Border m_borderChoixZoneJeu, m_borderTypePartie, borderJoueur_, m_borderValider;
	private ButtonGroup m_groupPartie, groupJoueur_;
	private JPanel m_panelPartieJoueur_, m_panelTypePartie, m_panelJoueur, m_panelValidate, m_panelTransit;
	
	private JButton m_buttonAdd, m_buttonRemove, m_buttonAcceptCampaign;
	private JPanel m_panelChoixZoneJeu, m_panelAjoutSupprime;
	private JComboBox m_comboBoxZoneJeu;
	
	public Campagne(Fenetre fenetre, GestionnaireEvenement gestionnaireDEvenement) {
		super(fenetre, gestionnaireDEvenement);
		typeVue = TypesVue.CAMPAGNE;
		titreFenetre = "Campagne - INF2990";
		largeurFenetre = 640;
		hauteurFenetre = 480;
		
		// 3.15.1.1 - Les valeurs inscrites correspondent aux valeurs utilisées lors de la dernière campagne
		LireConfigurationCampagne();
	}
	
	@Override
	public void setProprietesFenetre() {
		// Affecter le titre de la fenêtre et sa taille à l'affichage
		fenetrePrincipale.setTitle(this.getTitreFenetre());
		fenetrePrincipale.setSize(this.getLargeurFenetre(), this.getHauteurFenetre());
		
		// Définir une taille minimale sur la fenêtre (Dimensions pour garder la barre de proprietes et la barre d'outils visible)
		fenetrePrincipale.setResizable(false);
		gestionnaireEvenement.setResizeCanvas(false);

	}
	
	public void ActiverVue() {
		// Afficher le context OpenGL et activer la minuterie
	}

	public void DetruireVue() {
		// Désactiver la minuterie et masquer le context OpenGL
		//gestionnaireEvenement.deleteObserver(gestionEtatAction);
	}
	
	
	void CreerComboBox() {
		m_comboBoxZoneJeu = new javax.swing.JComboBox();
		m_comboBoxZoneJeu.setModel(new javax.swing.DefaultComboBoxModel(new String[] {}));
		m_comboBoxZoneJeu.setPreferredSize(new Dimension(280,30));
		m_comboBoxZoneJeu.setEditable(false);
		
	}
	
	void CreerBoutonAjouterZoneJeu() {
		m_buttonAdd = new JButton();
		m_buttonAdd.setText("Ajouter");
		m_buttonAdd.setActionCommand("Campagne_Ajouter");
		m_buttonAdd.addActionListener(gestionnaireEvenement);
		m_buttonAdd.setForeground(Color.BLACK);
	}
	
	void CreerBoutonSupprimerZoneJeu() {
		m_buttonRemove = new JButton();
		m_buttonRemove.setText("Supprimer");
		m_buttonRemove.setActionCommand("Campagne_Supprimer");
		m_buttonRemove.addActionListener(gestionnaireEvenement);
		m_buttonRemove.setForeground(Color.BLACK);
	}
	
	void CreerBoutonAccepterCampagne() {
		m_buttonAcceptCampaign = new JButton();
		m_buttonAcceptCampaign.setText("Démarrer la campagne?");
		m_buttonAcceptCampaign.setActionCommand("Campagne_Confirmation");
		m_buttonAcceptCampaign.addActionListener(gestionnaireEvenement);
		m_buttonAcceptCampaign.setForeground(Color.BLACK);
	}
	
	void CreerBorderChoixZoneJeu() {
		m_borderChoixZoneJeu = BorderFactory.createTitledBorder("Choix des zones de jeux (minimum de 2).");
		CreerComboBox();
		CreerBoutonAjouterZoneJeu();
		CreerBoutonSupprimerZoneJeu();
		CreerBoutonAccepterCampagne();
		
		m_panelChoixZoneJeu = new JPanel();
		m_panelChoixZoneJeu.setBorder(m_borderChoixZoneJeu);
		m_panelChoixZoneJeu.add(m_comboBoxZoneJeu);
		m_panelChoixZoneJeu.add(m_buttonAcceptCampaign).setPreferredSize(new Dimension(280,30));;
		m_panelChoixZoneJeu.add(m_buttonAdd);
		m_panelChoixZoneJeu.add(m_buttonRemove);
	}
	
	void CreerBorderTypePartie() {
		m_borderTypePartie = BorderFactory.createTitledBorder("Type de la partie");
		m_buttonSolo = new JRadioButton("Solo", true);
		m_buttonCooperative = new JRadioButton("Coopérative", false);
		
		// Keyboard shortcuts
		m_buttonSolo.setMnemonic(KeyEvent.VK_S);
		m_buttonCooperative.setMnemonic(KeyEvent.VK_C);
		
		// Required actions
		m_buttonSolo.setActionCommand("CampSeul");
		m_buttonSolo.addActionListener(gestionnaireEvenement);
		
		m_buttonCooperative.setActionCommand("Coop_Campagne");
		m_buttonCooperative.addActionListener(gestionnaireEvenement);
		
		m_groupPartie = new ButtonGroup();
		m_groupPartie.add(m_buttonSolo);
		m_groupPartie.add(m_buttonCooperative);
	
		m_panelTypePartie = new JPanel();
		m_panelTypePartie.setBorder(m_borderTypePartie);
		m_panelTypePartie.add(m_buttonSolo);
		m_panelTypePartie.add(m_buttonCooperative);
	}
	
	void CreerBorderTypeJoueur() {
		borderJoueur_ = BorderFactory.createTitledBorder("Type du deuxième joueur");
		m_bHumain = new JRadioButton("Humain", true);
		m_bVirtuel = new JRadioButton("Virtuel", false);
		m_bHumain.setEnabled(false);
		m_bVirtuel.setEnabled(false);
		
		// Keyboard shortcuts
		m_bHumain.setMnemonic(KeyEvent.VK_H);
		m_bVirtuel.setMnemonic(KeyEvent.VK_V);
		
		// Required actions
		m_bHumain.setActionCommand("Humain_Campagne");
		m_bHumain.addActionListener(gestionnaireEvenement);
		
		m_bVirtuel.setActionCommand("Virtuel_Campagne");
		m_bVirtuel.addActionListener(gestionnaireEvenement);
		
		groupJoueur_ = new ButtonGroup();
		groupJoueur_.add(m_bHumain);
		groupJoueur_.add(m_bVirtuel);
		
		m_panelJoueur = new JPanel();
		m_panelJoueur.setBorder(borderJoueur_);
		m_panelJoueur.add(m_bHumain);
		m_panelJoueur.add(m_bVirtuel);
	}
	
	void CreerBoutonMenuPrincipal() {
		m_borderValider = BorderFactory.createTitledBorder("Valider pour commencer le jeu");
		
		m_buttonMenuPrincipal = new JButton("Retour au menu principal");
		m_buttonMenuPrincipal.setPreferredSize(new Dimension(280,30));
		m_buttonMenuPrincipal.setActionCommand("Changer vue: menu");
		m_buttonMenuPrincipal.addActionListener(gestionnaireEvenement);
		
		CreerBoutonQuitter();
		
		m_panelValidate = new JPanel();
		m_panelValidate.setLayout(new FlowLayout());
		m_panelValidate.add(m_buttonMenuPrincipal);
		m_panelValidate.add(m_buttonQuitter);
		m_panelValidate.setBorder(m_borderValider);
	}
	
	void CreerBoutonQuitter() {
		m_buttonQuitter = new JButton("Quitter");
		m_buttonQuitter.setPreferredSize(new Dimension(280,30));
		m_buttonQuitter.setActionCommand("Quitter");
		m_buttonQuitter.addActionListener(gestionnaireEvenement);
	}
	
	@Override
	public void ChargerComposants() {
		fenetrePrincipale.add(m_panelPartieJoueur_, BorderLayout.PAGE_START);
		fenetrePrincipale.add(m_panelAjoutSupprime, BorderLayout.CENTER);
		fenetrePrincipale.add(m_panelTransit, BorderLayout.PAGE_END);
	}
	
	@Override
	protected void CreerComposants() {
		CreerBorderTypePartie();
		CreerBorderTypeJoueur();
		m_panelPartieJoueur_ = new JPanel();
		m_panelPartieJoueur_.setLayout(new GridLayout(1,2));
		m_panelPartieJoueur_.add(m_panelTypePartie);
		m_panelPartieJoueur_.add(m_panelJoueur);
		listeComposants.add(m_panelPartieJoueur_);
		
		CreerBorderChoixZoneJeu();
		m_panelAjoutSupprime = new JPanel();
		m_panelAjoutSupprime.setLayout(new GridLayout(2,1));
		m_panelAjoutSupprime.add(m_panelChoixZoneJeu);
		listeComposants.add(m_panelAjoutSupprime);
		
		CreerBoutonMenuPrincipal();
		m_panelTransit = new JPanel();
		m_panelTransit.setLayout(new GridLayout(2,1));
		m_panelTransit.add(m_panelValidate);
		listeComposants.add(m_panelTransit);
	}
	
	public void AjouterZoneJeu(String strFileName, String strAbsPath) {
		m_comboBoxZoneJeu.addItem(strFileName);	
		m_vecFilename.add(strFileName);
		m_vecFilePath.add(strAbsPath);
		m_comboBoxZoneJeu.setSelectedIndex(m_comboBoxZoneJeu.getItemCount() - 1);
	}
	
	public void SupprimerZoneJeu(){
		if(m_comboBoxZoneJeu.getItemCount()>=3){
			String strFilename = m_comboBoxZoneJeu.getItemAt(m_comboBoxZoneJeu.getSelectedIndex()).toString();
			int index = m_vecFilename.indexOf(strFilename);
			if(index != -1) {
				m_vecFilename.removeElementAt(index);
				m_vecFilePath.removeElementAt(index);
				m_comboBoxZoneJeu.removeItemAt(m_comboBoxZoneJeu.getSelectedIndex());
			}
		}else{
			JOptionPane.showMessageDialog(fenetre_,
				    "Minimum 2 parties.",
				    "Nombre de parties insuffisant.",
				    JOptionPane.PLAIN_MESSAGE);
		}
		
	}
	
	public void LireConfigurationCampagne() {
		try {
			String strCanonicalPath = new File(".").getCanonicalPath();
			String strConfigPath = strCanonicalPath + "\\config\\campagne.xml";
			File fXmlFile = new File(strConfigPath);
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
			org.w3c.dom.Document doc = dBuilder.parse(fXmlFile);
			doc.getDocumentElement().normalize();
			
			Node type_partie = doc.getElementsByTagName("TypePartie").item(0);
			Node type_joueur = doc.getElementsByTagName("TypeJoueur").item(0);
			
			boolean bSolo, bCoop, bHumainSelected, bVirutelSelected, bHumainEnabled, bVirutelEnabled;
			bSolo = Boolean.parseBoolean(type_partie.getAttributes().getNamedItem("Solo").getNodeValue());
			bCoop = Boolean.parseBoolean(type_partie.getAttributes().getNamedItem("Coop").getNodeValue());
			bHumainSelected = Boolean.parseBoolean(type_joueur.getAttributes().getNamedItem("HumainSelected").getNodeValue());
			bVirutelSelected = Boolean.parseBoolean(type_joueur.getAttributes().getNamedItem("VirtualSelected").getNodeValue());
			bHumainEnabled = Boolean.parseBoolean(type_joueur.getAttributes().getNamedItem("HumainEnabled").getNodeValue());
			bVirutelEnabled = Boolean.parseBoolean(type_joueur.getAttributes().getNamedItem("VirtualEnabled").getNodeValue());
			
			m_buttonSolo.setSelected(bSolo);
			m_buttonCooperative.setSelected(bCoop);
			m_bHumain.setSelected(bHumainSelected);
			m_bVirtuel.setSelected(bVirutelSelected);
			m_bHumain.setEnabled(bHumainEnabled);
			m_bVirtuel.setEnabled(bVirutelEnabled);
			
			NodeList nodeList = doc.getElementsByTagName("Zone");
			for (int i = 0; i < nodeList.getLength(); i++) {
				Node n = nodeList.item(i);
				if (n != null) {
					// Check if file exist
					String strFilename = n.getAttributes().getNamedItem("Filename").getNodeValue();	
					String strFilepath = strCanonicalPath + "\\zones\\" + strFilename;
					File f = new File(strFilepath);
					if(f.exists()) {		
						AjouterZoneJeu(strFilename, strFilepath);
					} else {
						String strZoneParDefault = "ZoneParDefaut.xml";
						String strZoneParDefaultFolder = strCanonicalPath + "\\" +"ZoneParDefaut.xml";
						AjouterZoneJeu(strZoneParDefault, strZoneParDefaultFolder);
					}
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	} 
	
	public void SauvegarderConfigurationCampagne() {
		try {
			DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
		
			// root elements
			org.w3c.dom.Document doc = docBuilder.newDocument();
			org.w3c.dom.Element rootElement = doc.createElement("Campagne");
			doc.appendChild(rootElement);
			
			org.w3c.dom.Element type_partie = doc.createElement("TypePartie");
			org.w3c.dom.Element type_joueur = doc.createElement("TypeJoueur");
			
			type_partie.setAttribute("Solo", String.valueOf(m_buttonSolo.isSelected()));
			type_partie.setAttribute("Coop", String.valueOf(m_buttonCooperative.isSelected()));

			type_joueur.setAttribute("HumainSelected", String.valueOf(m_bHumain.isSelected()));
			type_joueur.setAttribute("VirtualSelected", String.valueOf(m_bVirtuel.isSelected()));
			
			type_joueur.setAttribute("HumainEnabled", String.valueOf(m_bHumain.isEnabled()));
			type_joueur.setAttribute("VirtualEnabled", String.valueOf(m_bVirtuel.isEnabled()));
			
			rootElement.appendChild(type_partie);	
			rootElement.appendChild(type_joueur);
			
			for(int i = 0; i < m_comboBoxZoneJeu.getItemCount(); ++i) {
				org.w3c.dom.Element zone = doc.createElement("Zone");
				
				zone.setAttribute("Filename", m_vecFilename.elementAt(i));
				zone.setAttribute("AbsFilePath", m_vecFilePath.elementAt(i));
				
				rootElement.appendChild(zone);	
			}
			
			// write the content into xml file
			TransformerFactory transformerFactory = TransformerFactory.newInstance();
			Transformer transformer = null;
			try {
				transformer = transformerFactory.newTransformer();
			} catch (TransformerConfigurationException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			DOMSource source = new DOMSource(doc);
			String strCanonicalPath;
			try {
				strCanonicalPath = new File(".").getCanonicalPath();
				String strConfigPath = strCanonicalPath + "\\config\\campagne.xml";
				StreamResult result = new StreamResult(new File(strConfigPath));
				try {
					transformer.transform(source, result);
				} catch (TransformerException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		} catch (ParserConfigurationException pce) {
			pce.printStackTrace();
		}
	}
	
	void ValidateZoneJeu() {
		
	}
	
	public void LaunchGame() {
		for(int i = 0; i < m_vecFilename.size(); ++i) {
		}
	}
	
	public JMenuBar construireMenu() {
		return null;
	}
	
	public JRadioButton getBoutonSolo(){
		return m_buttonSolo;
	}
	
	public JRadioButton getBoutonCoop(){
		return m_buttonCooperative;
	}
	
	public JRadioButton getBoutonHumain(){
		return m_bHumain;
	}
	
	public JRadioButton getBoutonVirtuel(){
		return m_bVirtuel;
	}
	
	public ButtonGroup getBoutonGroupJoueur(){
		return groupJoueur_;
	}
	
	public Vector<String> GetFilename() {
		return m_vecFilename;
	}
	
	public Vector<String> GetFilepath() {
		return m_vecFilePath;
	}
}
