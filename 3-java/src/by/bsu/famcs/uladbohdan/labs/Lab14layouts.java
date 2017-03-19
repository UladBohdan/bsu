package by.bsu.famcs.uladbohdan.labs;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Lab14layouts extends JFrame {

    public Lab14layouts(String title) {
        super(title);
        try {
         //   UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
            UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());
        } catch (Exception e) {
            JOptionPane.showMessageDialog(this, "Setting appropriate Look and Feel failed.");
        }
        setSize(520,500);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        JTabbedPane tabbedPane = new JTabbedPane();
        tabbedPane.addTab("Lists", new Card1());
        tabbedPane.addTab("Buttons", new Card2());
        tabbedPane.addTab("Radio Group", new Card3());
        add(tabbedPane);
    }

    class Card1 extends JPanel {
        public Card1() {
            setLayout(new BorderLayout());

            JPanel central = new JPanel();
            central.setLayout(new BorderLayout());
            JButton right = new JButton("->");
            central.add(right, BorderLayout.NORTH);
            JButton left = new JButton("<-");
            central.add(left, BorderLayout.SOUTH);
            add(central, BorderLayout.CENTER);

            DefaultListModel<String> leftListModel = new DefaultListModel<>();
            JList<String> leftList = new JList<>(leftListModel);
            leftList.setFont(new Font(getFont().getFontName(), Font.PLAIN, 26));
            add(new JScrollPane(leftList,
                    JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
                    JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED), BorderLayout.WEST);
            DefaultListModel<String> rightListModel = new DefaultListModel<>();
            JList<String> rightList = new JList<>(rightListModel);
            rightList.setFont(new Font(getFont().getFontName(), Font.PLAIN, 26));
            add(new JScrollPane(rightList,
                    JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
                    JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED), BorderLayout.EAST);

            final String[] strings = new String[] {     "abstract","continue","for","new","switch","default",
                    "package","synchronized","boolean","do","if","private","this","break","double","implements",
                    "protected","throw","byte","else","import","public","throws","case","instanceof","return",
                    "transient","catch","extends","int","short","try","char","final","interface","static","void",
                    "class","finally","long","volatile","float","native","super","while"
            };
            for (String i: strings) {
                leftListModel.addElement(i);
            }
            // usual listeners are replaced with Lambda expressions below:
            right.addActionListener(e -> {
                if (!leftList.isSelectionEmpty()) {
                    rightListModel.addElement(leftList.getSelectedValue());
                    leftListModel.remove(leftList.getSelectedIndex());
                }
            });
            left.addActionListener(e -> {
                if (!rightList.isSelectionEmpty()) {
                    leftListModel.addElement(rightList.getSelectedValue());
                    rightListModel.remove(rightList.getSelectedIndex());
                }
            });
        }
    }

    class Card2 extends JPanel implements MouseListener {
        public Card2() {
            setLayout(new GridLayout(N,N));
            for (int i = 0; i < N; i++)
                for (int j=0; j<N; j++) {
                    JButton temp = new JButton();
                    temp.setText(Integer.toString(i*N+j+1));
                    temp.addMouseListener(this);
                    add(temp);
                }
        }
        @Override
        public void mouseEntered(MouseEvent e) {
            defBtnColor = ((JButton) e.getSource()).getBackground();
            ((JButton) e.getSource()).setBackground(Color.RED);
        }
        @Override
        public void mouseExited(MouseEvent e) {
            ((JButton) e.getSource()).setBackground(defBtnColor);
        }
        @Override
        public void mousePressed(MouseEvent e) {
            if (e.getButton()==MouseEvent.BUTTON1) {
                tempText = ((JButton) e.getSource()).getText();
                ((JButton) e.getSource()).setText("Clicked!");
            }
        }
        @Override
        public void mouseReleased(MouseEvent e) {
            if (e.getButton()==MouseEvent.BUTTON1)
                ((JButton) e.getSource()).setText(tempText);
        }
        @Override
        public void mouseClicked(MouseEvent e) {
        }
        private static final int N = 5;
        private String tempText;
        private Color defBtnColor;
    }

    class Card3 extends JPanel {
        public Card3() {
            setBackground(new Color(175,238,238));
            ButtonGroup radioGroup = new ButtonGroup();
            final String[] districts = new String[] {
                    "Homiel", "Harodnia", "Berasce", "Vicebsk", "Mahiliou", "Minsk" };
            final ImageIcon[] icons = new ImageIcon[] {
                    new ImageIcon("flags/AQ.png"),
                    new ImageIcon("flags/_basque-country.png"),
                    new ImageIcon("flags/AS.png"),
                    new ImageIcon("flags/AU.png"),
                    new ImageIcon("flags/BN.png")
            };
            Font font = new Font(getFont().getName(), Font.BOLD, 30);
            for (String i : districts) {
                JRadioButton temp = new JRadioButton(i);
                temp.setFont(font);
                temp.setIcon(icons[0]);
                temp.setSelectedIcon(icons[1]);
                temp.setDisabledIcon(icons[2]);
                temp.setRolloverIcon(icons[3]);
                temp.setPressedIcon(icons[4]);
                radioGroup.add(temp);
                add(temp);
            }
        }
    }

    public static void main(String[] args) {
        Lab14layouts frame = new Lab14layouts("Layouts");
        frame.setVisible(true);
    }
}
