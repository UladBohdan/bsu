package uladbohdan.finaltest;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import java.awt.*;
import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.TreeSet;

public class FinalTask extends JFrame {

    public FinalTask(String title) {
        super(title);
        setSize(600,300);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setLayout(null);
        JMenuBar menuBar = new JMenuBar();
        JMenuItem openWet = new JMenuItem("Open wet cleaners");
        menuBar.add(openWet);
        JMenuItem openRobot = new JMenuItem("Open robot cleaners");
        menuBar.add(openRobot);
        setJMenuBar(menuBar);

        items = new ArrayList<>();

        setLayout(new GridLayout(2,3));
        listModelElements = new DefaultListModel<>();
        listElements = new JList<>(listModelElements);
        listModelColors = new DefaultListModel<>();
        listColors = new JList<>(listModelColors);
        add(new JScrollPane(listElements,
                JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
                JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED));
        imagePanel = new JPanel();
        imageLabel = new JLabel();
        imagePanel.add(imageLabel);
        add(imagePanel);
        add(new JScrollPane(listColors,
                JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
                JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED));
        showUniqueBrands = new JButton("Show unique brands");
        showByColorsBtn = new JButton("Show with chosen color");
        colorInput = new JTextField();
        add(showUniqueBrands);
        add(colorInput);
        add(showByColorsBtn);

        openWet.addActionListener(e -> {
            try {
                Scanner in = new Scanner(new File(fileWetCleaners));
                int n = in.nextInt();
                items.clear();
                for (int i = 0; i < n; i++) {
                    items.add(new WetCleaner(in.next(), in.next(), in.nextInt(), in.next(), in.nextInt()));
                }
                listModelElements.clear();
                listModelColors.clear();
                colorInput.setText("");
                imageLabel.setIcon(null);
                for (Cleaner i : items) {
                    listModelElements.addElement(i.toString());
                }
            } catch (Exception exc) {
              JOptionPane.showMessageDialog(FinalTask.this, "Reading failed: file not found or has wrong format");
            }
        });

        openRobot.addActionListener(e -> {
            try {
                Scanner in = new Scanner(new File(fileRobotCleaners));
                int n = in.nextInt();
                items.clear();
                for (int i=0; i<n; i++) {
                    items.add(new RobotCleaner(in.next(), in.next(), in.nextInt(), in.next(), in.next()=="TRUE"));
                }
                in.close();
                listModelElements.clear();
                listModelColors.clear();
                colorInput.setText("");
                imageLabel.setIcon(null);
                for (Cleaner i : items) {
                    listModelElements.addElement(i.toString());
                }
            } catch (Exception exc) {
                JOptionPane.showMessageDialog(FinalTask.this, "Reading failed: file not found or has wrong format");
            }
        });

        showUniqueBrands.addActionListener(e -> {
            TreeSet<String> set = new TreeSet<>();
            for (Cleaner i : items) {
                set.add(i.getBrand());
            }
            listModelColors.clear();
            for (String i : set) {
                listModelColors.addElement(i);
            }
        });

        showByColorsBtn.addActionListener(e -> {
            String curColor = colorInput.getText();
            listModelColors.clear();
            for (Cleaner i : items) {
                if (i.getColor().equals(curColor)) {
                    listModelColors.addElement(i.getBrand());
                }
            }
        });

        listElements.addListSelectionListener(new ListSelectionListener() {
            @Override
            public void valueChanged(ListSelectionEvent e) {
                int n = listElements.getSelectedIndex();
                if (items.get(n).getImagePath()!=null) {
                    imageLabel.setIcon(new ImageIcon(items.get(n).getImagePath()));
                }
            }
        });

    }

    public static void main(String[] args) {
        FinalTask frame = new FinalTask("CLEANERS");
        frame.setVisible(true);
    }

    protected ArrayList<Cleaner> items;
    private static String fileWetCleaners = "./testResources/wetCleaners.txt", fileRobotCleaners = "./testResources/robotCleaners.txt";
    private JList<String> listElements, listColors;
    private DefaultListModel<String> listModelElements, listModelColors;
    private JPanel imagePanel;
    private JTextField colorInput;
    private JLabel imageLabel;
    private JButton showByColorsBtn, showUniqueBrands;
}
