#include "mbed.h"
#include "Simple-LoRaWAN.h"
#include "LoRaMessage.h"
#include "settings.h"

using namespace SimpleLoRaWAN;

BufferedSerial pc(USBTX, USBRX, 115200);

Node node(keys, pins);

int main(void)
{
  printf("\r\n*** Starting LoRaWAN Shield Example ***\r\n");
  
  int counter = 0;

  while(true) {
    LoRaMessage message;
    message.addUint8(counter++);
    node.send(message.getMessage(), message.getLength());
    printf("Message sent. counter: %d\r\n", counter);
    ThisThread::sleep_for(30s);
  }
}