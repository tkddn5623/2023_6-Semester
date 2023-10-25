import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class MainFrame extends JFrame {
	public MainFrame() {
		setResizable(false);
		setTitle("Trip Planner");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 600, 550);

		JPanel panel = new JPanel();
		panel.setBackground(new Color(255, 128, 0));
		getContentPane().add(panel, BorderLayout.CENTER);
		panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));

		JPanel panel_1 = new JPanel();
		panel.add(panel_1);

		JLabel lblNewLabel = new JLabel(new ImageIcon("assets/planner_logo.png"));
		panel_1.add(lblNewLabel);

		JPanel panel_2 = new JPanel();
		panel.add(panel_2);
		panel_2.setLayout(new BoxLayout(panel_2, BoxLayout.X_AXIS));

		JPanel panel_4 = new JPanel();
		panel_4.setAlignmentX(Component.LEFT_ALIGNMENT);
		panel_2.add(panel_4);
		panel_4.setLayout(new GridLayout(3, 0, 0, 0));

		JButton btnNewButton_TRAIN = new JButton("TRAIN", new ImageIcon("assets/train.png"));
		panel_4.add(btnNewButton_TRAIN);

		JButton btnNewButton_BUS = new JButton("BUS", new ImageIcon("assets/bus.png"));
		panel_4.add(btnNewButton_BUS);

		JButton btnNewButton_TAXI = new JButton("TAXI", new ImageIcon("assets/taxi.png"));
		panel_4.add(btnNewButton_TAXI);

		JTextArea textArea = new JTextArea();
		textArea.setEditable(false);
		panel_2.add(textArea);

		JPanel panel_5 = new JPanel();
		panel_2.add(panel_5);
		panel_5.setLayout(new GridLayout(2, 1, 0, 0));

		JButton btnNewButton_YES = new JButton("YES", new ImageIcon("assets/enterSmall.png"));
		panel_5.add(btnNewButton_YES);

		JButton btnNewButton_NO = new JButton("NO", new ImageIcon("assets/cancelSmall.png"));
		panel_5.add(btnNewButton_NO);

		JPanel panel_3 = new JPanel();
		panel.add(panel_3);
		panel_3.setLayout(new GridLayout(4, 4, 0, 0));

		JButton btnNewButton_1 = new JButton(new ImageIcon("assets/1.png"));
		panel_3.add(btnNewButton_1);

		JButton btnNewButton_2 = new JButton(new ImageIcon("assets/2.png"));
		panel_3.add(btnNewButton_2);

		JButton btnNewButton_3 = new JButton(new ImageIcon("assets/3.png"));
		panel_3.add(btnNewButton_3);

		JButton btnNewButton_CANCEL = new JButton("CANCEL", new ImageIcon("assets/cancel.png"));
		panel_3.add(btnNewButton_CANCEL);

		JButton btnNewButton_4 = new JButton(new ImageIcon("assets/4.png"));
		panel_3.add(btnNewButton_4);

		JButton btnNewButton_5 = new JButton(new ImageIcon("assets/5.png"));
		panel_3.add(btnNewButton_5);

		JButton btnNewButton_6 = new JButton(new ImageIcon("assets/6.png"));
		panel_3.add(btnNewButton_6);

		JButton btnNewButton_CLEAR = new JButton("CLEAR", new ImageIcon("assets/clear.png"));
		panel_3.add(btnNewButton_CLEAR);

		JButton btnNewButton_7 = new JButton(new ImageIcon("assets/7.png"));
		panel_3.add(btnNewButton_7);

		JButton btnNewButton_8 = new JButton(new ImageIcon("assets/8.png"));
		panel_3.add(btnNewButton_8);

		JButton btnNewButton_9 = new JButton(new ImageIcon("assets/9.png"));
		panel_3.add(btnNewButton_9);

		JButton btnNewButton_ENTER = new JButton("ENTER", new ImageIcon("assets/enter.png"));
		panel_3.add(btnNewButton_ENTER);

		JButton btnNewButton_0 = new JButton(new ImageIcon("assets/0.png"));
		panel_3.add(btnNewButton_0);
		setVisible(true);
	}
}
