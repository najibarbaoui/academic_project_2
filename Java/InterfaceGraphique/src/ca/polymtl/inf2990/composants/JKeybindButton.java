package ca.polymtl.inf2990.composants;

import java.awt.Dimension;
import java.util.List;

import javax.swing.JButton;

@SuppressWarnings("serial")
public class JKeybindButton extends JButton {
	List<Character> usedKeybinds;
	char defaultValue;
	
	public JKeybindButton(List<Character> usedKeybinds, char defaultValue) {
		this.usedKeybinds = usedKeybinds;
		this.defaultValue = defaultValue;
		
		this.setPreferredSize(new Dimension(50, 50));
		
		// Set value
		this.setText("" + this.defaultValue);
	}
	
	public void ResetDefaultValue() {
		this.setText("" + defaultValue);
	}
}
