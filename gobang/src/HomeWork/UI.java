package HomeWork;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class UI {
    private static int BLACK = 1;
    private static int WHITE = 0;
    private final static int buttonwidth = 140; //主界面按钮宽度
    private final static int buttonheight = 55; //主界面按钮高度
    public static int chessboardwidth;   //棋盘宽度
    public static int chessboardheight; // 棋盘高度
    public static Font font = new Font("宋体",Font.BOLD,20);
    private String[] buttonname;   // 主界面上所有按钮名称
    public static JFrame mainframe; // 主界面
    private ImageIcon background; // 背景图片
    private JLabel showbackground;
    public static ButtonStyle[] button; // 主界面所有按钮
    public static int chosenpattern;//0代表初始；1代表人机；2代表双人
    public static Dimension dimension; // 获得窗口大小
    public static JPanel jpanel,blist;
    public static ChessBoard drawchessboard;
    public static long time;
    public static JTextField showtimetext;
    void init(){
        mainframe = new JFrame("五子棋");
        jpanel = (JPanel) mainframe.getContentPane();
        jpanel.setOpaque(false);
        time = -2;
        setBackGround();
        mainframe.setSize(background.getIconWidth(),background.getIconHeight());
        dimension = mainframe.getSize();

        chessboardwidth = (int)dimension.getWidth()/1000*100;
        chessboardheight = (int)dimension.getHeight()/900*155;
        drawchessboard = new ChessBoard(chosenpattern);
        jpanel.add(drawchessboard);

        showtimetext = new JTextField(10);
        jpanel.add(showtimetext);
        showtimetext.setBorder(null);
        showtimetext.setOpaque(false);
        showtimetext.setBounds(dimension.width/3,dimension.height/100*87,dimension.width/3,70);
        showtimetext.setEditable(false);
        showtimetext.setFont(font);

        setButtonList();
        mainframe.setResizable(false);
        mainframe.setVisible(true);  //窗口可见
        mainframe.setLocationRelativeTo(null); //窗口显示在屏幕中央
        mainframe.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
    }
    public void setBackGround(){
        background = new ImageIcon("resource/BackGround.jpg");
        background.getImage().getScaledInstance(background.getIconWidth(),background.getIconHeight(),Image.SCALE_DEFAULT);
        showbackground = new JLabel(background);
        showbackground.setBounds(0,0,background.getIconWidth(),background.getIconHeight());
        mainframe.getLayeredPane().setLayout(null);
        mainframe.getLayeredPane().add(showbackground,new Integer(Integer.MIN_VALUE));
    }

    public void setButtonList(){
        int bwidth = (int)dimension.getWidth();
        int bheight = (int)dimension.getHeight();
        buttonname = new String[]{"开始游戏","时间设置","游戏说明","认输","关于","退出"};
        button = new ButtonStyle[6];
        blist = new JPanel();
        jpanel.add(blist);
        blist.setLayout(null);
        blist.setOpaque(false);

        for(int i=0,x=0;i<6;i++,x++){
            button[i] = new ButtonStyle(buttonname[i]);
            button[i].setMargin(new Insets(0,0,0,0));
            button[i].setBounds(0,0,buttonwidth,buttonheight);
            if(i==3) x++;
            button[i].setLocation(bwidth/10*8,bheight/9*(x+1));
            blist.add(button[i]);
        }
        button[3].setEnabled(false);
        button[0].setEnabled(false);
        setButtonListener();
    }

    public void setButtonListener(){
        //游戏开始按钮的功能实现
        button[0].addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                new PlayDialog("选择对战模式").play.setVisible(true);//弹出选择对战模式
                chosenpattern = 0;   //初始化
            }
        });
        //游戏设置按钮的功能实现
        button[1].addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                new SettingDialog("游戏设置").play.setVisible(true);
            }
        });
        //游戏说明按钮的功能实现
        button[2].addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String instructiontext = "   默认黑棋先手，默认无时间限制。对局双方各执一色棋子。空棋盘开局。黑先、白后，交替下子，每次只能下一子。棋子下在棋盘的空白点上，棋子下定后，不得向其它点移动，不得从棋盘上拿掉或拿起另落别处。黑方的第一枚棋子可下在棋盘任意交叉点上。轮流下子是双方的权利，但允许任何一方放弃下子权（即：PASS权）,超时方为负。横,竖,斜,任意连成五个子的直线.同时阻止对手连成直线.最先连成五子直线胜。";
                JTextArea instruction = new JTextArea(10,45);
                instruction.setText(instructiontext);
                instruction.setOpaque(false);
                instruction.setFont(new Font("宋体",Font.BOLD,30));//设置字体
                instruction.setWrapStyleWord(true);//自动换行
                instruction.setLineWrap(true);
                instruction.setEditable(false); //不可编辑
                JOptionPane showinstruction = new JOptionPane();
                showinstruction.showMessageDialog(mainframe,instruction,"游戏说明",JOptionPane.DEFAULT_OPTION);
            }
        });
        //认输按钮的功能实现
        button[3].addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JLabel result = new JLabel();
                if(ChessBoard.flag){
                    result.setText("黑方认输，白方胜利");
                }
                else{
                    result.setText("白方认输，黑方胜利");
                }
                button[1].setEnabled(true);
                JOptionPane.showMessageDialog(null,result,"游戏结束",JOptionPane.DEFAULT_OPTION);
                button[3].setEnabled(false);
            }
        });
        //关于按钮的功能实现
        button[4].addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JOptionPane.showMessageDialog(null,"  游戏版本：1.0.0.11.18_beta","关于",JOptionPane.DEFAULT_OPTION);
            }
        });
        //退出按钮的功能实现
        button[5].addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int chose = JOptionPane.showConfirmDialog(null,"你确定要退出吗？","退出游戏",JOptionPane.YES_NO_OPTION);
                if(chose==JOptionPane.YES_OPTION) System.exit(0);
            }
        });
    }
}
