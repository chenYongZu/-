package HomeWork;

import javax.swing.*;

public class SetTimeLimit extends Thread{
    private static long totaltime;
    public  static long temptime;
    private String timetext,name;
    public  boolean exit;
    public SetTimeLimit(int x,long curtime,boolean exit){
        if(x==0) name = "黑方";
        else name = "白方";
        this.exit = exit;
        this.totaltime = curtime;
        this.temptime = totaltime;
        if(curtime==-2){
            timetext = name + "无时间限制";
        }
        else {
            timetext = name + "步数时间剩余：" + getTemptime()+ "秒";
        }
    }
    public void run(){
        while(temptime>=0 && !exit) {
            try {
                timetext = name + "步数时间剩余：" + getTemptime()+"秒";
                temptime--;
                UI.showtimetext.setText(timetext);
                Thread.sleep(1000);
            }catch (InterruptedException e){
                e.printStackTrace();
                return;
            }
        }
        if(temptime==-1 && !exit){
            JOptionPane.showMessageDialog(null, name + "超时，失败","游戏结束",JOptionPane.DEFAULT_OPTION);
            ChessBoard.patten = 0;
            UI.button[1].setEnabled(true);
            UI.button[3].setEnabled(false);
        }
        if(temptime==-2) UI.showtimetext.setText(timetext);
    }
    public long getTotaltime(){
        return this.totaltime;
    }
    public long getTemptime(){
        return this.temptime;
    }
    public void setTotaltime(long totaltime){
        this.totaltime = totaltime;
    }

}
