package ca.polymtl.inf2990.vue.modeScoreVue;

	import java.awt.BorderLayout;
import java.awt.Canvas;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.Label;
import java.lang.reflect.InvocationTargetException;
import java.util.Timer;
import java.util.TimerTask;

	import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JMenuBar;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

	import ca.polymtl.inf2990.composants.Fenetre;
import ca.polymtl.inf2990.cpp.FacadeCpp;
import ca.polymtl.inf2990.gestionnaires.GestionnaireEtatAction;
import ca.polymtl.inf2990.gestionnaires.GestionnaireEvenement;
import ca.polymtl.inf2990.gestionnaires.GestionnaireDeVue.TypesVue;
import ca.polymtl.inf2990.vue.editeur.EditeurBarreOutils;
import ca.polymtl.inf2990.vue.editeur.EditeurBarreProprietes;
import ca.polymtl.inf2990.vue.editeur.EditeurMenu;
import ca.polymtl.inf2990.vues.Vue;

	public class ModeScoreVue extends JPanel {
			private GestionnaireEvenement ge;
			private JButton brejouer;
			private JButton bmenuPrincipal;
			private Label textScore;
			
			JPanel setText, setext, grouper;
			
			public ModeScoreVue(GestionnaireEvenement gestionnaireEvenement) { 
				
				//this.setSize(new Dimension(400,200));
				//this.setLocation(450, 300);
				setext = setTextScore();
				grouper = groupMenu();
				this.setLayout(new BorderLayout());
				this.add(setext, BorderLayout.CENTER);
				this.add(grouper, BorderLayout.SOUTH);
				this.setVisible(false);
				
			}
			
			
			public JPanel groupMenu(){
				JPanel group = new JPanel();
				brejouer = new JButton("Rejouer");
				brejouer.setFocusable(isCursorSet());
				brejouer.setActionCommand("Rejouer");
				brejouer.addActionListener(ge);
				brejouer.setPreferredSize(new Dimension(150, 40));
				bmenuPrincipal = new JButton("Menu principal");
				bmenuPrincipal.setActionCommand("Changer vue: menu");
				bmenuPrincipal.addActionListener(ge);
				bmenuPrincipal.setPreferredSize(new Dimension(150, 40));
				group.add(brejouer);
				group.add(bmenuPrincipal);
				return group;
			}
			public JButton getBoutonMenuPrincipal(){
				return bmenuPrincipal;
			}
			
			public JButton getBoutonRejouer(){
				return brejouer;
			}
				
			public Label getTextScore(){
				return textScore;
			}
			public JPanel setTextScore(){
				setText = new JPanel();
				textScore = new Label();
				setText.add(textScore);
				return setText;
			}
			
			
}

