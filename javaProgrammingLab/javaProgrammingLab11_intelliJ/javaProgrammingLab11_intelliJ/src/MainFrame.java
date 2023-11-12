import javax.swing.*;
import javax.swing.plaf.basic.BasicInternalFrameTitlePane;
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
            "Phone number: ",
            "Attended university (for Graduates): ",
            "GPA (for Graduates): ",
            // @formatter:on
    };
    private ArrayList<JTextField> textList;

    // Makes components and Renders GUI
    public MainFrame() {
        // Makes components
        setResizable(false);
        setTitle("Assignment 3");
        setBounds(100, 100, 900, 700);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);

        textList = new ArrayList<JTextField>();
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
        gbl.rowWeights = new double[24];
        gbl.rowHeights = new int[24];
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
        GridBagConstraints gbc_lblStatement = new GridBagConstraints();
        gbc_lblStatement.gridwidth = 2;
        gbc_lblStatement.gridx = 0;
        gbc_lblStatement.gridy = labelText.length * 2 + 1;
        panelSubmit.add(lblStatement, gbc_lblStatement);


        JTextArea textStatement = new JTextArea("");
        JScrollPane scrollPane = new JScrollPane(textStatement);
        scrollPane.setMinimumSize(new Dimension(500, 100));
        scrollPane.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
        scrollPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_NEVER);
        textStatement.setLineWrap(true);
        GridBagConstraints gbc_scrollPane = new GridBagConstraints();
        gbc_scrollPane.fill = GridBagConstraints.BOTH;
        gbc_scrollPane.gridwidth = 2;
        gbc_scrollPane.gridheight = 2;
        gbc_scrollPane.gridx = 0;
        gbc_scrollPane.gridy = labelText.length * 2 + 3;
        panelSubmit.add(scrollPane, gbc_scrollPane);

        JLabel lblAddress = new JLabel("Home Address: ");
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
        gbc_textAddress.fill = GridBagConstraints.BOTH;
        gbc_textAddress.gridx = 1;
        gbc_textAddress.gridy = labelText.length * 2 + 5;
        panelSubmit.add(textAddress, gbc_textAddress);

        JLabel lblHuman = new JLabel("Human check: Write here (1 + 7) = ?? ");
        lblHuman.setHorizontalAlignment(SwingConstants.CENTER);
        GridBagConstraints gbc_lblHuman = new GridBagConstraints();
        gbc_lblHuman.anchor = GridBagConstraints.EAST;
        gbc_lblHuman.fill = GridBagConstraints.VERTICAL;
        gbc_lblHuman.gridx = 0;
        gbc_lblHuman.gridy = labelText.length * 2 + 7;
        panelSubmit.add(lblHuman, gbc_lblHuman);

        JTextField textHuman = new JTextField("");
        textList.add(textHuman);
        GridBagConstraints gbc_textHuman = new GridBagConstraints();
        gbc_textHuman.fill = GridBagConstraints.BOTH;
        gbc_textHuman.gridx = 1;
        gbc_textHuman.gridy = labelText.length * 2 + 7;
        panelSubmit.add(textHuman, gbc_textHuman);

        JButton btn = getSubmitButton(textStatement);
        GridBagConstraints gbc_btnNewButton = new GridBagConstraints();
        gbc_btnNewButton.gridx = 0;
        gbc_btnNewButton.gridwidth = 2;
        gbc_btnNewButton.gridy = labelText.length * 2 + 9;
        panelSubmit.add(btn, gbc_btnNewButton);

        // Renders GUI
        invalidate();
        validate();
        repaint();
    }

    // Wrapper of JOptionPane.showMessageDialog
    private void popupMessage(Component parentComponent, ArrayList<String> errorStringList) {
        String s = "";
        if (errorStringList.isEmpty()) {
            s = "Successfully Submitted\n";
            JOptionPane.showMessageDialog(parentComponent, s, "Success Message", JOptionPane.INFORMATION_MESSAGE);
        } else {
            for (String e : errorStringList)
                s += e;
            JOptionPane.showMessageDialog(parentComponent, s, "You have following problems:", JOptionPane.ERROR_MESSAGE);
        }
    }

    // This returns Submit button and adds its handlers
    private JButton getSubmitButton(JTextArea textStatement) {
        JButton btn = new JButton("Submit");
        btn.setForeground(new Color(255, 255, 255));
        btn.setBackground(new Color(0, 0, 160));
        btn.addMouseListener(new MouseAdapter() {
            public void mousePressed(MouseEvent e) {
                ArrayList<Integer> idxList = new ArrayList<>();
                ArrayList<String> el = new ArrayList<String>();
                String s1;
                boolean isGraduate = false;
                int eidx = 1;

                s1 = textList.get(0).getText();
                if (s1.isEmpty())
                    el.add(eidx++ + ".You forgot to fill the name text field, Please fill it\n");
                else if (s1.split("[ ]+").length < 2)
                    el.add(eidx++ + ".You forgot to write your name or surname\n");

                s1 = textList.get(1).getText();
                if (s1.isEmpty())
                    el.add(eidx++ + ".You forgot to fill the birth date text field, Please fill it\n");
                else if (s1.split("[/]+").length != 3)
                    el.add(eidx++ + ".Birthdate must be in '06/06/1995' format\n");

                s1 = textList.get(2).getText();
                if (s1.isEmpty())
                    el.add(eidx++ + ".You forgot to fill the email text field, Please fill it\n");
                else if (s1.split("[@.]+").length != 3)
                    el.add(eidx++ + ".Email must be in example@some.some\n");

                s1 = textList.get(3).getText();
                if (s1.isEmpty())
                    el.add(eidx++ + ".You forgot to fill the degree text field, Please fill it\n");
                else if (!s1.equalsIgnoreCase("bachelor"))
                    isGraduate = true;

                s1 = textList.get(4).getText();
                if (s1.isEmpty())
                    el.add(eidx++ + ".You forgot to fill the email text field, Please fill it\n");
                else if (s1.split("[-]+").length != 3)
                    el.add(eidx++ + ".Proper format for a phone number is '10-2158-0222'\n");

                s1 = textList.get(5).getText();
                if (isGraduate && s1.isEmpty())
                    el.add(eidx++ + ".For graduate, you have to enter previous university\n");

                s1 = textList.get(6).getText();
                if (isGraduate && s1.isEmpty())
                    el.add(eidx++ + ".For graduate, you have to enter GPA\n");
                else if (isGraduate) {
                    double gpa = -1;
                    if (s1.matches("[+-]?[0-9]+|(([.][0-9]+)|([0-9]+[.])[0-9]*)")) //This is tricky floating point regular expression
                        gpa = Double.parseDouble(s1);
                    if (gpa < 0 || gpa > 4.5)
                        el.add(eidx++ + ".GPA must be between 0 and 4.5\n");
                }

                // Be ware this is not textList: because it's not textLabel
                s1 = textStatement.getText();
                if (s1.length() < 100)
                    el.add(eidx++ + ".Your Personal Statement must be at least 100 words\n");

                s1 = textList.get(7).getText();
                if (s1.isEmpty())
                    el.add(eidx++ + ".You forgot to fill the home address text field, Please fill it\n");

                s1 = textList.get(8).getText();
                if (!s1.equals("8"))
                    el.add(eidx++ + ".You should enter correct human check value\n");

                popupMessage(textStatement, el);
            }
        });
        return btn;
    }
}
