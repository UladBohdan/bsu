package by.bsu.famcs.uladbohdan.labs;

import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.border.Border;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.GeneralPath;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.util.*;

public class Lab13paint extends JFrame {

    public Lab13paint(String title) {
        super(title);
        UIManager.getCrossPlatformLookAndFeelClassName();
        setSize(600, 300);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setLayout(new GridBagLayout());
        add(new JScrollPane(drawPanel,
                        JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
                        JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED),
                new GridBagConstraints(0, 0, 1, 1, 1.0, 70.0,
                        GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));
        buttonRed = new JButton("Red");
        buttonGreen = new JButton("Green");
        buttonBlue = new JButton("Blue");
        setBold();
        JButton buttonSaveAsImage = new JButton("Save as image");
        JButton buttonSaveAsText = new JButton("Save as text");
        JButton buttonOpen = new JButton("Open");
        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new GridLayout(1, 6));
        buttonPanel.add(buttonRed);
        buttonPanel.add(buttonGreen);
        buttonPanel.add(buttonBlue);
        buttonPanel.add(buttonSaveAsImage);
        buttonPanel.add(buttonSaveAsText);
        buttonPanel.add(buttonOpen);
        add(buttonPanel, new GridBagConstraints(0, 1, 1, 1, 1.0, 1.0,
                GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(10, 10, 10, 10), 0, 0));

