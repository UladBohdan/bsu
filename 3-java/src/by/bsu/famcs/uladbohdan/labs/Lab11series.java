package by.bsu.famcs.uladbohdan.labs;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

public class Lab11series extends JFrame {

    Lab11series(String title) {
        super(title);
        init();
    }

    public static void main(String[] args) {
        Lab11series frame = new Lab11series("Series");
        frame.setSize(700,150);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
        return;
    }

    private void init() {
        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(4,1));
        JPanel p1 = new JPanel();
        p1.setLayout(new GridLayout(1,6));
        JLabel labelFirst = new JLabel("First:");
        JLabel labelStep = new JLabel("Step:");
        JLabel labelNumber = new JLabel("Element(s):");
        textNumber = new JTextField("2");
        textFirst = new JTextField("2");
        textStep = new JTextField("2");
        p1.add(labelFirst);
        p1.add(textFirst);
        p1.add(labelStep);
        p1.add(textStep);
        p1.add(labelNumber);
        p1.add(textNumber);
        panel.add(p1);
        JPanel p2 = new JPanel();
        radioLin = new JRadioButton("Linear");
        radioExp = new JRadioButton("Exponential");
        radioLin.doClick();
        ButtonGroup group = new ButtonGroup();
        group.add(radioLin);
        group.add(radioExp);
        p2.add(radioLin);
        p2.add(radioExp);
        panel.add(p2);
        JPanel p3 = new JPanel();
        p3.setLayout(new GridLayout(1,5));
        buttonJ = new JButton("Count i element");
        buttonSum = new JButton("Count sum");
        buttonFile = new JButton("Elements to a file");
        textFile = new JTextField("file.txt");
        buttonList = new JButton("Get first elements");
        p3.add(buttonJ);
        p3.add(buttonSum);
        p3.add(buttonFile);
        p3.add(textFile);
        p3.add(buttonList);
        panel.add(p3);
        areaAnswer = new JTextArea();
        areaAnswer.setEditable(false);
        areaAnswer.setLineWrap(true);
        areaAnswer.setWrapStyleWord(true);
        panel.add(areaAnswer);
        add(panel);

        buttonJ.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                try {
                    double first = Double.parseDouble(textFirst.getText());
                    double step = Double.parseDouble(textStep.getText());
                    if (radioLin.isSelected())
                        series = new LinearSeries(first, step);
                    else
                        series = new ExponentialSeries(first, step);
                    int j = Integer.parseInt(textNumber.getText());
                    if (j<=0)
                        throw new NumberFormatException();
                    areaAnswer.setText("Element "+j+" is "+series.getElement(j));
                    return;
                }
                catch (NumberFormatException e) {
                    areaAnswer.setText("Wrong values in text fields");
                }
            }
        });

        buttonSum.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                try {
                    double first = Double.parseDouble(textFirst.getText());
                    double step = Double.parseDouble(textStep.getText());
                    if (radioLin.isSelected())
                        series = new LinearSeries(first, step);
                    else
                        series = new ExponentialSeries(first, step);
                    int j = Integer.parseInt(textNumber.getText());
                    if (j<=0)
                        throw new NumberFormatException();
                    series.setNumber(j);
                    areaAnswer.setText("Sum of the first "+j+" elements is "+series.getSum());
                    return;
                }
                catch (NumberFormatException e) {
                    areaAnswer.setText("Wrong values in text fields");
                }
            }
        });

        buttonFile.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                try {
                    double first = Double.parseDouble(textFirst.getText());
                    double step = Double.parseDouble(textStep.getText());
                    if (radioLin.isSelected())
                        series = new LinearSeries(first, step);
                    else
                        series = new ExponentialSeries(first, step);
                    int j = Integer.parseInt(textNumber.getText());
                    if (j<=0)
                        throw new NumberFormatException();
                    series.setNumber(j);
                    String fileName = textFile.getText();
                    series.saveToFile(fileName);
                    areaAnswer.setText("Successfully written into a file "+fileName);
                    return;
                }
                catch (NumberFormatException e) {
                    areaAnswer.setText("Wrong values in text fields");
                }
                catch (IOException w) {
                    areaAnswer.setText("Failed writing to file");
                }
            }
        });

        buttonList.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                try {
                    double first = Double.parseDouble(textFirst.getText());
                    double step = Double.parseDouble(textStep.getText());
                    if (radioLin.isSelected())
                        series = new LinearSeries(first, step);
                    else
                        series = new ExponentialSeries(first, step);
                    int j = Integer.parseInt(textNumber.getText());
                    if (j<=0)
                        throw new NumberFormatException();
                    series.setNumber(j);
                    areaAnswer.setText("First "+j+" elements: "+series);
                    return;
                }
                catch (NumberFormatException e) {
                    areaAnswer.setText("Wrong values in text fields");
                }
            }
        });
    }

    private JTextArea areaAnswer;
    private JButton buttonJ, buttonSum, buttonFile, buttonList;
    private JTextField textFile, textFirst, textNumber, textStep;
    private JRadioButton radioLin, radioExp;

    private Series series;
}
