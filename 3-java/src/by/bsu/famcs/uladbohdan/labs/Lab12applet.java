package by.bsu.famcs.uladbohdan.labs;

import javax.swing.*;
import java.awt.event.*;

public class Lab12applet extends JApplet {

    public Lab12applet() {
        setLayout(null);
        btn = new JButton("button");
        btn.setHorizontalAlignment(SwingConstants.CENTER);
        btn.setVerticalAlignment(SwingConstants.CENTER);
        btn.setBounds(200,200,100,100);
        add(btn);

        btn.addMouseMotionListener(new MouseAdapter() {
            @Override
            public void mouseMoved(MouseEvent e) {
                tempX = e.getX();
                tempY = e.getY();
                showStatus("x: "+(e.getX()+btn.getX())+", y: "+(e.getY()+btn.getY()));
            }

            @Override
            public void mouseDragged(MouseEvent e) {
                showStatus("x: " + (e.getX() + btn.getX()) + ", y: " + (e.getY() + btn.getY()));
                if (e.isControlDown())
                    btn.setLocation(btn.getX() + e.getX() - tempX, btn.getY() + e.getY() - tempY);
            }

            private int tempX, tempY;
        });

        addMouseMotionListener(new MouseAdapter() {
            @Override
            public void mouseMoved(MouseEvent e) {
                showStatus("x: "+e.getX()+", y: "+e.getY());
            }

            @Override
            public void mouseDragged(MouseEvent e) {
                showStatus("x: "+e.getX()+", y: "+e.getY());
            }
        });

        addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                btn.setLocation(e.getX(), e.getY());
            }
        });

        btn.addKeyListener(new KeyAdapter() {
            @Override
            public void keyTyped(KeyEvent e) {
                if (e.getKeyChar()==KeyEvent.VK_BACK_SPACE) {
                    if (btn.getText().length()>0)
                        btn.setText(btn.getText().substring(0,btn.getText().length()-1));
                }
                else
                    btn.setText(btn.getText()+Character.toString(e.getKeyChar()));
            }
        });

    }

    private JButton btn;
}
