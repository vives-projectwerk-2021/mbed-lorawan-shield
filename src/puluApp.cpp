#include "puluApp.h"

#include "LoRaMessage.h"
#include "converters.h"
#include "identifier.h"

namespace Pulu {
    App::App(Pulu::config config, Pulu::EEPROM_Config eeprom_config) :
        eeprom(config.eeprom.sda, config.eeprom.scl, config.eeprom.address),
        node(eeprom_config.keys, config.lorawan.pins),
        sensors()
    {   
        wait_time = eeprom_config.wait_time;
    };
    
    void App::run() {
        send_boot_message();

        app_DEBUG("Initializing sensors");
        sensors.init();
        app_DEBUG("Initialized sensors");
        while(true) {
            app_DEBUG("reading sensorValues");
            Pulu::sensorValues sensorValues = sensors.values();
            app_DEBUG("read sensorValues");
            app_DEBUG("converting sensorValues to LoRaMessage");
            LoRaMessage message = Pulu::Converters::sensorValues_to_LoRaMessage(sensorValues);
            app_DEBUG("converted sensorValues to LoRaMessage");
            app_DEBUG("scheduling message");
            node.send(message.getMessage(), message.getLength());
            app_DEBUG("scheduled message");
            ThisThread::sleep_for(wait_time * 1s);
        }
    }

    void App::send_boot_message() {
        app_DEBUG("creating boot message");
        LoRaMessage message;
        auto config = eeprom.read_config();
        message.addUint8(config.version);
        message.addUint16(config.wait_time);
        auto uid = get_uid_bytes();
        for(uint8_t i = 0; i<uid.size(); i++) {
            message.addUint8(uid[i]);
        }
        app_DEBUG("created boot message");
        app_DEBUG("scheduling boot message");
        node.send(message.getMessage(), message.getLength(), 10);
        app_DEBUG("scheduled boot message");
        ThisThread::sleep_for(15s);
    }
};