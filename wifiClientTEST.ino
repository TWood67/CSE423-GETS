#include <SPI.h>
#include <WiFi.h>

int status = WL_IDLE_STATUS; //Wifi radio's status
IPAddress ip;
WiFiClient client;

void setup() {
  // initialize serial and wait for the port to open:
  Serial.begin(9600);
  while(!Serial) ;

  // attempt to connect using WEP encryption:
  Serial.println("Initializing Wifi...");
  printMacAddress();

  // scan for existing networks:
  Serial.println("Scanning available networks...");
  listNetworks();
  
  wifiConnect();
  clientSetup();
}

void loop() {

}

void clientSetup(){
  if(status == WL_CONNECTED) {
    if(client.connect("www.google.com", 80)){
      Serial.println("connected to server");
    }
    else{
      Serial.println("cannot connect to server");
    }
  }
}

void wifiConnect() {
  char ssid[] = "iPhone";
  char pass[] = "00000000";
  
  Serial.println("Attempting to connect to WPA network...");
  status = WiFi.begin(ssid, pass);
  
  //if not connected, stop here
  if(status != WL_CONNECTED){
    Serial.println("Couldn't connect...");
    while(true);
  }
  
  //if connected, print info about connection
  else{
    Serial.println("Connected");
    ip = WiFi.localIP();
    Serial.println(ip);
  }
}

void printMacAddress() {
  // the MAC address of your Wifi shield
  byte mac[6];                    

  // print your MAC address:
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
}

void listNetworks() {
  // scan for nearby networks:
  Serial.println("** Scan Networks **");
  byte numSsid = WiFi.scanNetworks();

  // print the list of networks seen:
  Serial.print("number of available networks:");
  Serial.println(numSsid);

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet<numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") ");
    Serial.print(WiFi.SSID(thisNet));
    Serial.print("\tSignal: ");
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(" dBm");
    Serial.print("\tEncryption: ");
    Serial.println(WiFi.encryptionType(thisNet));
  }
}
