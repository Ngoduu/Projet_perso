#include <WebServer_WT32_ETH01.h>
#include <Arduino.h>
#include "UdpMessage.h"
#include "UdpSend.h"

IPAddress myIP(192, 168, 2, 232);  //mon @IP
IPAddress myGW(192, 168, 2, 1);    //passerelle
IPAddress mySN(255, 255, 255, 0);  //masque
IPAddress myDNS(8, 8, 8, 8);

TLA tla;

void setup() {
  Serial.begin(115200);
  delay(5000);
  while (!Serial);

  Serial.print("\nStarting UDPSendReceive on " + String(ARDUINO_BOARD));
  Serial.println(" with " + String(SHIELD_TYPE));
  Serial.println(WEBSERVER_WT32_ETH01_VERSION);

  WT32_ETH01_onEvent();

  ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER);

  ETH.config(myIP, myGW, mySN, myDNS);

  WT32_ETH01_waitForConnect();

  Serial.println(F("\nStarting connection to server..."));

  tla.begin();
}

void loop() {
 
  tla.sendUdpMsg();

  delay(1000);

}
