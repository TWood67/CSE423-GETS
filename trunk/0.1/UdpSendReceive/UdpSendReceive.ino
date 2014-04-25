#include <SPI.h>
#include <WiFi.h>
#include <WiFiUdp.h>


int status = WL_IDLE_STATUS;
char ssid[] = "TantricPumpkin";
char pass[] = "willsphone";
IPAddress ip;                       // IP address of the shield
int keyIndex = 0;                   // your network key Index number (needed only for WEP)
unsigned int localPort = 2390;      // local port to listen on

char packetBuffer[255];             // buffer to hold incoming packet
WiFiUDP Udp;

void setup() {
  // initialize serial and wait for the port to open:
  Serial.begin(9600);
  while(!Serial) ;

  pinMode(22, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(28, OUTPUT);

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) 
  {
      Serial.println("WiFi shield not present");
      while (true);
  }

  String fv = WiFi.firmwareVersion();
  if ( fv != "1.1.0" )
    Serial.println("Please upgrade the firmware");

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) 
  {
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(ssid);
      
      // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
      status = WiFi.begin(ssid, pass);
  
      // wait 2 seconds for connection:
      delay(2000);
      
      //print the local IP address
      ip = WiFi.localIP();
      Serial.println(ip);
  }
  Serial.println("Connected to wifi");
  printWifiStatus();
  Serial.println("\nStarting connection to server...");
  
  // if you get a connection, report back via serial:
  Udp.begin(localPort);
  Serial.print("\nConnection Accomplished; Waiting on Port: ");
  Serial.println(localPort);
  
}





void loop() 
{
    delay(10);
  
    // if there's data available, read a packet
    int packetSize = Udp.parsePacket();
    
    if (packetSize)
    {
        // read the packet into packetBufffer
        int len = Udp.read(packetBuffer, 8);
        if (len > 0) packetBuffer[len] = 0;
        
        if(packetBuffer[5] == '9' && packetBuffer[6] == '9' && packetBuffer[7] == '9')
        {
            Serial.println("Kill Command Recieved");
            digitalWrite(28, HIGH);
        }
        else if (packetBuffer[5] == '9' && packetBuffer[6] == '9' && packetBuffer[7] == '8')
        {
            Serial.println("Kill Timer Command Recieved");
            digitalWrite(26, HIGH);
        }
        else if (packetBuffer[5] == '2' && packetBuffer[6] == '0' && packetBuffer[7] == '1')
        {
            Serial.println("Landing Command Recieved");
            digitalWrite(24, HIGH);
        }
        else if (packetBuffer[5] == '2' && packetBuffer[6] == '0' && packetBuffer[7] == '2')
        {
            Serial.println("Launch Command Recieved");
            digitalWrite(22, HIGH);
        }        
    }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
