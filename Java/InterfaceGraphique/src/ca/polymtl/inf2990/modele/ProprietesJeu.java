package ca.polymtl.inf2990.modele;

public class ProprietesJeu {
	// Chacune des propriétés du jeu
	private int victoire;
	private int frequence;
	private int acceleration;
	private int difficulte;
	
	
	public ProprietesJeu(int victoire, int frequence, int acceleration, int difficulte) {
		this.victoire = victoire;
		this.frequence = frequence;
		this.acceleration = acceleration;
		this.difficulte = difficulte;
	}
	
	public int getVictoire() {
		return victoire;
	}

	public void setVictoire(int victoire) {
		this.victoire = victoire;
	}

	public int getFrequence() {
		return frequence;
	}

	public void setFrequence(int frequence) {
		this.frequence = frequence;
	}

	public int getAcceleration() {
		return acceleration;
	}

	public void setAcceleration(int acceleration) {
		this.acceleration = acceleration;
	}

	public int getDifficulte() {
		return difficulte;
	}

	public void setDifficulte(int difficulte) {
		this.difficulte = difficulte;
	}

	/*public double getPropriete(int index) {
		switch (index) {
		case 0:
			return positionX;
		case 1:
			return positionY;
		case 2:
			return rotation;
		case 3:
			return echelle;
		default:
			return 0;
		}
	}*/
}
