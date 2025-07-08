#include <WiFiUdp.h>

class TLA{

public:
  void begin();
  void listen(unsigned char* packetBuffer,size_t length);
  void decode(const unsigned char* buffer,size_t size);
  void sendUdpMsg();
  uint8_t htons(uint8_t value);
};





