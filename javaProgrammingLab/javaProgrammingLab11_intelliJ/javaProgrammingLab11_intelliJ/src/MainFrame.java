import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;


public class MainFrame extends JFrame {
    private static final String[] labelText = {
            // @formatter:off
            "Applicant Name: ",
            "Birth Date: ",
            "Email: ",
            "Degree: ",
            "Attended university (for Graduates): ",
            "GPA (for Graduates): ",
            // @formatter:on
    };
    private ArrayList<JTextField> textList = new ArrayList<JTextField>();

    public MainFrame() {
        setResizable(false);
        setTitle("Assignment 3");
        setBounds(100, 100, 900, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);

        getContentPane().setLayout(new BorderLayout(0, 0));

        JPanel panelWallpaper = new JPanel();
        panelWallpaper.setBackground(new Color(255, 255, 255));
        getContentPane().add(panelWallpaper, BorderLayout.WEST);

        JLabel lblWallpaper = new JLabel(new ImageIcon("images/skku_wallpaper.png"));
        lblWallpaper.setMinimumSize(new Dimension(100, 100));
        panelWallpaper.add(lblWallpaper);

        JPanel panelSubmit = new JPanel();
        panelSubmit.setBackground(new Color(255, 255, 255));
        getContentPane().add(panelSubmit, BorderLayout.CENTER);
        GridBagLayout gbl = new GridBagLayout();
        gbl.columnWeights = new double[]{1.0, 1.0};
        gbl.columnWidths = new int[]{400, 400};
        gbl.rowWeights = new double[20];
        gbl.rowHeights = new int[20];
        Arrays.fill(gbl.rowWeights, 1.0);
        Arrays.fill(gbl.rowHeights, 10);
        gbl.rowHeights[0] = 100;
        panelSubmit.setLayout(gbl);

        JLabel lblTitle = new JLabel(new ImageIcon("images/title_label.png"));
        GridBagConstraints gbc_lblTitle = new GridBagConstraints();
        gbc_lblTitle.insets = new Insets(0, 0, 5, 0);
        gbc_lblTitle.gridx = 0;
        gbc_lblTitle.gridy = 0;
        gbc_lblTitle.gridwidth = 2;
        gbc_lblTitle.fill = GridBagConstraints.HORIZONTAL;
        panelSubmit.add(lblTitle, gbc_lblTitle);

        for (int i = 0; i < labelText.length; i++) {
            JLabel lb = new JLabel(labelText[i]);
            GridBagConstraints gbc = new GridBagConstraints();
            gbc.anchor = GridBagConstraints.EAST;
            gbc.fill = GridBagConstraints.VERTICAL;
            gbc.gridx = 0;
            gbc.gridy = i * 2 + 1;
            panelSubmit.add(lb, gbc);

            JTextField tf = new JTextField("");
            textList.add(tf);
            gbc = new GridBagConstraints();
            gbc.anchor = GridBagConstraints.WEST;
            gbc.fill = GridBagConstraints.BOTH;
            gbc.gridx = 1;
            gbc.gridy = i * 2 + 1;
            panelSubmit.add(tf, gbc);
        }
        JLabel lblStatement = new JLabel("Personal Statement");
//        lblStatement.setHorizontalAlignment(SwingConstants.CENTER);
        GridBagConstraints gbc_lblStatement = new GridBagConstraints();
        gbc_lblStatement.insets = new Insets(0, 0, 5, 0);
//        gbc_lblStatement.fill = GridBagConstraints.BOTH;
        gbc_lblStatement.gridwidth = 2;
        gbc_lblStatement.gridx = 0;
        gbc_lblStatement.gridy = labelText.length * 2 + 1;
        panelSubmit.add(lblStatement, gbc_lblStatement);

        JTextField textStatement = new JTextField("");
        textList.add(textStatement);
        GridBagConstraints gbc_textStatement = new GridBagConstraints();
        gbc_textStatement.insets = new Insets(0, 0, 5, 0);
        textStatement.setMinimumSize(new Dimension(500, 1));
        textList.add(textStatement);
        gbc_textStatement.fill = GridBagConstraints.BOTH;
        gbc_textStatement.gridwidth = 2;
        gbc_textStatement.gridheight = 2;
        gbc_textStatement.gridx = 0;
        gbc_textStatement.gridy = labelText.length * 2 + 3;
        panelSubmit.add(textStatement, gbc_textStatement);

        JLabel lblAddress = new JLabel("Home Address");
        lblAddress.setHorizontalAlignment(SwingConstants.CENTER);
        GridBagConstraints gbc_lblAddress = new GridBagConstraints();
        gbc_lblAddress.anchor = GridBagConstraints.EAST;
        gbc_lblAddress.fill = GridBagConstraints.VERTICAL;
        gbc_lblAddress.gridx = 0;
        gbc_lblAddress.gridy = labelText.length * 2 + 5;
        panelSubmit.add(lblAddress, gbc_lblAddress);

        JTextField textAddress = new JTextField("");
        textList.add(textAddress);
        GridBagConstraints gbc_textAddress = new GridBagConstraints();
        textList.add(textAddress);
        gbc_textAddress.fill = GridBagConstraints.BOTH;
        gbc_textAddress.gridx = 1;
        gbc_textAddress.gridy = labelText.length * 2 + 5;
        panelSubmit.add(textAddress, gbc_textAddress);

        JButton btn = new JButton("Submit");
        btn.setForeground(new Color(255, 255, 255));
        btn.setBackground(new Color(0, 0, 160));
        btn.addMouseListener(new MouseAdapter() {
            public void mousePressed(MouseEvent e) {
                System.out.println("...");
            }
        });
        GridBagConstraints gbc_btnNewButton = new GridBagConstraints();
        gbc_btnNewButton.gridx = 0;
        gbc_btnNewButton.gridwidth = 2;
        gbc_btnNewButton.gridy = labelText.length * 2 + 7;
        panelSubmit.add(btn, gbc_btnNewButton);

        // Start rendering
        invalidate();
        validate();
        repaint();
    }
}