        buttonRed.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                curColor = Color.RED;
                setBold();
            }
        });
        buttonGreen.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                curColor = Color.GREEN;
                setBold();
            }
        });
        buttonBlue.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                curColor = Color.BLUE;
                setBold();
            }
        });
        buttonSaveAsImage.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                try {
                    JFileChooser fileChooser = new JFileChooser();
                    if (fileChooser.showSaveDialog(Lab13paint.this) == JFileChooser.APPROVE_OPTION) {
                        File file = fileChooser.getSelectedFile();
                        drawPanel.saveAsImage(file);
                    }
                } catch (Exception e) {
                    JOptionPane.showMessageDialog(Lab13paint.this, "Writing an image failed.");
                }
            }
        });
        buttonSaveAsText.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                try {
                    JFileChooser fileChooser = new JFileChooser();
                    if (fileChooser.showSaveDialog(Lab13paint.this) == JFileChooser.APPROVE_OPTION) {
                        File file = fileChooser.getSelectedFile();
                        drawPanel.saveAsText(file);
                    }
                } catch (Exception e) {
                    JOptionPane.showMessageDialog(Lab13paint.this, "Writing as a text failed.");
                }
            }
        });
        buttonOpen.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                try {
                    JFileChooser fileChooser = new JFileChooser();
                    if (fileChooser.showOpenDialog(Lab13paint.this) == JFileChooser.APPROVE_OPTION) {
                        File file = fileChooser.getSelectedFile();
                        drawPanel.openFromFile(file);
                    }
                } catch (Exception e) {
                    JOptionPane.showMessageDialog(Lab13paint.this, "Reading failed: file not found or has wrong format");
                }
            }
        });
    }

    public static void main(String[] args) {
        Lab13paint frame = new Lab13paint("Paint");
        frame.setVisible(true);
    }

    private void setBold() {
        buttonRed.setFont(buttonRed.getFont().deriveFont(Font.PLAIN));
        buttonBlue.setFont(buttonBlue.getFont().deriveFont(Font.PLAIN));
        buttonGreen.setFont(buttonGreen.getFont().deriveFont(Font.PLAIN));
        if (curColor.equals(Color.RED))
            buttonRed.setFont(buttonRed.getFont().deriveFont(Font.BOLD));
        else if (curColor.equals(Color.GREEN))
            buttonGreen.setFont(buttonGreen.getFont().deriveFont(Font.BOLD));
        else if (curColor.equals(Color.BLUE))
            buttonBlue.setFont(buttonBlue.getFont().deriveFont(Font.BOLD));
    }

    private DrawingPanel drawPanel = new DrawingPanel();
    private Color curColor = Color.RED;
    private JButton buttonRed, buttonGreen, buttonBlue;

    class DrawingPanel extends JPanel {
        public DrawingPanel() {
            super();
            points = new ArrayList<>();
            addMouseMotionListener(new MouseMotionAdapter() {
                @Override
                public void mouseDragged(MouseEvent e) {
                    super.mouseDragged(e);
                    tempPoints.add(new ColorPoint(e.getX(), e.getY(), Lab13paint.this.curColor));
                    points.add(new ColorPoint(e.getX(), e.getY(), Lab13paint.this.curColor));
                    drawOnline();
                }

            });
            addMouseListener(new MouseAdapter() {
                @Override
                public void mouseReleased(MouseEvent e) {
                    super.mouseReleased(e);
                    points.add(new ColorPoint(-1, -1, Color.WHITE));
                }
                @Override
                public void mousePressed(MouseEvent e) {
                    super.mousePressed(e);
                    tempPoints = new ArrayList<>();
                    tempPoints.add(new ColorPoint(e.getX(), e.getY(), Lab13paint.this.curColor));
                    points.add(new ColorPoint(e.getX(), e.getY(), Lab13paint.this.curColor));
                    drawOnline();
                }
            });
        }
        @Override
        public Dimension getPreferredSize() {
            return Toolkit.getDefaultToolkit().getScreenSize();
        }
        @Override
        public void paint(Graphics gTemp) {
            super.paintComponent(gTemp);
            Graphics2D g = (Graphics2D) gTemp;
            int start = 0, num = 0;
            for (ColorPoint i : points) {
                if (i.getX() == -1) {
                    polyline = new GeneralPath(GeneralPath.WIND_EVEN_ODD, num + 1);
                    polyline.moveTo(points.get(start).getX(), points.get(start).getY());
                    for (int j = start; j < start + num; j++) {
                        polyline.lineTo(points.get(j).getX(), points.get(j).getY());
                    }
                    g.setColor(points.get(start).getColor());
                    g.draw(polyline);

                    start += (num + 1);
                    num = 0;
                } else {
                    num++;
                }
            }
        }
        public void saveAsText(File file) throws Exception {
            FileWriter out = new FileWriter(file);
            out.write(Integer.toString(points.size()) + "\n");
            for (ColorPoint i : points) {
                out.write((int) i.getX() + " " + (int) i.getY() + " " + Integer.toString(i.getColor().getRGB()) + "\n");
            }
            out.close();
        }
        public void openFromFile(File file) throws Exception {
            Scanner in = new Scanner(file);
            int n = in.nextInt();
            points = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                points.add(new ColorPoint(in.nextInt(), in.nextInt(), new Color(in.nextInt())));
            }
            in.close();
            repaint();
        }
        public void saveAsImage(File file) throws Exception {
            BufferedImage bi = new BufferedImage(getWidth(), getHeight(), BufferedImage.TYPE_INT_RGB);
            paint(bi.getGraphics());
            ImageIO.write(bi, "JPEG", file);
        }
        private void drawOnline() {
            Graphics2D g = (Graphics2D) getGraphics();
            polyline = new GeneralPath(GeneralPath.WIND_EVEN_ODD, tempPoints.size());
            polyline.moveTo(tempPoints.get(0).getX(), tempPoints.get(0).getY());
            for (int j = 0; j < tempPoints.size(); j++)
                polyline.lineTo(tempPoints.get(j).getX(), tempPoints.get(j).getY());
            g.setColor(tempPoints.get(0).getColor());
            g.draw(polyline);
        }

        private ArrayList<ColorPoint> points;
        private ArrayList<ColorPoint> tempPoints;
        private GeneralPath polyline;
    }

    class ColorPoint extends Point {
        public ColorPoint(int x, int y, Color color) {
            super(x, y);
            this.color = color;
        }

        public void setColor(Color color) {
            this.color = color;
        }

        public Color getColor() {
            return color;
        }

        private Color color;
    }
}