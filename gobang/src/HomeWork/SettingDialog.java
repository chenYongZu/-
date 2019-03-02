package HomeWork;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SettingDialog {
    JDialog play = new JDialog();
    public SettingDialog(String name){
        JRadioButton notimelimit,other;
        ButtonGroup group = new ButtonGroup();
        JPanel checkpanel = new JPanel();
        ButtonStyle check = new ButtonStyle("确认");
        Box box = Box.createVerticalBox();
        JTextField timetext = new JTextField();
        timetext.setEnabled(false);
        timetext.setFont(UI.font);
        play.setTitle(name);
        play.setModal(true);
        play.setLocationRelativeTo(null);
        play.setSize((int)UI.dimension.getWidth()/4,(int)UI.dimension.getHeight()/4);

        check.setLocation(100,100);
        notimelimit = new JRadioButton("无时间限制",true);
        other = new JRadioButton("自定义时间(秒)",false);
        notimelimit.setFont(UI.font);
        other.setFont(UI.font);
        group.add(notimelimit);
        group.add(other);
        box.add(Box.createVerticalStrut(10));
        box.add(notimelimit);
        box.add(Box.createVerticalStrut(10));
        box.add(other);
        box.add(Box.createVerticalStrut(10));
        box.add(timetext);
        box.add(Box.createVerticalStrut(10));
        box.add(check);
        checkpanel.add(box);
        play.add(checkpanel);
        play.setResizable(false);
        other.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (other.isSelected()) {
                    timetext.setEnabled(true);
                }
            }
        });
        notimelimit.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(notimelimit.isSelected()){
                    timetext.setText("");
                    timetext.setEnabled(false);
                }
            }
        });
        check.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e){
                UI.button[1].setEnabled(false);
                UI.button[0].setEnabled(true);
                String changetime = timetext.getText();
                if(other.isSelected()) {
                    if (!isNumber(changetime) || (changetime.length()==1 && Integer.parseInt(changetime) == 0)) {
                        JOptionPane.showMessageDialog(null, "  请输入一个正整数代表秒数", "出错了", JOptionPane.ERROR_MESSAGE);
                    } else {
                        UI.time = (long) Integer.parseInt(changetime);//获得设置的秒数
                         play.dispose();
                    }
                }
                else{
                    UI.time = -2;//如果没有时间限制，则是-2
                    play.dispose();
                }
            }
        });
    }
    //判断输入的是否是数字
    public boolean isNumber(String s){
        if(s.length()==0) return false;
        for(int i=s.length();--i>=0;){
            int chr=s.charAt(i);
            if(chr<48 || chr>57)  return false;
        }
        return true;
    }
}

