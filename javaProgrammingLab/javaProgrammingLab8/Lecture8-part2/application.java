import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JButton;
import java.awt.Color;
import javax.swing.JTextField;
import javax.swing.JTree;
import javax.swing.JRadioButton;
import javax.swing.JList;
import javax.swing.JFormattedTextField;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JLabel;
import javax.swing.SwingConstants;

public class application extends JFrame implements ActionListener {

	private JPanel contentPane;
	private JButton ResetButton;
	private JPanel panel;
	private JLabel lblNewLabel;
	private JLabel lblNewLabel_1;
	private JLabel RedScoreLabel;
	private JLabel BlueScoreLabel;
	private JButton RedScoreButton;
	private JButton BlueScoreButton;
	private int redCounter = 0;
	private int blueCounter = 0;
	/**
	 * Create the frame.
	 */
	public application() {
		setTitle("This is the title");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 305, 205);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setLayout(new BorderLayout(0, 0));
		setContentPane(contentPane);
		
		ResetButton = new JButton("Reset Score");
		contentPane.add(ResetButton, BorderLayout.SOUTH);
		
		panel = new JPanel();
		contentPane.add(panel, BorderLayout.CENTER);
		panel.setLayout(new GridLayout(3, 2, 0, 0));
		
		lblNewLabel = new JLabel("Red Team");
		lblNewLabel.setHorizontalAlignment(SwingConstants.CENTER);
		lblNewLabel.setForeground(Color.RED);
		panel.add(lblNewLabel);
		
		lblNewLabel_1 = new JLabel("Bluee Team");
		lblNewLabel_1.setHorizontalAlignment(SwingConstants.CENTER);
		lblNewLabel_1.setForeground(Color.BLUE);
		panel.add(lblNewLabel_1);
		
		RedScoreLabel = new JLabel("0");
		RedScoreLabel.setHorizontalAlignment(SwingConstants.CENTER);
		panel.add(RedScoreLabel);
		
		BlueScoreLabel = new JLabel("0");
		BlueScoreLabel.setHorizontalAlignment(SwingConstants.CENTER);
		panel.add(BlueScoreLabel);
		
		RedScoreButton = new JButton("Red Score");
		panel.add(RedScoreButton);
		
		BlueScoreButton = new JButton("Blue Score");
		panel.add(BlueScoreButton);
		RedScoreButton.addActionListener(this);
		BlueScoreButton.addActionListener(this);
		ResetButton.addActionListener(this);
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == RedScoreButton ) {
			redCounter++;
			RedScoreLabel.setText(redCounter+"");
			
		}
		else if(e.getSource() == BlueScoreButton) {
			blueCounter++;
			BlueScoreLabel.setText(blueCounter+"");
		}
		else if(e.getSource() == ResetButton) {
			blueCounter = 0;
			redCounter = 0;
			BlueScoreLabel.setText("0");
			RedScoreLabel.setText("0");
		}
	}
	
	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					application frame = new application();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}
	

	

}
