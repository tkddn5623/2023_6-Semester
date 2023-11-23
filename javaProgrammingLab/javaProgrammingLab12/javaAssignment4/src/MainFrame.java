import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;

@SuppressWarnings("serial")
public class MainFrame extends JFrame {
    public MainFrame() {
        // Initialization about GUI
        setResizable(false);
        setTitle("Assignment4");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setBounds(100, 100, 600, 550);

        JPanel panel_0 = new JPanel();
        getContentPane().add(panel_0, BorderLayout.CENTER);
        panel_0.setLayout(new BoxLayout(panel_0, BoxLayout.Y_AXIS));

        JPanel panel_1 = new JPanel();
        panel_1.setLayout(new BoxLayout(panel_1, BoxLayout.X_AXIS));
        panel_1.setMaximumSize(new Dimension((int) getBounds().getWidth(), 100));
        panel_0.add(panel_1);

        JLabel label_0 = new JLabel("Number of row in Lucas series: ");
        panel_1.add(label_0);

        JTextField textInput = new JTextField();
        textInput.setMinimumSize(new Dimension(40, 20));
        panel_1.add(textInput);

        JButton btnGet = new JButton("Get Sum of Lucas series");
        panel_1.add(btnGet);

        JButton btnCancel = new JButton("Cancel");
        btnCancel.setEnabled(false);
        panel_1.add(btnCancel);

        JPanel panel_2 = new JPanel();
        panel_2.setLayout(new BoxLayout(panel_2, BoxLayout.X_AXIS));
        panel_2.setMinimumSize((new Dimension((int) getBounds().getWidth(), 300)));
        panel_0.add(panel_2);

        JTextArea textOutput = new JTextArea();
        textOutput.setEditable(false);
        panel_2.add(textOutput);

        JPanel panel_3 = new JPanel();
        panel_3.setLayout(new BoxLayout(panel_3, BoxLayout.X_AXIS));
        panel_0.add(panel_3);

        JProgressBar progressBar = new JProgressBar();
        progressBar.setPreferredSize(new Dimension(100,25));
//        progressBar.setValue();
        panel_3.add(progressBar);

        JLabel labelSum = new JLabel();
        labelSum.setPreferredSize((new Dimension(60, 25)));
        panel_3.add(labelSum);

        setVisible(true);

        // Initialization about Listener
        btnGet.addMouseListener(new MouseAdapter() {
            public void mouseReleased(MouseEvent e) {
                if (!textInput.getText().matches("[0-9]+")){
                    JOptionPane.showMessageDialog(getContentPane(), "Enter valid input! (3~20)");
                    return;
                }
                int n = Integer.parseInt(textInput.getText());
                if (n < 3 || n > 20) {
                    JOptionPane.showMessageDialog(getContentPane(), "Enter valid input! (3~20)");
                    return;
                }
                SwingWorker<ArrayList<Integer>, Integer> sw;



            }
        });
    }
}
