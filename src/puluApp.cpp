#include "puluApp.h"

#include "LoRaMessage.h"
#include "converters.h"

namespace Pulu {
    App::App(Pulu::config config, Pulu::EEPROM_Config eeprom_config) :
        eeprom(config.eeprom.sda, config.eeprom.scl, config.eeprom.address),
        node(eeprom_config.keys, config.lorawan.pins),
        sensors()
    {   
        wait_time = eeprom_config.wait_time;
    };
    
    void App::run() {
        sensors.init();
        while(true) {
            LoRaMessage message = Pulu::Converters::sensorValues_to_LoRaMessage(sensors.values());
            node.send(message.getMessage(), message.getLength());
            ThisThread::sleep_for(wait_time * 1s);
        }
    }
};