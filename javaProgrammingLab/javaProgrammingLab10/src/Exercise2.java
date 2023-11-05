import javax.swing.*;
import java.awt.*;
import javax.swing.GroupLayout.Alignment;
import net.miginfocom.swing.MigLayout;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class Exercise2 extends JFrame {
	public Exercise2() {
		setResizable(false);
		setTitle("Exercise2");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 400, 200);
		getContentPane().setLayout(new GridLayout(2, 2, 0, 0));

		JLabel lblNewLabel_0 = new JLabel("Fahrenheit");
		lblNewLabel_0.setHorizontalAlignment(SwingConstants.CENTER);
		getContentPane().add(lblNewLabel_0);

		JTextArea textArea = new JTextArea();
		getContentPane().add(textArea);

		JButton btnNewButton = new JButton("Calculate");
		getContentPane().add(btnNewButton);

		JLabel lblNewLabel_1 = new JLabel();
		lblNewLabel_1.setHorizontalAlignment(SwingConstants.CENTER);
		getContentPane().add(lblNewLabel_1);
		setVisible(true);

		btnNewButton.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseReleased(MouseEvent e) {
				String inputString = textArea.getText();
				Double fahrenheit;
				try {
					fahrenheit = Double.parseDouble(inputString);
					lblNewLabel_1.setText(Double.toString(getCelsius(fahrenheit)));
				} catch (Exception e1) {
					lblNewLabel_1.setText("incorrect input");
				}
			}
		});
	}

	public double getCelsius(double Fahrenheit) {
		return (Fahrenheit - 32) * 5 / 9;
	}

	public static void main(String[] args) {
		new Exercise2();
	}
}
