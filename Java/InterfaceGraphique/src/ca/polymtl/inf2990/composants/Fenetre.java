package ca.polymtl.inf2990.composants;

import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JComponent;
import javax.swing.JFrame;

import ca.polymtl.inf2990.vues.Vue;

@SuppressWarnings("serial")
public class Fenetre extends JFrame {
	Vue vueCourante;
	
	public Fenetre() {
		try {
			this.setIconImage(ImageIO.read(getClass()
					.getResource(
							"/ca/polymtl/inf2990/images/Logo.png")));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

	public void setVue(Vue vue) {
		// Enlever les composants de l'ancienne vue de la fenêtre principale
		if (vueCourante != null) {
			for (JComponent composant : vueCourante.getListeComposants()) {
				this.remove(composant);
			}
		}

		vueCourante = vue;

		vueCourante.ChargerComposants();
	}

	public Vue getVue() {
		return vueCourante;
	}
}
