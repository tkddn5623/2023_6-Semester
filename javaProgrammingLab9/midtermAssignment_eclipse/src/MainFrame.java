import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;

@SuppressWarnings("serial")
public class MainFrame extends JFrame {
	static final private String[] helpString = {
			//@formatter:off
			"Choose transport (from left menu):\n",
			"Add more transport (from right menu)?", 
			"You choose TAXI\n" + "Enter base fare: ",
			"Enter fare per km: ",
			"Enter distance (in KM): ", 
			"You choose BUS\n" + "Enter base fare: ",
			"Enter fare per station (for extra stations): ",
			"Enter number of stations: ",
			"You choose TRAIN\n" + "Enter base fare: ",
			"Enter fare per station (for extra stations): ",
			"Enter number of stations: ",
			//@formatter:on
	};
	private int state;
	private int number;
	private ArrayList<Integer> argmentList;
	private ArrayList<PublicTransport> transportList;
	private JTextArea textArea;

	public MainFrame() {
		// Initialization about variables
		state = 0;
		number = 0;
		argmentList = new ArrayList<Integer>(5);
		for (int i = 0; i < 5; i++) {
			argmentList.add(0);
		}
		transportList = new ArrayList<PublicTransport>(10);
		
		// Initialization about GUI
		setResizable(false);
		setTitle("Trip Planner");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 600, 550);

		JPanel panel = new JPanel();
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

		textArea = new JTextArea();
		textArea.setEditable(false);
		textArea.setText(helpString[state]);

		JScrollPane scrollPane = new JScrollPane(textArea);
		scrollPane.setPreferredSize(new Dimension(500, 200));
		panel_2.add(scrollPane);

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

		// Initialization about Listeners
		btnNewButton_0.addMouseListener(new MouseAdapter() {
			public void mouseReleased(MouseEvent e) {
				numberHandle(0);
			}
		});
		btnNewButton_1.addMouseListener(new MouseAdapter() {
			public void mouseReleased(MouseEvent e) {
				numberHandle(1);
			}
		});
		btnNewButton_2.addMouseListener(new MouseAdapter() {
			public void mouseReleased(MouseEvent e) {
				numberHandle(2);
			}
		});
		btnNewButton_3.addMouseListener(new MouseAdapter() {
			public void mouseReleased(MouseEvent e) {
				numberHandle(3);
			}
		});
		btnNewButton_4.addMouseListener(new MouseAdapter() {
			public void mouseReleased(MouseEvent e) {
				numberHandle(4);
			}
		});
		btnNewButton_5.addMouseListener(new MouseAdapter() {
			public void mouseReleased(MouseEvent e) {
				numberHandle(5);
			}
		});
		btnNewButton_6.addMouseListener(new MouseAdapter() {
			public void mouseReleased(MouseEvent e) {
				numberHandle(6);
			}
		});
		btnNewButton_7.addMouseListener(new MouseAdapter() {
			public void mouseReleased(MouseEvent e) {
				numberHandle(7);
			}
		});
		btnNewButton_8.addMouseListener(new MouseAdapter() {
			public void mouseReleased(MouseEvent e) {
				numberHandle(8);
			}
		});
		btnNewButton_9.addMouseListener(new MouseAdapter() {
			public void mouseReleased(MouseEvent e) {
				numberHandle(9);
			}
		});
		btnNewButton_TAXI.addMouseListener(new MouseAdapter() {
			public void mouseReleased(MouseEvent e) {
				if (state != 0)
					return;
				number = 0;
				state = 2;
				textArea.setText(helpString[state]);
			}
		});
		btnNewButton_BUS.addMouseListener(new MouseAdapter() {
			public void mouseReleased(MouseEvent e) {
				if (state != 0)
					return;
				number = 0;
				state = 5;
				textArea.setText(helpString[state]);
			}
		});
		btnNewButton_TRAIN.addMouseListener(new MouseAdapter() {
			public void mouseReleased(MouseEvent e) {
				if (state != 0)
					return;
				number = 0;
				state = 8;
				textArea.setText(helpString[state]);
			}
		});
		btnNewButton_CANCEL.addMouseListener(new MouseAdapter() {
			public void mouseReleased(MouseEvent e) {
				state = 0;
				number = 0;
				transportList.clear();
				textArea.setText("Cancelled!\n New Plan:\n");
				textArea.append(helpString[state]);
			}
		});
		btnNewButton_CLEAR.addMouseListener(new MouseAdapter() {
			public void mouseReleased(MouseEvent e) {
				number = 0;
				textArea.setText(helpString[state]);
			}
		});
		btnNewButton_YES.addMouseListener(new MouseAdapter() {
			public void mouseReleased(MouseEvent e) {
				if (state != 1)
					return;
				state = 0;
				textArea.setText(helpString[state]);
			}
		});
		btnNewButton_NO.addMouseListener(new MouseAdapter() {
			public void mouseReleased(MouseEvent e) {
				if (state != 1)
					return;
				double totalTripFare = 0;
				textArea.setText("");
				int i = 1;
				for (PublicTransport p : transportList) {
					textArea.append("Transport " + i + ": " + p.getModel() + "\n");
					textArea.append("Fare:" + p.getTotalFare() + "\n");
					totalTripFare += p.getTotalFare();
					i++;
				}
				textArea.append("=========================\n");
				textArea.append("Total Trip Fare: " + totalTripFare + "\n");

				// Below code allows retry. Same as cancel event listener
				transportList.clear();
				state = 0;
				number = 0;
			}
		});
		
		// The main part of this assignment.
		// this finite automata prevents errors by wrong button click
		btnNewButton_ENTER.addMouseListener(new MouseAdapter() {
			public void mouseReleased(MouseEvent e) {
				if (state == 2) {
					state = 3;
					textArea.setText(helpString[state]);
					argmentList.set(0, number);
				} else if (state == 3) {
					state = 4;
					textArea.setText(helpString[state]);
					argmentList.set(1, number);
				} else if (state == 4) {
					state = 1;
					textArea.setText(helpString[state]);
					argmentList.set(2, number);
					Taxi taxi = new Taxi("KOR TAXI", argmentList.get(0), argmentList.get(1), argmentList.get(2));
					transportList.add(taxi);
				} else if (state == 5) {
					state = 6;
					textArea.setText(helpString[state]);
					argmentList.set(0, number);
				} else if (state == 6) {
					state = 7;
					textArea.setText(helpString[state]);
					argmentList.set(1, number);
				} else if (state == 7) {
					state = 1;
					textArea.setText(helpString[state]);
					argmentList.set(2, number);
					Bus bus = new Bus("KOR BUS", argmentList.get(0), argmentList.get(1), argmentList.get(2));
					transportList.add(bus);
				} else if (state == 8) {
					state = 9;
					textArea.setText(helpString[state]);
					argmentList.set(0, number);
				} else if (state == 9) {
					state = 10;
					textArea.setText(helpString[state]);
					argmentList.set(1, number);
				} else if (state == 10) {
					state = 1;
					textArea.setText(helpString[state]);
					argmentList.set(2, number);
					Train train = new Train("KOR TRAIN", argmentList.get(0), argmentList.get(1), argmentList.get(2));
					transportList.add(train);
				}
				number = 0;
			}
		});
	}

	private void numberHandle(int N) {
		if (state == 0 || state == 1)
			return;
		this.number = this.number * 10 + N;
		if (this.number != 0)
			textArea.append(Integer.toString(N));
	}
}
