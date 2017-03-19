package by.bsu.famcs.uladbohdan.labs;

import javax.swing.*;
import javax.swing.text.DefaultFormatterFactory;
import javax.swing.text.NumberFormatter;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.io.File;
import java.io.FileWriter;
import java.text.NumberFormat;
import java.util.*;

public class Lab15comparators extends JFrame {

    public Lab15comparators(String title) {
        super(title);
        setSize(300,450);
        setResizable(false);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        initMenu();
        listModel = new DefaultListModel<>();
        list = new JList<>(listModel);
        list.setFont(new Font("Ubuntu mono",Font.PLAIN,16));
        updateList();
        add(new JScrollPane(list,
                JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
                JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED));
    }

    private void initMenu() {
        JMenuBar menuBar = new JMenuBar();
        menuBar.setLayout(new BoxLayout(menuBar, BoxLayout.PAGE_AXIS));
        JMenuItem openItem = new JMenuItem("Open a file", KeyEvent.VK_O);
        menuBar.add(openItem);
        JMenuItem saveItem = new JMenuItem("Save as", KeyEvent.VK_S);
        menuBar.add(saveItem);
        JMenuItem addStudentItem = new JMenuItem("Add new student", KeyEvent.VK_A);
        menuBar.add(addStudentItem);
        setJMenuBar(menuBar);

        openItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {

                JFileChooser fileChooser = new JFileChooser();
                if (fileChooser.showOpenDialog(Lab15comparators.this)==JFileChooser.APPROVE_OPTION) {
                    File file = fileChooser.getSelectedFile();
                    try {
                        Scanner in = new Scanner(file);
                        int n = in.nextInt();
                        students.clear();
                        for (int i=0; i<n; i++) {
                            students.add(new Student(in.nextInt(), in.next(), in.nextInt(), in.nextInt()));
                        }
                        in.close();
                        updateList();
                    }
                    catch (Exception e) {
                        JOptionPane.showMessageDialog(Lab15comparators.this, "Reading from file failed.");
                    }
                }
            }
        });

        saveItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                JFileChooser fileChooser = new JFileChooser();
                if (fileChooser.showSaveDialog(Lab15comparators.this)==JFileChooser.APPROVE_OPTION) {
                    File file = fileChooser.getSelectedFile();
                    try {
                        FileWriter out = new FileWriter(file);
                        out.write(students.size()+"\n");
                        for (Iterator it = students.iterator(); it.hasNext(); ) {
                            out.write(it.next()+"\n");
                        }
                        out.close();
                    }
                    catch (Exception e) {
                        JOptionPane.showMessageDialog(Lab15comparators.this, "Writing to file failed.");
                    }
                }
            }
        });

        addStudentItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                JTextField idField = new JTextField();
                JTextField nameField = new JTextField();
                JTextField courseField = new JTextField();
                JTextField groupField = new JTextField();
                final JComponent[] inputs = new JComponent[] {
                        new JLabel("ID:"), idField,
                        new JLabel("Surname:"), nameField,
                        new JLabel("Course:"), courseField,
                        new JLabel("Group:"), groupField
                };
                if (JOptionPane.showConfirmDialog(Lab15comparators.this, inputs,
                        "Input new student", JOptionPane.OK_CANCEL_OPTION) == JOptionPane.YES_OPTION) {
                    try {
                        students.add(new Student(Integer.parseInt(idField.getText()),
                                nameField.getText(),
                                Integer.parseInt(courseField.getText()),
                                Integer.parseInt(groupField.getText()) ));
                        updateList();
                    } catch (NumberFormatException e) {
                        JOptionPane.showMessageDialog(Lab15comparators.this, "Wrong values.");
                    }
                }
            }
        });
    }

    private void updateList() {
        listModel.clear();
        if (students.isEmpty()) {
            listModel.addElement("<html><body><b>Nothing to show.");
            return;
        }
        Collections.sort(students, new NameComparator());
        ArrayList<Student> array = new ArrayList<>();
        for (int i=0; i<students.size(); i++) {
            String name = students.get(i).getName();
            if ( (i!=0 && students.get(i-1).getName().compareTo(name)==0) ||
                    (i!=students.size()-1 && students.get(i+1).getName().compareTo(name)==0) ) {
                array.add(students.get(i));
            }
        }
        if (array.isEmpty()) {
            listModel.addElement("<html><body><b>Nothing to show.");
            return;
        }
        Collections.sort(array);
        listModel.addElement("<html><body><b>" +
                "crs/gr&nbsp name&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp id");
        for (Iterator<Student> it = array.iterator(); it.hasNext(); ) {
            listModel.addElement(it.next().getFormattedString());
        }
    }

    public static void main(String[] args) {
        Lab15comparators frame = new Lab15comparators("Students");
        frame.setVisible(true);
    }

    private ArrayList<Student> students = new ArrayList<>();
    private DefaultListModel<String> listModel;
    private JList<String> list;

    class NameComparator implements Comparator<Student> {
        @Override
        public int compare(Student st1, Student st2) {
            return st1.getName().compareTo(st2.getName());
        }
    }

    class Student implements Comparable<Student> {
        public Student(int id, String name, int course, int group) {
            this.id = id;
            this.name = name;
            this.group = group;
            this.course = course;
        }
        public String getFormattedString() {
            StringBuilder sb = new StringBuilder();
            Formatter formatter = new Formatter(sb);
            formatter.format("%-3d %-3d %-18s %-6d",course,group,name,id);
            return sb.toString();
        }
        public int getId() {
            return id;
        }
        public int getGroup() {
            return group;
        }
        public int getCourse() {
            return course;
        }
        public String getName() {
            return name;
        }
        @Override
        public int compareTo(Student st) {
            int cmp;
            cmp = Integer.compare(course, st.getCourse());
            if (cmp!=0)
                return cmp;
            cmp = Integer.compare(group, st.getGroup());
            if (cmp!=0)
                return cmp;
            cmp = name.compareTo(st.getName());
            if (cmp!=0)
                return cmp;
            return Integer.compare(id, st.getId());
        }
        @Override
        public String toString() {
            return id+" "+name+" "+course+" "+group;
        }
        private int id, group, course;
        private String name;
    }
}
