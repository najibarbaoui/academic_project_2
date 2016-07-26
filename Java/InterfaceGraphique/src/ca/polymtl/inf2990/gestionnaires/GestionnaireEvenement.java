package ca.polymtl.inf2990.gestionnaires;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.FlowLayout;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.Toolkit;
import java.io.File;
import java.util.Observable;
import java.util.Vector;
import java.util.concurrent.CancellationException;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

import javax.swing.BoxLayout;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.Timer;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import ca.polymtl.inf2990.composants.FenetreProprietes;
import ca.polymtl.inf2990.cpp.FacadeCpp;
import ca.polymtl.inf2990.gestionnaires.GestionnaireDeVue.TypesVue;
import ca.polymtl.inf2990.modele.ProprietesNoeud;
import ca.polymtl.inf2990.vue.editeur.EditeurVue;
import ca.polymtl.inf2990.vue.jeu.ModeJeuVue;
import ca.polymtl.inf2990.vue.modeScoreVue.ModeScoreVue;
import ca.polymtl.inf2990.vue.modetest.ModeTestVue;
import ca.polymtl.inf2990.vue.partie_rapide.PartieRapideVue;
import ca.polymtl.inf2990.vue.campagne.Campagne;


public class GestionnaireEvenement extends Observable implements
		ActionListener, MouseListener, MouseMotionListener, MouseWheelListener,
		ComponentListener, KeyListener {
	// Référence sur le gestionnaire de vue
	private GestionnaireDeVue gestionnaireDeVue;
	//private ModeScoreVue jdialog;
	String cheminFichierModeJeu;
	JPanel menuPanel = new JPanel();
	static JFrame frame;
	int IndexCampagne = 0;
	
	private int clickX;
	private int clickY;
	private boolean resizeCanvas = false;
	private boolean etatDeCanavasJeu = false;
	private boolean etatDeCanavasEditeur = false;
	//private boolean etatDeCanavasModeTest = false;
	private int etatActionCourant;
	private ProprietesNoeud noeudSelectionne = null;
	private String fichierSauvegardeParDefaut;
	private TraitementEvenement traitement;
	private boolean estTerminer = false;
	private enum EtatModele {
		MENU, EDITEUR, JEU, ETATCONFIGURATION, MODETEST, PARTIERAPIDE, CAMPAGNE
	};

	private enum ClavierDirection {
		UP, DOWN, LEFT, RIGHT
	};

	public GestionnaireEvenement(GestionnaireDeVue gestionnaireDeVue) {
		this.gestionnaireDeVue = gestionnaireDeVue;
		traitement = new TraitementEvenement();
		fichierSauvegardeParDefaut = System.getProperty("user.dir")
				+ "\\zones\\ZoneParDefaut.xml";
	}

	public void UpdateVue() {
		int etat = FacadeCpp.fctC_obtenirEtat();
		if (etat == EtatModele.EDITEUR.ordinal()) {
			// Obtenir etat action courant
			etatActionCourant = FacadeCpp.fctC_obtenirEtatActionId();

			// Obtenir les proprietes du seul noeud sélectionné
			noeudSelectionne = FacadeCpp.fctC_obtenirSeulNoeudSelectionne();

			String nomFichierSauvegarde = FacadeCpp
					.fctC_obtenirNomFichierSauvegarde();

			gestionnaireDeVue.getFenetre().setTitle(nomFichierSauvegarde);

			// Notifier de l'état courant pour la barre d'outils
			this.setChanged();
			this.notifyObservers();
		}
	}

	public void setResizeCanvas(boolean resizeCanvas) {
		this.resizeCanvas = resizeCanvas;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		String commande = e.getActionCommand();
		if (commande == "Quitter") {
			System.exit(0);
		} else if (commande.contains("Nouveau")) {
			// FacadeCpp.fctC_
		} else if (commande.contains("Changer vue")) {
			
			if (commande.contains("menu")) {
				//
				etatDeCanavasEditeur = false;
				FacadeCpp.fctC_changerEtat(FacadeCpp.EtatModele.MENU.ordinal());
				gestionnaireDeVue.ChangerVue(TypesVue.MENU);
				
			} else if (commande.contains("editeur")) {
				etatDeCanavasEditeur = true;
				FacadeCpp.fctC_changerEtat(FacadeCpp.EtatModele.EDITEUR
						.ordinal());
				gestionnaireDeVue.ChangerVue(TypesVue.EDITEUR);
			} else if (commande.contains("configuration")) {
				FacadeCpp.fctC_changerEtat(FacadeCpp.EtatModele.CONFIGURATION
						.ordinal());
				gestionnaireDeVue.ChangerVue(TypesVue.CONFIGURATION);
			} else if (commande.contains("Mode test")) {
				FacadeCpp.fctC_changerEtat(FacadeCpp.EtatModele.MODETEST.ordinal());
				gestionnaireDeVue.ChangerVue(TypesVue.MODETEST);
				FacadeCpp.fctC_buttonPressed("start");
				gestionnaireDeVue.getFenetre().getJMenuBar().setVisible(false);
			} else if (commande.contains("partie rapide")) {
				FacadeCpp.fctC_changerEtat(FacadeCpp.EtatModele.PARTIERAPIDE.ordinal());
				gestionnaireDeVue.ChangerVue(TypesVue.PARTIERAPIDE);
			} else if(commande.contains("campagne")) {
				gestionnaireDeVue.getFenetre().setVisible(false);
				FacadeCpp.fctC_changerEtat(FacadeCpp.EtatModele.CAMPAGNE.ordinal());
				gestionnaireDeVue.ChangerVue(TypesVue.CAMPAGNE);
				gestionnaireDeVue.getFenetre().setVisible(true);
			} else if (commande.contains("jeu")) {
				etatDeCanavasJeu = true;
				//verifier la partie à jouer solo ou cooperative
				if(((PartieRapideVue)gestionnaireDeVue.getCurrentVue()).getBoutonCoop().isSelected())
					if(((PartieRapideVue)gestionnaireDeVue.getCurrentVue()).getBoutonHumain().isSelected())
						FacadeCpp.fctC_buttonPressed("Humain");
					else
						FacadeCpp.fctC_buttonPressed("Virtuel");
				else
					FacadeCpp.fctC_buttonPressed("Solo");
				
				//changer etat mode jeu 
				FacadeCpp.fctC_changerEtat(FacadeCpp.EtatModele.JEU.ordinal());
				gestionnaireDeVue.ChangerVue(TypesVue.JEU);
				gestionnaireDeVue.getFenetre().getJMenuBar().setVisible(false);
				try {
					
					if (!FacadeCpp.fctC_ouvrirFichier(cheminFichierModeJeu)) {
						// S'il y a eu une erreur
						JOptionPane.showMessageDialog(
								gestionnaireDeVue.getFenetre(),
								"Le fichier " + cheminFichierModeJeu
										+ " n'a pas pu être ouvert.",
								"Erreur d'ouverture du fichier.",
								JOptionPane.ERROR_MESSAGE);
					}
				} catch (CancellationException exception) {
					// L'action a été annulé
				}
				FacadeCpp.fctC_buttonPressed("start");
			}
		} else if (commande.contains("Orthographique")) {
			FacadeCpp.fctC_activerVueOrthogonale();
		} else if (commande.contains("Orbite")) {
			FacadeCpp.fctC_activerVuePerspective();
		}else if (commande.contains("Solo")) {
			((PartieRapideVue)gestionnaireDeVue.getCurrentVue()).getBoutonGroupJoueur().clearSelection();
			((PartieRapideVue)gestionnaireDeVue.getCurrentVue()).getBoutonHumain().setEnabled(false);
			((PartieRapideVue)gestionnaireDeVue.getCurrentVue()).getBoutonVirtuel().setEnabled(false);
		}else if (commande.contains("Cooperative")) {
			((PartieRapideVue)gestionnaireDeVue.getCurrentVue()).getBoutonHumain().setEnabled(true);
			((PartieRapideVue)gestionnaireDeVue.getCurrentVue()).getBoutonVirtuel().setEnabled(true);
			((PartieRapideVue)gestionnaireDeVue.getCurrentVue()).getBoutonHumain().setSelected(true);
		} else if(commande.contains("CampSeul")) {
			((Campagne)gestionnaireDeVue.getCurrentVue()).getBoutonHumain().setEnabled(false);
			((Campagne)gestionnaireDeVue.getCurrentVue()).getBoutonVirtuel().setEnabled(false);
		} else if(commande.contains("Coop_Campagne")) {
			((Campagne)gestionnaireDeVue.getCurrentVue()).getBoutonHumain().setEnabled(true);
			((Campagne)gestionnaireDeVue.getCurrentVue()).getBoutonVirtuel().setEnabled(true);
		} else if (commande.contains("Humain")) {
			//rien a faire
		}else if (commande.contains("Virtuel")) {
			//rien n a faire
		}else if (commande.contains("Parcourir")) {
			cheminFichierModeJeu = selectFile();
			((PartieRapideVue)gestionnaireDeVue.getCurrentVue()).setNomFichier(cheminFichierModeJeu);
			((PartieRapideVue)gestionnaireDeVue.getCurrentVue()).getBoutonValider().setEnabled(true);
			((PartieRapideVue)gestionnaireDeVue.getCurrentVue()).getJTextField().setEditable(false);
		}else if (commande.contains("Rejouer")) {
			traitement.keyPressed(8);
			((ModeJeuVue)gestionnaireDeVue.getCurrentVue()).getJdialog().setVisible(false);
		} else if(commande.contains("Campagne_Ajouter")) {
			File path = selectFileNoRestriction();
			if(path != null) {
				((Campagne)gestionnaireDeVue.getCurrentVue()).AjouterZoneJeu(path.getName(), path.getAbsolutePath());
			}
		} else if(commande.contains("Campagne_Supprimer")) {
			((Campagne)gestionnaireDeVue.getCurrentVue()).SupprimerZoneJeu();
		} else if(commande.contains("Campagne_Confirmation")) {
				((Campagne)gestionnaireDeVue.getCurrentVue()).SauvegarderConfigurationCampagne();
				if(FacadeCpp.fctC_obtenirEtat() == EtatModele.CAMPAGNE.ordinal()) {
					//((Campagne)gestionnaireDeVue.getCurrentVue()).LaunchGame();
					Vector<String> vecFilePath = ((Campagne)gestionnaireDeVue.getCurrentVue()).GetFilepath();
					Vector<String> vecFilename = ((Campagne)gestionnaireDeVue.getCurrentVue()).GetFilename();;
					if(IndexCampagne < vecFilePath.size()) {
						String strFilename = vecFilename.elementAt(IndexCampagne);
						String strFilepath = vecFilePath.elementAt(IndexCampagne);
						final String strFullText = LireConfigurationZoneJeu(strFilename);
						
						JFrame f = new JFrame();
						final JDialog dialog = new JDialog(f, "Démarrer Campagne", true);

						//Must schedule the close before the dialog becomes visible
						ScheduledExecutorService s = Executors.newSingleThreadScheduledExecutor();     
						s.schedule(new Runnable() {
						    public void run() {
						        dialog.setVisible(false); //should be invoked on the EDT
						        dialog.dispose();
						    }
						}, 5, TimeUnit.SECONDS);

						dialog.pack();
						dialog.setLocationRelativeTo(null);
						dialog.setSize(320, 200);
						
						JLabel label = new JLabel(strFullText);
				    	label.setHorizontalAlignment(SwingConstants.CENTER);
				    	dialog.add(label);
				    	dialog.setVisible(true); // if modal, application will pause here
						
				    	etatDeCanavasJeu = true;
						//verifier la partie à jouer solo ou cooperative
						if(((Campagne)gestionnaireDeVue.getCurrentVue()).getBoutonCoop().isSelected())
							if(((Campagne)gestionnaireDeVue.getCurrentVue()).getBoutonHumain().isSelected())
								FacadeCpp.fctC_buttonPressed("Humain");
							else
								FacadeCpp.fctC_buttonPressed("Virtuel");
						else
							FacadeCpp.fctC_buttonPressed("Solo");
						
						//changer etat mode jeu
						FacadeCpp.fctC_changerEtat(FacadeCpp.EtatModele.JEU.ordinal());
						gestionnaireDeVue.ChangerVue(TypesVue.JEU);
						gestionnaireDeVue.getFenetre().getJMenuBar().setVisible(false);
						try {
							
							if (!FacadeCpp.fctC_ouvrirFichier(strFilepath)) {
								// S'il y a eu une erreur
								JOptionPane.showMessageDialog(
										gestionnaireDeVue.getFenetre(),
										"Le fichier " + cheminFichierModeJeu
												+ " n'a pas pu être ouvert.",
										"Erreur d'ouverture du fichier.",
										JOptionPane.ERROR_MESSAGE);
							}
						} catch (CancellationException exception) {
							// L'action a été annulé
						}
						FacadeCpp.fctC_buttonPressed("start");
						
						++IndexCampagne;
					}
				}		
		} else if (commande.contains("Ouvrir")) {
			String completePath = selectFile();
			
			try {
				
				if (!FacadeCpp.fctC_ouvrirFichier(completePath)) {
					// S'il y a eu une erreur
					JOptionPane.showMessageDialog(
							gestionnaireDeVue.getFenetre(),
							"Le fichier " + completePath
									+ " n'a pas pu être ouvert.",
							"Erreur d'ouverture du fichier.",
							JOptionPane.ERROR_MESSAGE);
				}
			} catch (CancellationException exception) {
				// L'action a été annulé
			}
		} else if (commande.contains("Enregistrer sous")) {
			FacadeCpp.fctC_buttonPressed("Escape");
			try {
				String completePath = selectFile();

				if (completePath.equals(fichierSauvegardeParDefaut)) {
					JOptionPane
							.showMessageDialog(
									gestionnaireDeVue.getFenetre(),
									"Le fichier "
											+ completePath
											+ " ne peut être écrasé. Choisissez un autre fichier.",
									"Erreur d'ouverture du fichier.",
									JOptionPane.ERROR_MESSAGE);
				} else if (!FacadeCpp.fctC_sauvegarderFichier(completePath)) {
					// S'il y a eu une erreur
					JOptionPane.showMessageDialog(
							gestionnaireDeVue.getFenetre(), "Le fichier "
									+ completePath
									+ " n'a pas pu être enregistré.",
							"Erreur d'enregistrement du fichier.",
							JOptionPane.ERROR_MESSAGE);
				}
			} catch (CancellationException exception) {
				// L'action a été annulé
			}
		} else if (commande.contains("Enregistrer")) {
			FacadeCpp.fctC_buttonPressed("Escape");
			if (FacadeCpp.fctC_fichierSauvegardeEstDefini()) {
				FacadeCpp.fctC_sauvegarderFichier("");
			} else {
				try {
					String completePath = selectFile();

					if (completePath.equals(fichierSauvegardeParDefaut)) {
						JOptionPane
								.showMessageDialog(
										gestionnaireDeVue.getFenetre(),
										"Le fichier "
												+ completePath
												+ " ne peut être écrasé. Choisissez un autre fichier.",
										"Erreur d'ouverture du fichier.",
										JOptionPane.ERROR_MESSAGE);
					} else if (!FacadeCpp.fctC_sauvegarderFichier(completePath)) {
						// S'il y a eu une erreur
						JOptionPane.showMessageDialog(
								gestionnaireDeVue.getFenetre(), "Le fichier "
										+ completePath
										+ " n'a pas pu être enregistré.",
								"Erreur d'enregistrement du fichier.",
								JOptionPane.ERROR_MESSAGE);
					}
				} catch (CancellationException exception) {
					// L'action a été annulé
				}
			}
			
		} else if (commande.contains("Propriétés")) {
			FenetreProprietes fp = new FenetreProprietes();
			fp.setVisible(true);
			 
		} else if (commande.contains("Action: ")) {
			commande = commande.substring("Action: ".length());

			// Envoyer commande
			FacadeCpp.fctC_buttonPressed(commande);
		} else if (commande.contains("Supprimer")) {
			FacadeCpp.fctC_buttonPressed(commande);
		}

		this.UpdateVue();
	}

	@Override
	public void mouseWheelMoved(MouseWheelEvent e) {
		if (FacadeCpp.fctC_obtenirEtat() == EtatModele.EDITEUR.ordinal()) {
			int notches = e.getWheelRotation();
			if (notches < 0) {
				FacadeCpp.fctC_zoomIn();
			} else {
				FacadeCpp.fctC_zoomOut();
			}
		}
	}

	@Override
	public void mousePressed(MouseEvent e) {
		clickX = e.getX();
		clickY = e.getY();
		boolean ctrlPressed = (e.getModifiersEx() & InputEvent.CTRL_DOWN_MASK) == InputEvent.CTRL_DOWN_MASK;
		boolean altPressed = (e.getModifiersEx() & InputEvent.ALT_DOWN_MASK) == InputEvent.ALT_DOWN_MASK;

		FacadeCpp.fctC_mousePressed(clickX, clickY, e.getButton(), ctrlPressed,
				altPressed);
	}

	@Override
	public void mouseDragged(MouseEvent e) {
		int x = e.getX();
		int y = e.getY();
		boolean ctrlPressed = (e.getModifiersEx() & InputEvent.CTRL_DOWN_MASK) == InputEvent.CTRL_DOWN_MASK;
		boolean altPressed = (e.getModifiersEx() & InputEvent.ALT_DOWN_MASK) == InputEvent.ALT_DOWN_MASK;

		int dx = clickX - x;
		int dy = clickY - y;

		FacadeCpp.fctC_mouseDragged(x, y, dx, dy, ctrlPressed, altPressed);
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		int x = e.getX();
		int y = e.getY();
		boolean ctrlPressed = (e.getModifiersEx() & InputEvent.CTRL_DOWN_MASK) == InputEvent.CTRL_DOWN_MASK;
		boolean altPressed = (e.getModifiersEx() & InputEvent.ALT_DOWN_MASK) == InputEvent.ALT_DOWN_MASK;

		int dx = clickX - x;
		int dy = clickY - y;

		// Vérifie si on a affaire à un click ou à un drag
		if (Math.abs(dx) > 3 && Math.abs(dy) > 3) {
			FacadeCpp.fctC_mouseReleased(x, y, e.getButton(), ctrlPressed,
					altPressed);
		} else {
			FacadeCpp.fctC_mouseClicked(clickX, clickY, e.getButton(),
					ctrlPressed, altPressed);
		}

		UpdateVue();
	}

	@Override
	public void mouseMoved(MouseEvent e) {
		int x = e.getX();
		int y = e.getY();
		boolean ctrlPressed = (e.getModifiersEx() & InputEvent.CTRL_DOWN_MASK) == InputEvent.CTRL_DOWN_MASK;
		boolean altPressed = (e.getModifiersEx() & InputEvent.ALT_DOWN_MASK) == InputEvent.ALT_DOWN_MASK;

		FacadeCpp.fctC_mouseMoved(x, y, ctrlPressed, altPressed);
	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void componentHidden(ComponentEvent arg0) {
		// TODO Auto-generated method stub

	}

	@Override
	public void componentMoved(ComponentEvent arg0) {
		// TODO Auto-generated method stub

	}

	@Override
	public void componentResized(ComponentEvent arg0) {
		// resizeCanvas est vrai seulement si la vue est de type EditeurVue
		// TODO changer lorsqu'on ajoutera la vue de type JeuVue
		if (resizeCanvas && etatDeCanavasEditeur) {
			int newWidth = ((EditeurVue) gestionnaireDeVue.getCurrentVue())
					.getCanvasSize().width;
			int newHeight = ((EditeurVue) gestionnaireDeVue.getCurrentVue())
					.getCanvasSize().height;

			FacadeCpp.fctC_redimensionnerFenetre(newWidth, newHeight);
			etatDeCanavasEditeur = false;
		}
		if (resizeCanvas && etatDeCanavasJeu) {
			int newWidth = ((ModeJeuVue) gestionnaireDeVue.getCurrentVue())
					.getCanvasSize().width;
			int newHeight = ((ModeJeuVue) gestionnaireDeVue.getCurrentVue())
					.getCanvasSize().height;

			System.out.print("Java canvas size ");
			System.out.print(newWidth);
			System.out.print(" ");
			System.out.println(newHeight);

			FacadeCpp.fctC_redimensionnerFenetre(newWidth, newHeight);
			etatDeCanavasJeu = false;
		}
		
	}

	@Override
	public void componentShown(ComponentEvent arg0) {
		// TODO Auto-generated method stub

	}

	@Override
	public void keyTyped(KeyEvent e) {
	}

	@Override
	public void keyPressed(KeyEvent e) {
		int etat = FacadeCpp.fctC_obtenirEtat();
		if (etat == EtatModele.MODETEST.ordinal() || etat == EtatModele.JEU.ordinal() || etat == EtatModele.PARTIERAPIDE.ordinal()) {
			int keyCode = e.getKeyCode(); 
			traitement.keyPressed(keyCode);
		}
		//UpdateVue();
	}

	@Override
	public void keyReleased(KeyEvent e) {
		int etat = FacadeCpp.fctC_obtenirEtat();
		if (etat == EtatModele.MODETEST.ordinal() || etat == EtatModele.JEU.ordinal() || etat == EtatModele.PARTIERAPIDE.ordinal()){
			int keyCode = e.getKeyCode();
			traitement.keyReleased(keyCode);
		} 
		{
			// Capturer l'évenement lorsque la touche escape est appuyée
			switch (e.getKeyCode()) {
			case KeyEvent.VK_ESCAPE:
				// Retourner l'action par défaut
				//FacadeCpp.fctC_buttonPressed("Escape");
				if(etat == EtatModele.JEU.ordinal() ||
						etat == EtatModele.MODETEST.ordinal() || etat == EtatModele.PARTIERAPIDE.ordinal())
				gestionnaireDeVue.getFenetre().getJMenuBar().setVisible(
						!gestionnaireDeVue.getFenetre().getJMenuBar().isVisible());
				break;
			case KeyEvent.VK_DELETE:
				// Supprimer les noeuds sélectionnés
				FacadeCpp.fctC_buttonPressed("Supprimer");
				break;
			case 107:
			case '+':
				if (FacadeCpp.fctC_obtenirEtat() == EtatModele.EDITEUR
						.ordinal()) {
					FacadeCpp.fctC_zoomIn();
				}
				break;
			case 61:
				// Shift et égal donne un +
				boolean shiftPressed = (e.getModifiersEx() & InputEvent.SHIFT_DOWN_MASK) == InputEvent.SHIFT_DOWN_MASK;
				if (shiftPressed) {
					if (FacadeCpp.fctC_obtenirEtat() == EtatModele.EDITEUR
							.ordinal()) {
						FacadeCpp.fctC_zoomIn();
					}
				}
				break;
			case 109:
			case '-':
				if (FacadeCpp.fctC_obtenirEtat() == EtatModele.EDITEUR
						.ordinal()) {
					FacadeCpp.fctC_zoomOut();
				}
				break;
			case KeyEvent.VK_UP:
				if (FacadeCpp.fctC_obtenirEtat() == EtatModele.EDITEUR
						.ordinal()) {
					FacadeCpp.fctC_move(ClavierDirection.UP.ordinal());
				}
				break;
			case KeyEvent.VK_DOWN:
				if (FacadeCpp.fctC_obtenirEtat() == EtatModele.EDITEUR
						.ordinal()) {
					FacadeCpp.fctC_move(ClavierDirection.DOWN.ordinal());
				}
				break;
			case KeyEvent.VK_LEFT:
				if (FacadeCpp.fctC_obtenirEtat() == EtatModele.EDITEUR
						.ordinal()) {
					FacadeCpp.fctC_move(ClavierDirection.LEFT.ordinal());
				}
				break;
			case KeyEvent.VK_RIGHT:
				if (FacadeCpp.fctC_obtenirEtat() == EtatModele.EDITEUR
						.ordinal()) {
					FacadeCpp.fctC_move(ClavierDirection.RIGHT.ordinal());
				}
				break;
			case KeyEvent.VK_D:
				FacadeCpp.fctC_buttonPressed("Déplacement");
				break;
			case KeyEvent.VK_S:
				FacadeCpp.fctC_buttonPressed("Sélection");
				break;
			case KeyEvent.VK_R:
				FacadeCpp.fctC_buttonPressed("Rotation");
				break;
			case KeyEvent.VK_E:
				FacadeCpp.fctC_buttonPressed("Mise à l'échelle");
				break;
			case KeyEvent.VK_C:
				FacadeCpp.fctC_buttonPressed("Duplication");
				break;
			case KeyEvent.VK_Z:
				FacadeCpp.fctC_buttonPressed("Zoom");
				break;
			case KeyEvent.VK_M:
				FacadeCpp
						.fctC_buttonPressed("Ajouter Noeud: barriereProtectrice");
				break;
			case KeyEvent.VK_P:
				FacadeCpp.fctC_buttonPressed("Ajouter Noeud: portail");
				break;
			case KeyEvent.VK_B:
				FacadeCpp
						.fctC_buttonPressed("Ajouter Noeud: bonusAccelerateur");
				break;
			case KeyEvent.VK_G:
				FacadeCpp.fctC_buttonPressed("Ajouter Noeud: stationSpatiale");
				break;
			}
		}

		UpdateVue();
	}

	public int getEtatActionCourant() {
		return etatActionCourant;
	}

	public ProprietesNoeud getSeulNoeudSelectionne() {
		return noeudSelectionne;
	}

	public void UpdateProprietesNoeudSelectionne(int indexPropriete,
			double newVal) {
		switch (indexPropriete) {
		case 0:
			noeudSelectionne.setPositionX(newVal);
			break;
		case 1:
			noeudSelectionne.setPositionY(newVal);
			break;
		case 2:
			noeudSelectionne.setRotation(newVal);
			break;
		case 3:
			noeudSelectionne.setEchelle(newVal);
			break;
		}

		FacadeCpp.fctC_modifierSeulNoeudSelectionne(noeudSelectionne);

		UpdateVue();
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	private String selectFile() throws CancellationException {

		JFileChooser fc = new JFileChooser();

		File dossierSauvegarde = new File(System.getProperty("user.dir")
				+ "/zones");

		fc.setAcceptAllFileFilterUsed(false);
		fc.setMultiSelectionEnabled(false);
		fc.setFileFilter(new FileNameExtensionFilter("Game data (.xml)", "xml"));
		fc.setCurrentDirectory(dossierSauvegarde);

		int returnVal = fc.showOpenDialog(gestionnaireDeVue.getFenetre());

		if (returnVal != JFileChooser.APPROVE_OPTION) {
			throw new CancellationException("L'action a été annulé.");
		}

		File file = fc.getSelectedFile();

		if (!fc.getCurrentDirectory().equals(dossierSauvegarde)) {
			JOptionPane
					.showMessageDialog(
							gestionnaireDeVue.getFenetre(),
							"Le fichier "
									+ file.getAbsolutePath()
									+ " n'a pas pu être sélectionné car il ne se trouve pas dans le dossier /zones.",
							"Erreur de sélection du fichier.",
							JOptionPane.ERROR_MESSAGE);
			throw new CancellationException("L'action a été annulé.");
		}

		return file.getAbsolutePath();
	}
	
	private File selectFileNoRestriction() throws CancellationException {

		JFileChooser fc = new JFileChooser();

		File dossierSauvegarde = new File(System.getProperty("user.dir")
				+ "/zones");

		fc.setAcceptAllFileFilterUsed(false);
		fc.setMultiSelectionEnabled(false);
		fc.setFileFilter(new FileNameExtensionFilter("Game data (.xml)", "xml"));
		fc.setCurrentDirectory(dossierSauvegarde);

		int returnVal = fc.showOpenDialog(gestionnaireDeVue.getFenetre());

		
		if (returnVal != JFileChooser.APPROVE_OPTION) {
			//throw new CancellationException("L'action a été annulé.");
		}

		File file = fc.getSelectedFile();

		if (!fc.getCurrentDirectory().equals(dossierSauvegarde)) {
			JOptionPane
					.showMessageDialog(
							gestionnaireDeVue.getFenetre(),
							"Le fichier "
									+ file.getAbsolutePath()
									+ " n'a pas pu être sélectionné car il ne se trouve pas dans le dossier /zones.",
							"Erreur de sélection du fichier.",
							JOptionPane.ERROR_MESSAGE);
			throw new CancellationException("L'action a été annulé.");
		}
		
		return file;
	}
	
	public class TestTimer {
	     private JLabel label;
	     Timer countdownTimer;
	     int timeRemaining = 5;
	     String text;
	     
	     public TestTimer(JLabel passedLabel, String text) {
	    	 this.label = passedLabel;
	    	 this.text = text;
	    	 //passedLabel.setText(text);
	    	 countdownTimer = new Timer(500, new CountdownTimerListener());
	    	 countdownTimer.start();
	     }
	     
	      class CountdownTimerListener implements ActionListener {
	          public void actionPerformed(ActionEvent e) {
	        	  while(--timeRemaining > 0) {
	        		  
	        	  }
	        	  countdownTimer.stop();
	          }
	      }
	  }
	
	public class TimerJFrame extends JFrame implements KeyListener {
	    private static final long serialVersionUID = 1L;
	    private JLabel label;
	    private TestTimer timer;
	    
	    public TimerJFrame(String strFullText) {
	    	addKeyListener(this);
	    	setSize(900, 600);
	    	
	    	this.setLayout(new GridLayout());
	    	JLabel label = new JLabel(strFullText);
	    	label.setHorizontalAlignment(SwingConstants.CENTER);
	    	this.add(label);
	    	this.pack();
	    	this.setVisible(true);
	    	
	        //this.getContentPane().add(textLabel, BorderLayout.CENTER); 
	        
			
			//label = new JLabel("10", JLabel.CENTER);
			timer = new TestTimer(label, strFullText);
			this.setLocationRelativeTo(null);
		}

		@Override
		public void keyPressed(KeyEvent e) {
			if(e.getKeyCode() == KeyEvent.VK_SPACE) {
				this.dispose();
			}
		}

		@Override
		public void keyReleased(KeyEvent e) {
			// TODO Auto-generated method stub
			
		}

		@Override
		public void keyTyped(KeyEvent e) {
			// TODO Auto-generated method stub
			
		}
	    
	}
	
	public static Node findNode(
		      Node root,
		      String elementName,
		      boolean deep,
		      boolean elementsOnly) {
		      //Check to see if root has any children if not return null
	  if (!(root.hasChildNodes()))
	    return null;
	
	  //Root has children, so continue searching for them
	  Node matchingNode = null;
	  String nodeName = null;
	  Node child = null;
	
	  NodeList childNodes = root.getChildNodes();
	  int noChildren = childNodes.getLength();
	  for (int i = 0; i < noChildren; i++) {
	    if (matchingNode == null) {
	      child = childNodes.item(i);
	      nodeName = child.getNodeName();
	      if ((nodeName != null) & (nodeName.equals(elementName)))
	        return child;
	      if (deep)
	        matchingNode =
	          findNode(child, elementName, deep, elementsOnly);
	    } else
	      break;
	  }
	
	  if (!elementsOnly) {
	    NamedNodeMap childAttrs = root.getAttributes();
	    noChildren = childAttrs.getLength();
	    for (int i = 0; i < noChildren; i++) {
	      if (matchingNode == null) {
	        child = childAttrs.item(i);
	        nodeName = child.getNodeName();
	        if ((nodeName != null) & (nodeName.equals(elementName)))
	          return child;
	      } else
	        break;
	    }
	  }
	  return matchingNode;
	}
	String LireConfigurationZoneJeu(String name) {
		String strFullText = null;
		try {
			String strCanonicalPath = new File(".").getCanonicalPath();
			String strConfigPath = strCanonicalPath + "\\zones\\" + name;
			File fXmlFile = new File(strConfigPath);
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
			org.w3c.dom.Document doc = dBuilder.parse(fXmlFile);
			doc.getDocumentElement().normalize();
			
			int ptVie;
			int niveauDifficulte ;
			int dureePartie;
			int nombreStationsSauver;
			
			// Nombre des points de vies des stations
			NodeList nodeList = doc.getElementsByTagName("stationSpatiale");
			Vector<Integer> vecPointsVie = new Vector<Integer>();
			for (int i = 0; i < nodeList.getLength(); i++) {
				Node n = nodeList.item(i);
				if (n != null) {
					Node absrait = findNode(n, "abstrait", true, true);;
					if(absrait != null) {
						Node PointDeVie = absrait.getAttributes().getNamedItem("PointDeVie");
						if(PointDeVie != null) {
							String strptVie = (absrait.getAttributes().getNamedItem("PointDeVie").getNodeValue());
							ptVie = Integer.parseInt(strptVie);
							vecPointsVie.add(ptVie);
						}
					}
				}
			}
			
			Node propriety = findNode(doc, "proprietes", true, true);
			String strNiveauDifficulteeTemp = "Facile";
			String strNbStationsTemp = "0";
			if(propriety != null) {
				niveauDifficulte = Integer.parseInt(propriety.getAttributes().getNamedItem("cotediff").getNodeValue());
				nombreStationsSauver = Integer.parseInt(propriety.getAttributes().getNamedItem("stations").getNodeValue());
				
				strNiveauDifficulteeTemp = "Niveau de difficulté: " + propriety.getAttributes().getNamedItem("cotediff").getNodeValue();
				strNbStationsTemp = "Nombre de station à sauver: " + propriety.getAttributes().getNamedItem("stations").getNodeValue();
			}
			
			if(strNiveauDifficulteeTemp == "1") {
				strNiveauDifficulteeTemp = "Medium";
			} else if(strNiveauDifficulteeTemp == "2") {
				strNiveauDifficulteeTemp = "Expert";
			} else {
				strNiveauDifficulteeTemp = "Hardcore";
			}
			
			String strZoneJeu = "<html>Nom de la zone de jeu: " + name + "<br>";
			String strNiveauDifficultee = "Niveau de difficulté: " + strNiveauDifficulteeTemp + "<br>";
			String strDureePartie = "Durée de la partie: " + "<br>";
			String strNbStations = "Nombre de station à sauver: " + strNbStationsTemp + "<br>";
			for (int i = 0; i < vecPointsVie.size(); i++) {
				String strStation = "\tNombre des points de vie de la station" + i + ": " + vecPointsVie.elementAt(i) + "<br>";
				strNbStations += strStation;
			}
			
			strFullText = strZoneJeu + strNiveauDifficultee + strDureePartie + strNbStations + "</html>";
				
		} catch (Exception e) {
			e.printStackTrace();
		}
		return strFullText;
	}
	
	

}
