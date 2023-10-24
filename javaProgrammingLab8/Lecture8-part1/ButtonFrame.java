
// Creating JButtons.
import java.awt.FlowLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

import javax.swing.AbstractButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JButton;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JOptionPane;
import javax.swing.JRadioButton;
import javax.swing.JToggleButton;

public class ButtonFrame extends JFrame implements ActionListener {
	private AbstractButton plainJButton; // button with just text
	private JButton fancyJButton; // button with icons

	// ButtonFrame adds JButtons to JFrame
	public ButtonFrame() {
		super("Testing Buttons");
		setLayout(new FlowLayout()); // set frame layout

		plainJButton = new JRadioButton("Plain Button"); // button with text
		add(plainJButton); // add plainJButton to JFrame

		Icon bug1 = new ImageIcon(getClass().getResource("bug1.gif"));
		Icon bug2 = new ImageIcon(getClass().getResource("bug2.gif"));
		fancyJButton = new JButton("RollOver Button", bug1); // set image
		fancyJButton.setRolloverIcon(bug2); // set rollover image
		add(fancyJButton); // add fancyJButton to JFrame

		// create new ButtonHandler for button event handling

		fancyJButton.addActionListener(this);
		plainJButton.addActionListener(this);
	} // end ButtonFrame constructor

	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == fancyJButton) {

			JOptionPane.showMessageDialog(ButtonFrame.this, "fancyJButton", "fancyJButton action",
					JOptionPane.INFORMATION_MESSAGE);
		} 
		
		else if (e.getSource() == plainJButton) {
			JOptionPane.showMessageDialog(ButtonFrame.this, "Plain button", "Plain button action",
					JOptionPane.INFORMATION_MESSAGE);

		}

	}

} // end class ButtonFrame