import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.util.HashMap;
import java.util.Map;

import javax.swing.*;

public class Client extends Thread implements ActionListener{
    public static int STOP=0;
    public int isUpdate = 0;
    private Font font;
    public static Map<String,SocketAddress> userMap = new HashMap();
    public static Map<SocketAddress,String> userName = new HashMap();
    private String usersnumber;
    public DatagramSocket client;
    private JLabel sendTip,infoTip;
    public JFrame chatUI;
    private JTextArea info;
    private JTextField msgText;
    private JScrollPane scroll;
    private JButton sendButton;
    private JPanel sendpanel,infopanel;

    public Client(DatagramSocket client)throws Exception {
        this.client=client;
        this.chatUI=new JFrame("聊天窗口");
        font = new Font("Default",Font.PLAIN,17);
        usersnumber = "0";

        sendTip = new JLabel("输入消息");
        sendTip.setFont(font);

        infoTip = new JLabel("  聊天记录");
        infoTip.setFont(font);

        chatUI.setSize(600, 800);
        chatUI.setResizable(false);

        sendButton=new JButton("发送");
        sendButton.setFont(font);

        info=new JTextArea(30,30);
        scroll=new JScrollPane(info);
        info.setFont(font);
        info.setLineWrap(true);
        info.setWrapStyleWord(true);
        info.setEditable(false);

        infopanel=new JPanel(new BorderLayout(5,5));
        infopanel.add("North",infoTip);
        infopanel.add("Center",scroll);

        JPanel infopanele = new JPanel();
        infopanel.add("East",infopanele);
        JPanel infopanelw = new JPanel();
        infopanel.add("West",infopanelw);

        msgText=new JTextField(30);
        msgText.setFont(font);

        sendpanel=new JPanel(new BorderLayout(5,10));
        sendpanel.add("West",sendTip);
        sendpanel.add("Center",msgText);
        sendpanel.add("East",sendButton);

        chatUI.add("Center",infopanel);
        chatUI.add("South",sendpanel);
        chatUI.setVisible(false);
        chatUI.setDefaultCloseOperation(WindowConstants.HIDE_ON_CLOSE);

        sendButton.addActionListener(this);
    }

    public String getUsersnumber() {
        return usersnumber;
    }

    public void setUsersnumber(String usersnumber) {
        this.usersnumber = usersnumber;
    }

    public void run() {
        try {
            String msg;
            DatagramPacket data;
            if(isUpdate==0){
                isUpdate = 1;
            }

            while(true) {
                if(STOP==1) break;
                byte[] buf=new byte[1024];
                DatagramPacket packet = new DatagramPacket(buf, buf.length);
                client.receive(packet);
                msg = new String(packet.getData(),0,packet.getLength());
                if(msg.length()>0) {
                    if(msg.indexOf("server:")>-1) {
                        userMap.clear();
                        userName.clear();
                        String userdata=msg.substring(msg.indexOf(":")+1,msg.length());
                        usersnumber = userdata.split(":")[0];
                        userdata=userdata.substring(userdata.indexOf(":")+1,userdata.length());
                        String[] user=userdata.split(",");
                        for(String u:user) {
                            if(u!=null && u.length()>0) {
                                String[] udata=u.split("#");
                                String ip=udata[1].split(":")[0];
                                int port=Integer.parseInt(udata[1].split(":")[1]);

                                ip=ip.substring(1,ip.length());

                                SocketAddress adds=new InetSocketAddress(ip,port);
                                userMap.put(udata[0], adds);
                                userName.put(adds,udata[0]);
                            }
                        }
                    }
                    else {
                        //普通消息
                        SocketAddress adds = new InetSocketAddress(packet.getAddress(),packet.getPort());
                        String user = userName.get(adds);
                        this.info.append(user + " 说 ：" + msg + '\n');
                    }
                }
            }
        }
        catch(Exception e){}
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if(e.getSource()==this.sendButton) {
            try{
                String msg=this.msgText.getText();
                if(msg.length()>0) {
                    this.info.append("我 说："+ msg);
                    this.info.append("\n");

                    for (Map.Entry<String, SocketAddress> entry : userMap.entrySet()) {
                        DatagramPacket data=new DatagramPacket(msg.getBytes(),msg.getBytes().length,entry.getValue());
                        client.send(data);
                    }
                    this.msgText.setText("");
                }
            }
            catch(Exception ee){
                System.out.println(ee);
            }
        }
    }
}
