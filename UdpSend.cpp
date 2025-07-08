#include <WiFiUdp.h>
#include "UdpSend.h"
#include "UdpMessage.h"

#define X_PIN 36
#define Y_PIN 39
#define NB_VALUE_JOY 10

int valX[NB_VALUE_JOY], valY[NB_VALUE_JOY];

WiFiUDP Udp;

TLA_OUT_pos tla_out_pos;

IPAddress remoteIP(192, 168, 2, 233);  //@IP de KOC

const int localPort = 1883;
unsigned int remotePort = 1884;

void TLA::begin() {
  Udp.begin(localPort);
  Serial.print(F("Listening on port "));
  Serial.println(localPort);
}

void TLA::sendUdpMsg() {

  for (int i = 0; i < NB_VALUE_JOY; i++) {
    valX[i] = 0;
    valY[i] = 0;
  }

  Udp.beginPacket(remoteIP, remotePort);
  tla_out_pos.msg_id = 0x0221;
  //tla_out_pos.msg_counter = 0;
  tla_out_pos.msg_publisher = 0x0200;

  static int xmax = 0, xmin = 4095, ymax = 0, ymin = 4095;
  static int k = 0;
  static bool ten_cycles = false;

  int valueX = 0;
  int valueY = 0;

  valX[k] = analogRead(X_PIN);
  valY[k] = analogRead(Y_PIN);

  for (int i = 0; i < NB_VALUE_JOY; i++) {
    valueX += valX[i];
    valueY += valY[i];
  }
  valueX = (int)((double)valueX / (double)NB_VALUE_JOY);
  valueY = (int)((double)valueY / (double)NB_VALUE_JOY);

  if (true /*ten_cycles*/) {
    xmax = (valueX > xmax) ? valueX : xmax;
    xmin = (valueX < xmin) ? valueX : xmin;
    ymax = (valueY > ymax) ? valueY : ymax;
    ymin = (valueY < ymin) ? valueY : ymin;

    int xAngle = map(valueX, 409, 4095, 0, 180);
    int yAngle = map(valueY, 409, 4095, 0, 180);

    // Serial.print("x = ");
    // Serial.print(valX[k]);
    // Serial.print(", y = ");
    // Serial.println(valY[k]);

    k++;
    if (k >= NB_VALUE_JOY) {
      k = 0;
      ten_cycles = true;
    }

    Serial.print("xAngle = ");
    Serial.print(xAngle);
    Serial.print(", yAngle = ");
    Serial.println(yAngle);

    //tla_out_pos.pan = xAngle;
    //tla_out_pos.tilt = yAngle;
  }

  uint8_t outPos[sizeof(tla_out_pos)];
  //memset(outPos, 0, sizeof(outPos));

  memcpy(outPos,&tla_out_pos, sizeof(tla_out_pos));
  

  Serial.println("TLA_OUT_pos contenu :");
  for (int i = 0; i < sizeof(tla_out_pos); i++) {
    if (outPos[i] < 0x10)
      Serial.print("0");
      Serial.print(outPos[i], HEX);
      Serial.print(" ");
  }

  Udp.write(outPos, sizeof(outPos));
  Udp.endPacket();
}
