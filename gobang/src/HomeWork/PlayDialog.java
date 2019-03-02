package HomeWork;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import static HomeWork.UI.drawchessboard;
import static HomeWork.UI.jpanel;

public class PlayDialog {
    JDialog play = new JDialog();
    public PlayDialog(String name){
        JRadioButton pvp,pvc;
        ButtonGroup group = new ButtonGroup();
        JPanel checkpanel = new JPanel();
        ButtonStyle check = new ButtonStyle("确认");
        Box box = Box.createVerticalBox();

        play.setTitle(name);
        play.setModal(true);
        play.setLocationRelativeTo(null);
        play.setSize((int)UI.dimension.getWidth()/4,(int)UI.dimension.getHeight()/4);

        check.setLocation(100,100);
        pvc = new JRadioButton("人机对战",true);
        pvp = new JRadioButton("双人对战",true);
        pvc.setFont(UI.font);
        pvp.setFont(UI.font);
        //group.add(pvc);
        group.add(pvp);
        //box.add(Box.createVerticalStrut(10));
        //box.add(pvc);
        box.add(Box.createVerticalStrut(20));
        box.add(pvp);
        box.add(Box.createVerticalStrut(20));
        box.add(check);
        checkpanel.add(box);
        play.add(checkpanel);
        play.setResizable(false);
        check.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e){
                /*
                if(pvc.isSelected()){
                    UI.chosenpattern = 1;
                    ChessBoard.patten = 1;
                }
                */
                if(pvp.isSelected()){
                    UI.chosenpattern = 2;
                }
                UI.drawchessboard = new ChessBoard(UI.chosenpattern);
                jpanel.add(drawchessboard);
                UI.drawchessboard.repaint();
                UI.button[0].setEnabled(false);
                UI.button[1].setEnabled(false);
                UI.button[3].setEnabled(true);
                play.dispose();
            }
        });
    }
}
