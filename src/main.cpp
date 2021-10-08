#include "mbed.h"
#include "Simple-LoRaWAN.h"
#include "settings.h"
#include "Sensor.h"
#include "LoRaMessage.h"

using namespace SimpleLoRaWAN;

Node node(keys, pins);

int main(void)
{
  printf("\r\n*** Starting LoRaWAN Shield Example ***\r\n");
  
  Pulu::Sensor sensors;
  while(true) {
    sensors.Read();
    uint16_t* sensorValues = sensors.Values();
    Pulu::LoRaMessage message;
    message.setLightLevel(sensorValues[0])
    .setAirTemperature(sensorValues[1])
    .setGroundTemperature(sensorValues[2])
    .setMoistureLevel1(sensorValues[3])
    .setMoistureLevel2(sensorValues[4])
    .setMoistureLevel3(sensorValues[5])
    .setMoistureLevel4(sensorValues[6])
    .setMoistureLevel5(sensorValues[7])
    .setBatteryStatus(sensorValues[8]);
    
    node.send(message.message(), message.length());
    printf("Message sent.");
    ThisThread::sleep_for(30s);
  }
}