package socket;

import java.net.*;
import java.io.*;

public class UDP_client {
 final static int MAXBUFFER = 512;

 public static void main(String[] args) {
  int port = 1234;

  try {
   InetAddress inetadd = InetAddress.getByName("14.35.222.129");
   DatagramSocket socket = new DatagramSocket();
   DatagramPacket send_packet;
   BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

   receive rthread = new receive(socket);
   rthread.start();

   while (true) {
    byte buffer[] = new byte[MAXBUFFER];
    String data = br.readLine();
    if (data.length() == 0)
     break;
    buffer = data.getBytes();
    send_packet = new DatagramPacket(buffer, buffer.length, inetadd, port);
    socket.send(send_packet);

   }
  } catch (UnknownHostException ex) {
   System.out.println("Error in the host address ");
  } catch (IOException e) {
   System.out.println(e);
  }
 }

 static class receive extends Thread {
  DatagramSocket Dsocket;

  receive(DatagramSocket s) {
   Dsocket = s;
  }

  public void run() {
   byte rbuffer[] = new byte[MAXBUFFER];
   DatagramPacket rcvthread = new DatagramPacket(rbuffer, rbuffer.length);

   while (true) {
    try {
     Dsocket.receive(rcvthread);
    } catch (IOException e) {
  
     e.printStackTrace();
    }

    String sentence = new String(rcvthread.getData());
    String result = new String(rbuffer);
    System.out.println("echo IP: " + rcvthread.getAddress() + " Port NUM : " + rcvthread.getPort());
    System.out.println(sentence);
   }

  }
 }
} 

