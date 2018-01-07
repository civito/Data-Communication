package socket;

import java.net.*;
import java.io.*;


public class UDP_MultiThread {
 final int MAXBUFFER = 512;
 private static int a;
 static DatagramSocket Dsocket;
 static byte[] rbuffer = new byte[1024];
 static int[] info_port = new int[1000];
 static int count = 0;
 static int check = 0;
 
 public static void main (String[] args) throws UnknownHostException {
 int arg_port = 1234;
  work(arg_port);
 }
 
 static void work(int port) throws UnknownHostException {
  
  try {
   InetAddress inetaddr = InetAddress.getLocalHost();
   System.out.println("IP Address : "+inetaddr.getHostAddress()+ " PORT Num : " + port);
   DatagramSocket Dsocket = new DatagramSocket(port);
   
   for(int i = 0 ; i<1000 ; i++)
    info_port[i] = 0;
   
   
   receiveFrame r1 =new receiveFrame(Dsocket);
   r1.start();
  } catch (SocketException e) {
 
  e.printStackTrace();
  }
 }
  
 
 
 static class receiveFrame extends Thread {
  DatagramSocket Dsocket;
  receiveFrame (DatagramSocket s) {
   Dsocket = s;
  }  
  public void run() {

   byte[] sbuffer = new byte[1024];
   long time1;
   long time2;
   while (true) {
    byte buffer[] = new byte[512];
    try {
     
    rbuffer = new byte[1024];
    DatagramPacket recv_packet = new DatagramPacket(rbuffer, rbuffer.length);
    Dsocket.receive (recv_packet );
    
    for(int i = 0 ; i < count; i++)
    {     
     if(info_port[i] == recv_packet.getPort())
      check++;  
    }
    
    if(check == 0)
    {
     info_port[count] = recv_packet.getPort();      
     count++;
    }
    
    check = 0;
    
    System.out.println("From IP : "+recv_packet.getAddress()+" Port Num : "+recv_packet.getPort());
    String sentence = new String(recv_packet.getData());
    System.out.println(sentence);
    
    sbuffer = rbuffer;
    
    for(int i = 0 ; i< count ; i++)
    {
     
     do{
      time1 = System.currentTimeMillis();
      DatagramPacket send_packet = new DatagramPacket(rbuffer, rbuffer.length,recv_packet.getAddress(),info_port[i]);
      Dsocket.send (send_packet);
      time2 = System.currentTimeMillis();
     }while(time2 - time1 > 1000);
    }
    } catch(IOException e) {
     System.out.println(e);
    }
   }
  }
 }
}
