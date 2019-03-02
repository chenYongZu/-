import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.net.*;
import java.util.Map;

public class UserListUI implements ActionListener{
    public static JList onlinelist;
    public static JFrame window;
    public static JPanel northjpanel,centerjpanel,southjpanel,northlabeljpanel;
    private JButton login,exit,chat;
    public static JLabel loginStatus,onlinenumber,onlinelistlabel;
    public static JScrollPane onlinescroll;
    private String username;
    public Client client;
    private boolean ischatwindowOpen;

    private String serverIP="127.0.0.1";
    private int serverport=30000;
    private Font font;

    public void init(){
        window = new JFrame("P2P聊天");
        window.setSize(400,800);
        window.setResizable(false);

        font = new Font("Default",Font.PLAIN,18);

        onlinelist = new JList();
        onlinescroll = new JScrollPane(onlinelist);
        onlinescroll.setBounds(10,10,10,10);
        onlinelist.setPreferredSize(new Dimension(300,700));
        onlinelist.setFont(font);

        login = new JButton("登录");
        login.setFont(font);
        login.addActionListener(this);

        exit = new JButton("退出");
        exit.setFont(font);
        exit.addActionListener(this);

        chat = new JButton("聊天窗口");
        chat.setFont(font);
        chat.addActionListener(this);
        chat.setEnabled(false);

        loginStatus = new JLabel("  登录状态：离线");
        loginStatus.setFont(font);

        onlinenumber = new JLabel("  在线人数：0" );
        onlinenumber.setFont(font);

        onlinelistlabel = new JLabel("在线用户列表");
        onlinelistlabel.setFont(new Font("Default",Font.PLAIN,20));
        onlinelistlabel.setOpaque(true);
        onlinelistlabel.setBackground(Color.YELLOW);

        northlabeljpanel = new JPanel(new BorderLayout(1,1));
        northlabeljpanel.add("Center",onlinelistlabel);
        northlabeljpanel.add("East",chat);

        northjpanel = new JPanel();
        northjpanel.setLayout(new BorderLayout(10,10));
        northjpanel.add("Center",loginStatus);
        northjpanel.add("East",login);

        centerjpanel = new JPanel();
        centerjpanel.setLayout(new BorderLayout(1,1));
        centerjpanel.add("North",northlabeljpanel);
        centerjpanel.add("Center",onlinescroll);

        southjpanel = new JPanel();
        southjpanel.setLayout(new BorderLayout(10,10));
        southjpanel.add("Center",onlinenumber);
        southjpanel.add("East",exit);

        window.setLayout(new BorderLayout(70,10));
        window.add("North",northjpanel);
        window.add("Center",centerjpanel);
        window.add("South",southjpanel);
        window.setVisible(true);
        window.setLocationRelativeTo(null);

        window.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                try {
                    onLineRequest(false);
                } catch (Exception e1) {
                    e1.printStackTrace();
                }
                System.exit(0);
            }
        });
        onlinelist.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                if(e.getClickCount()==2){
                  //有待拓展
                }
            }
        });
    }

    public void onLineRequest(boolean check) throws Exception {
        SocketAddress target = new InetSocketAddress(serverIP, serverport);
        DatagramSocket clientOn = new DatagramSocket();

        String msg = username +"#"+(check?"1":"0")+"#"+ "请求"+ (check?"上":"下") +"线！";
        byte[] buf = msg.getBytes();
        DatagramPacket packet = new DatagramPacket(buf,buf.length,target);
        if(check==true){
            clientOn.send(packet);
            client = new Client(clientOn);
            client.start();
            if(client.getUsersnumber().equals("0")){
                client.setUsersnumber("1");
            }
        }
        else{
            client.client.send(packet);
        }
    }

    public void updateList(){
        new Thread(){
            public void run(){
                while(true){
                    if(client.isUpdate==1){
                        onlinelist.setModel(new DefaultListModel());
                        DefaultListModel listMode = (DefaultListModel)onlinelist.getModel();
                        for (Map.Entry<String, SocketAddress> entry : client.userMap.entrySet()) {
                            listMode.addElement(entry.getKey());
                        }
                        onlinenumber.setText("在线人数：" + client.getUsersnumber());
                        chat.setEnabled(true);
                    }
                    try {
                        Thread.sleep(2000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }.start();
    }

    public static void main(String[] args) throws Exception {
        UserListUI clientUI = new UserListUI();
        clientUI.init();
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if(e.getSource()==this.exit){
            try {
                onLineRequest(false);
            } catch (Exception e1) {
                e1.printStackTrace();
            }
            System.exit(0);
        }
        if(e.getSource()==this.login){
            username = JOptionPane.showInputDialog(window,"请输入你的用户名：\n","用户注册",JOptionPane.PLAIN_MESSAGE);
            if(username==null || username.equals("")){
                return;
            }
            else{
                loginStatus.setText("登录状态：在线    用户名："+ username);
                try {
                    onLineRequest(true);
                    updateList();
                } catch (Exception e1) {
                    e1.printStackTrace();
                }
                login.setVisible(false);
            }
        }
        if(e.getSource() == this.chat){
            ischatwindowOpen = client.chatUI.isVisible();
            if(ischatwindowOpen){
                client.chatUI.setVisible(false);
            }
            else{
                client.chatUI.setVisible(true);
            }
        }
    }
}
