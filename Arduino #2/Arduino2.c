// Java Source

import java.io.*;
import java.util.*;
import gnu.io.*; 
public class SimpleRead implements Runnable, SerialPortEventListener {
  static CommPortIdentifier portId;
  static Enumeration portList; 
  static SerialPort serialPort;
  static OutputStream outputStream;
  static Scanner in = new Scanner(System.in);    //messageString scan
  static String messageString = in.nextLine();   
 
  InputStream inputStream;
  Thread readThread; 
   
  public static void main(String[] args) {             //  main function
    portList = CommPortIdentifier.getPortIdentifiers(); 
    String State = "state : "+ messageString;         // make Statement
     
    while (portList.hasMoreElements()) {             
      portId = (CommPortIdentifier) portList.nextElement();      
      if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {      
        if (portId.getName().equals("COM3")) {         // confirm Port Num
          SimpleRead reader = new SimpleRead();
          try {
            serialPort = (SerialPort)portId.open("SimpleWriteApp", 2000);
          } catch (PortInUseException e) {}
        }
      }
     }
 
    try {
      outputStream = serialPort.getOutputStream();
    } catch (IOException e) { }
    try {
      serialPort.setSerialPortParams(9600,SerialPort.DATABITS_8, SerialPort.STOPBITS_1,SerialPort.PARITY_NONE);
    } catch (UnsupportedCommOperationException e) { }
    try {
      outputStream.write(State.getBytes());   // write to Arduino
    } catch (IOException e) {}  
 }
      
 public SimpleRead() {      //  function
   try {               
    serialPort = (SerialPort) portId.open("SimpleReadApp", 2000);
   } catch (PortInUseException e) { }
   try {             
    inputStream = serialPort.getInputStream();
   } catch (IOException e) { }
  
   try {
    serialPort.addEventListener(this);
   } catch (TooManyListenersException e) { }         
   serialPort.notifyOnDataAvailable(true); 
   try {
    serialPort.setSerialPortParams(9600,SerialPort.DATABITS_8, SerialPort.STOPBITS_1,SerialPort.PARITY_NONE);
    } catch (UnsupportedCommOperationException e) { }  
   readThread = new Thread(this); 
   readThread.start();
  }
 
  public void run() {
   try {
    Thread.sleep(20000);
    } catch (InterruptedException e) { }
  } 

  public void serialEvent(SerialPortEvent event) {

   switch (event.getEventType()){
     case SerialPortEvent.BI:
     case SerialPortEvent.OE:
  	 case SerialPortEvent.FE:
  	 case SerialPortEvent.PE:
  	 case SerialPortEvent.CD:
  	 case SerialPortEvent.CTS:
     case SerialPortEvent.DSR:
  	 case SerialPortEvent.RI:
  	 case SerialPortEvent.OUTPUT_BUFFER_EMPTY:
     break;
   
   case SerialPortEvent.DATA_AVAILABLE:     
    byte[] readBuffer = new byte[1];   // READ
 
        try {
            while (inputStream.available() > 0) {
                 int numBytes =inputStream.read(readBuffer);
             }
             System.out.print(new String(readBuffer));
             } catch (IOException e) { }
             break;
      }  
  }
  
}





// Arduino Source


const int ledPin = 13;
int blinkRate = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {                     //Read from console and write to console
  while(Serial.available()){
    char ch = Serial.read();
    Serial.print(ch);
    delay(100);
    flag = 1;
  }
  blink();
}

void blink(){           // to confirm Connection of computer and arduino , blinkrate 100ms
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
  delay(100); 
}
