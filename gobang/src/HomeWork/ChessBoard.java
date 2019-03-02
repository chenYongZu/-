package HomeWork;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class ChessBoard extends JPanel{
    private static int BLACK = 1;
    private static int WHITE = 0;
    private static int num = 16; //棋盘线条横竖各个数目
    private static int span = 38;//棋盘两个线条之间的间隔
    private static int len = num * span; //棋盘的宽度以及高度
    private static int eps  = span/2-5; //鼠标点击时误差范围
    public static int patten; //游戏模式
    public static ChessMan[][] chessStatus; //储存棋子的类
    public static boolean flag; //实现黑白棋交替
    public static int temp;
    public static SetTimeLimit showblacktime,showwhitetime;
    /*判断是否取得胜利横竖坐标走向，右，下，右下，左下*/
    private static final int[] dx = new int[]{1,0,-1,1};
    private static final int[] dy = new int[]{0,-1,-1,-1};
    /*实现画棋盘，刷新棋盘，下棋*/
    public ChessBoard(int patten) {
        this.patten = patten;
        flag = true;
        setBounds(UI.chessboardwidth, UI.chessboardheight, len, len); //棋盘位置以及大小
        setBackground(new Color(143, 91, 29));//棋盘颜色
        chessStatus = new ChessMan[num+1][num+1]; //棋子

        showblacktime = new SetTimeLimit(BLACK,UI.time,false);
        showwhitetime = new SetTimeLimit(WHITE,UI.time,false);

        /*获得鼠标点击的坐标定位棋子位置，以及刷新画棋子，棋盘线条*/
        this.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                super.mousePressed(e);
                int leftx = getWidth();
                int x = e.getX();  //鼠标点击横坐标
                int y = e.getY(); //鼠标点击纵坐标
                int px=0,py=0;    //棋子位置

                if(ChessBoard.patten!=0) { //获得棋子位置坐标
                    for (int i = 1; i < num; i++) {
                        if (i * span - eps <= x && x <= i * span + eps) px = i;
                        if (i * span - eps <= y && y <= i * span + eps) py = i;
                    }
                }
                //实现棋子交替下
                if(px!=0 && py!=0){
                    if(flag){
                        temp = 1;
                        flag = false;
                    } else {
                        flag = true;
                        temp = 0;
                    }

                    ChessMan chessman = new ChessMan(temp,true);

                    //如果该位置未被棋子占用，则准许在此放棋子
                    if(chessStatus[px][py]==null) {
                        chessStatus[px][py] = chessman;
                        repaint(); //刷新棋盘
                    }

                    if(checkwinner(BLACK)){ //判断黑棋是否已经胜利
                        setStatus();
                        JOptionPane.showMessageDialog(null,"  黑方胜利","游戏结束",JOptionPane.DEFAULT_OPTION);
                        ChessBoard.patten  = 0;

                    }
                    else if(checkwinner(WHITE)){ //判断白棋是否已经胜利
                        setStatus();
                        JOptionPane.showMessageDialog(null,"  白方胜利","游戏结束",JOptionPane.DEFAULT_OPTION);
                        ChessBoard.patten  = 0;
                    }
                    if(temp==1){
                        //if(showwhitetime.isAlive()) showwhitetime.stop();
                        showblacktime = new SetTimeLimit(BLACK,UI.time,false);
                        showblacktime.start();
                        showwhitetime.exit = true;
                        showwhitetime.interrupt();
                    }
                    else if(temp==0) {
                        showwhitetime = new SetTimeLimit(WHITE,UI.time,false);
                        showwhitetime.start();
                        showblacktime.exit = true;
                        showblacktime.interrupt();
                    }
                }
            }
        });
    }
    @Override
    /*画棋子实现方法*/
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        setBounds(UI.chessboardwidth, UI.chessboardheight, len, len); //棋盘位置以及大小
        float[] f = new float[]{0f, 1f};
        Color[] white = new Color[]{Color.WHITE, Color.BLACK};
        Color[] black = new Color[]{Color.BLACK, Color.WHITE};
        RadialGradientPaint paint;
        /*画棋盘线条*/
        for (int i = 1; i < num; i++) {
            g.drawLine(span, i * span, len - span, i * span);
            g.drawLine(i * span, span, i * span, len - span);
        }
        /*刷新棋局*/
        if (patten != 0){
            for (int i = 1; i < num; i++) {
                for (int j = 1; j < num; j++) {
                    if (chessStatus[i][j] != null && chessStatus[i][j].getIsplaced() == true) {
                        //chessStatus[i][j].setIsplaced(false);
                        int x = i * span;
                        int y = j * span;
                        if (chessStatus[i][j].getColor() == 1) {
                            paint = new RadialGradientPaint(x - span / 2f, y - span / 2f, 80f, f, black);
                        } else{
                            paint = new RadialGradientPaint(x - span / 2f, y - span / 2f, 120f, f, white);
                        }
                        ((Graphics2D) g).setPaint(paint);
                        ((Graphics2D) g).fillOval(x - span / 2, y - span / 2, span - 5, span - 5);
                    }
                }
            }
        }
    }
    public void setStatus() {
        showwhitetime.exit = true;
        showblacktime.exit = true;
        temp = 3;
        showwhitetime.interrupt();
        showblacktime.interrupt();
        UI.button[1].setEnabled(true);
        UI.button[3].setEnabled(false);
    }
    /*判断胜利的算法*/
    public boolean checkwinner(int x){
        for(int i=1;i<num;i++){
            for(int j=1;j<num;j++){
                if(chessStatus[i][j] != null && chessStatus[i][j].getIsplaced() == true)
                    if(chessStatus[i][j].getColor()==x)
                        if(getcheckwinner(i,j,x)) return true;
            }
        }
        return false;
    }
    public boolean getcheckwinner(int i,int j,int x){
        for(int k=0;k<4;k++){
            int xx=i,yy=j,sum=1;
            while(sum<=5){
                xx+=dx[k];
                yy+=dy[k];
                if(getcheck(xx,yy,x)==false) break;
                sum++;
            }
            if(sum>=5) return true;
        }
        return false;
    }
    public boolean getcheck(int i,int j,int x){
        if(i<1 || i>=num || j<1 || j>=num) return false;
        if(chessStatus[i][j] != null && chessStatus[i][j].getIsplaced() == true && chessStatus[i][j].getColor()==x) return true;
        return false;
    }
}