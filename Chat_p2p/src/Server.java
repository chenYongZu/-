import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;


public class Server extends Thread{
    public static List<Map> userList=new ArrayList<Map>();
    public static Map users=new HashMap();

    public static int index=0;
    public static String sum;
    private DatagramSocket server;

    public Server(DatagramSocket server)
    {
        this.server=server;
    }
    public void run(){
        try{
            DatagramPacket sendPacket;
            StringBuffer msg;
            while(true){
                sum = Integer.toString(index);
                for(Map user:Server.userList) {
                    msg=new StringBuffer("server:"+sum+":");
                    for(Map map:Server.userList) {
                        if(!map.get("id").toString().equals(user.get("id").toString())) {
                            msg.append(map.get("id")+"#"+map.get("ip")+":"+map.get("port"));
                            msg.append(",");
                        }
                    }
                    if(!msg.toString().equals("server:"+sum+":")) {
                        byte[] data=msg.toString().getBytes();
                        sendPacket = new DatagramPacket(data, data.length, (InetAddress)user.get("ip"), (Integer)user.get("port"));
                        server.send(sendPacket);
                    }
                }
                Thread.sleep(2000);
            }
        }catch(Exception e){}
    }

    public static void main(String args[])throws Exception {
        int port=30000;
        System.out.println("服务器已启动！");
        DatagramSocket server = new DatagramSocket(port);
        byte[] buf = new byte[1024];

        DatagramPacket packet = new DatagramPacket(buf, buf.length);

        new Server(server).start();

        String msg;
        while(true) {
            server.receive(packet);
            msg=new String(packet.getData(),0,packet.getLength());

            if(msg!=null && msg.equals("stop server"))  break;

            if(msg.length() > 0) {
                System.out.println("收到数据来自：("+packet.getAddress()+":"+packet.getPort()+")=" + msg);
                String[] datatemp = msg.split("#");
                String username = datatemp[0];
                Map map=new HashMap();
                map.put("id", username);
                map.put("ip", packet.getAddress());
                map.put("port", packet.getPort());

                if(!users.containsKey(packet.getAddress()+":"+packet.getPort())){
                    userList.add(map);
                    users.put(packet.getAddress()+":"+packet.getPort(), username);
                    index++;
                }
                else{
                    index--;
                    userList.remove(map);
                }
            }
        }
        server.close();
    }

}
