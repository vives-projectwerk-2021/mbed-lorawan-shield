#include "mbed.h"
#include "Simple-LoRaWAN.h"
#include "LoRaMessage.h"
#include "settings.h"

using namespace SimpleLoRaWAN;

Node node(keys, pins);

int main(void)
{
  printf("\r\n*** Starting LoRaWAN Shield Example ***\r\n");
  
  uint16_t lux = 0;
  uint16_t temperature = 0;
  uint16_t moisture = 0;
  uint8_t battery = 100;
  uint8_t sensors_status = 0b00000000;

  while(true) {
    LoRaMessage message;
    message.addUint16(lux);
    message.addUint16(temperature);
    message.addUint16(temperature);
    message.addUint16(moisture);
    message.addUint16(moisture);
    message.addUint16(moisture);
    message.addUint16(moisture);
    message.addUint16(moisture);
    message.addUint8(battery);
    battery = battery<1?100:battery-1;
    message.addUint8(sensors_status);
    node.send(message.getMessage(), message.getLength());
    printf("Message sent.");
    ThisThread::sleep_for(30s);
  }
}