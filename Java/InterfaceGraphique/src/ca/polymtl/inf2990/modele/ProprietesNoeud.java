package ca.polymtl.inf2990.modele;


public class ProprietesNoeud {
	// Chacune des propriétés du noeud
	private String type;
	private double positionX;
	private double positionY;
	private double rotation;
	private double echelle;
	
	public ProprietesNoeud(String type, double positionX, double positionY, double rotation, double echelle) {
		this.type = type;
		this.positionX = positionX;
		this.positionY = positionY;
		this.rotation = rotation;
		this.echelle = echelle;
	}
	
	public final String getType() {
		return type;
	}
	
	public final double getPositionX() {
		return positionX;
	}
	
	public final double getPositionY() {
		return positionY;
	}
	
	public final double getRotation() {
		return rotation;
	}
	
	public final double getEchelle() {
		return echelle;
	}
	
	public void setPositionX(double value) {
		positionX = value;
	}
	
	public void setPositionY(double value) {
		positionY = value;
	}
	
	public void setRotation(double value) {
		rotation = value;
	}
	
	public void setEchelle(double value) {
		if (value <= 0) {
			//TODO Show error
		} else {
			echelle = value;
		}
	}
	
	public double getPropriete(int index) {
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
	}
}
