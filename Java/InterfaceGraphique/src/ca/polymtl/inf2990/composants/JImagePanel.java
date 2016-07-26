package ca.polymtl.inf2990.composants;

import java.awt.Graphics;
import java.awt.Image;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;

import javax.swing.JPanel;

// Basé sur la réponse de Java42 dans http://stackoverflow.com/questions/15479820/set-background-image-for-jpanel-in-java-breakout-game
@SuppressWarnings("serial")
public class JImagePanel extends JPanel {
	private Image originalImage = null;
	private Image scaledImage = null;

	public JImagePanel(final Image image) {
		originalImage = image;

		this.addComponentListener(new ComponentAdapter() {
			@Override
			public void componentResized(final ComponentEvent e) {
				final int panelWidth = JImagePanel.this.getWidth();
				final int panelHeight = JImagePanel.this.getHeight();

				if (panelWidth > 0 && panelHeight > 0) {
					scaledImage = originalImage.getScaledInstance(panelWidth,
							panelHeight, Image.SCALE_SMOOTH);
				} else {
					scaledImage = originalImage;
				}

				JImagePanel.this.repaint();
			}
		});
	}

	@Override
	public void paintComponent(final Graphics g) {
		super.paintComponent(g);
		if (scaledImage != null) {
			g.drawImage(scaledImage, 0, 0, null);
		}
	}
}