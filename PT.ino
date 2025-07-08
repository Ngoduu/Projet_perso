#define DEBUG_ETHERNET_WEBSERVER_PORT Serial
#define _ETHERNET_WEBSERVER_LOGLEVEL_ 3
// #define ETH_ADDR 0
// #define ETH_POWER_PIN -1
// #define ETH_PHY_MDC 23
// #define ETH_PHY_MDIO 18
// #define ETH_PHY_TYPE ETH_PHY_LAN8720
// #define ETH_CLK_MODE ETH_CLOCK_GPIO0_OUT
#include <ESP32Servo.h>
#include <WebServer_WT32_ETH01.h>
#include "tourelle_struct.h"
#include <elapsedMillis.h>

IPAddress myIP(192, 168, 2, 232);  //mon @IP
IPAddress myGW(192, 168, 2, 1);    //passerelle
IPAddress mySN(255, 255, 255, 0);  //masque

IPAddress myDNS(8, 8, 8, 8);
IPAddress remoteIP(192, 168, 2, 50);  //@IP de KOC

unsigned int localPort = 1883;    //mon port
unsigned int remotePort = 49312;  //port KOC

char packetBuffer[255];  // buffer message de KOC
byte ReplyBuffer[255];   //buffer message à envoyer

WiFiUDP Udp;
elapsedMillis elapsedTime5Hz; 
unsigned long interval5Hz = 200;

Servo tilt;
Servo pan;
int panpos, tiltpos;

void setup() {
  Serial.begin(115200);
  delay(5000);
  while (!Serial);
  tilt.attach(4);   //GPIO 4
  pan.attach(2);    //GPIO 2
  tilt.write(167);  //à definir
  pan.write(117);   //à definir

  Serial.print("\nStarting UDPSendReceive on " + String(ARDUINO_BOARD));
  Serial.println(" with " + String(SHIELD_TYPE));
  Serial.println(WEBSERVER_WT32_ETH01_VERSION);
  WT32_ETH01_onEvent();  //à mettre avant ETH.begin()

  ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER);
  if (ETH.config(myIP, myGW, mySN, myDNS) == false)
    Serial.println("LAN8720 Configuration failed");
  else 
    Serial.println("LAN8720 Configuration success");

  WT32_ETH01_waitForConnect();

  Serial.println(F("\nStarting connection to server..."));
  Udp.begin(localPort);
  Serial.print(F("Listening on port "));
  Serial.println(localPort);

 
}

void loop() {

  int packetSize = Udp.parsePacket();
  IPAddress remoteIp = Udp.remoteIP();
  remotePort = Udp.remotePort();

  if (packetSize) { 
    Serial.print(F("Received packet of size "));
    Serial.println(packetSize);
    Serial.print(F("From "));
    IPAddress remoteIp = Udp.remoteIP();
    Serial.print(remoteIp);
    Serial.print(F(", port "));
    Serial.println(Udp.remotePort());

    //int len = Udp.read(packetBuffer, sizeof(packetBuffer));

    // if (len > 0) {
    //   packetBuffer[len] = 0;
    // }
    for (int i = 0; i < sizeof(packetBuffer); i++) {
      if (packetBuffer[i] < 0x10)
        Serial.print("0");
        Serial.print(packetBuffer[i], HEX);
        Serial.print(" ");
    }
  }

  // switch(len){
  //   case 1: 
  // break;

  //   case 2: 
  // break;
  // }

  // if (elapsedTime5Hz >= interval5Hz){
  //     elapsedTime5Hz -= interval5Hz;
  // }

}

void movetiltupstep() {
  tiltpos = tilt.read();
  //tiltpos = map(tiltpos,0,1023,0,180);
  //if (tiltpos >= 125){
  tilt.write(tiltpos + 4);
  Serial.println("The tilt pos is : ");
  Serial.println(tiltpos);
  //}
}

void movetiltfullupstep() {
  tiltpos = tilt.read();
  //tiltpos = map(tiltpos,0,1023,0,180);
  Serial.println(tiltpos);
  tilt.write(180);
}

void movetiltdownstep() {
  tiltpos = tilt.read();
  //tiltpos = map(tiltpos,0,1023,0,180);
  //if (tiltpos <= 180){
  tilt.write(tiltpos - 2);
  Serial.println("The tilt pos is : ");
  Serial.println(tiltpos);
  //}
}

void movetiltfulldownstep() {
  tiltpos = tilt.read();
  Serial.println(tiltpos);
  tilt.write(125);
}

void movepanleftstep() {
  panpos = pan.read();
  //panpos = map(panpos, 0, 1023, 0, 180);
  //if (panpos >= 41) {
  pan.write(panpos - 4);
  Serial.println("The pan pos is : ");
  Serial.println(panpos);
  //}
}

void movepanfullleftstep() {
  panpos = pan.read();
  Serial.println(panpos);
  pan.write(41);
}

void movepanrightstep() {
  panpos = pan.read();
  //panpos = map(panpos, 0, 1023, 0, 180);
  //if (panpos <= 178) {
  pan.write(panpos + 4);
  Serial.println("The pan pos is : ");
  Serial.println(panpos);
  //}
}

void movepanfullrightstep() {
  panpos = pan.read();
  Serial.println(panpos);
  pan.write(178);
}

void center() {

  tilt.write(167);
  pan.write(117);
}