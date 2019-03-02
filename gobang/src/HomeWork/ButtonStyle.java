package HomeWork;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.geom.RoundRectangle2D;
/*美化界面按钮的类*/
public class ButtonStyle extends JButton {
    private boolean flag;
    public ButtonStyle(String name){
            this.setText(name);
            setFont(UI.font);
            setBorderPainted(false); //去除边框
            setContentAreaFilled(false); //设置为透明按钮
            setFocusPainted(false);//去掉点击按钮时文字周围的框
        addMouseListener(new MouseAdapter() {
                @Override
                public void mouseEntered(MouseEvent e) {
                    flag = true;
                    repaint();
                }
                @Override
                public void mouseExited(MouseEvent e){
                    flag = false;
                    repaint();
                }
            });
        }
        @Override
        protected void paintComponent(Graphics g){
            int w = getWidth();
            int h = getHeight();
            Graphics2D g2d = (Graphics2D)g.create();
            float tran = 1F;
            if (!flag) {
                tran = 0.5F;
            }
            g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
            GradientPaint p1;
            GradientPaint p2;
            if (getModel().isPressed()) {
                //按下按钮时上下边缘变化
                p1 = new GradientPaint(0, 0, new Color(0, 0, 0), 0, h -1, new Color(100, 100, 100));
                p2 = new GradientPaint(0, 1, new Color(0, 0, 0, 50), 0, h - 3,new Color(255, 255, 255, 100));
            } else {
                //松开按钮边缘变化
                p1 = new GradientPaint(0, 0, new Color(100, 100, 100), 0, h - 1, new Color(0, 0, 0));
                p2 = new GradientPaint(0, 1, new Color(255, 255, 255, 100), 0, h - 3, new Color(0, 0, 0, 50));
            }
            g2d.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, tran));
            RoundRectangle2D.Float r2d = new RoundRectangle2D.Float(0, 0, w - 1, h - 1, 20, 20);
            //画圆角（左上角坐标，宽度，高度，圆弧的宽度，高度）
            Shape clip = g2d.getClip();
            g2d.clip(r2d);

            GradientPaint gp = new GradientPaint(0.0F, 0.0F, new Color(205, 255, 205), 0.0F, h, new Color(52, 39, 211), true);
            //设置颜色从（x1，y1，color1，(x2，y2),color2）渐变
            g2d.setPaint(gp);  //染色
            g2d.fillRect(0, 0, w, h);
            g2d.setClip(clip); //得到当前的染色剪辑空间
            g2d.setPaint(p1); //设置颜色
            g2d.drawRoundRect(0, 0, w - 1, h - 1, 20, 20); // 染色的范围
            g2d.setPaint(p2);
            g2d.drawRoundRect(1, 1, w - 3, h - 3, 18, 18);
            g2d.dispose();  //释放一部分占用资源
            super.paintComponent(g);
        }
}
