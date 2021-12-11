#include "puluApp.h"

#include "mbed.h"
#include "LoRaMessage.h"
#include "converters.h"
#include "identifier.h"

namespace Pulu {
    App::App(Pulu::EEPROM_Config eeprom_config) :
        eeprom(Pulu::default_config.eeprom.i2c, Pulu::default_config.eeprom.address),
        node(eeprom_config.keys, Pulu::default_config.lorawan.pins),
        sensors(Pulu::default_config.sensors)
    {   
        wait_time = eeprom_config.wait_time;
        node.on_received(mbed::callback(this, &App::node_on_receive));
    };
    
    void App::run() {
        send_boot_message();
        ThisThread::sleep_for(15s);

        while(true) {
            app_DEBUG("requesting sensor measurement");
            auto measurement = sensors.do_measurement();
            app_DEBUG("sensor measurement done");
            app_DEBUG("converting measurement to LoRaMessage");
            LoRaMessage message = Pulu::Converters::measurement_to_LoRaMessage(measurement);
            app_DEBUG("converted measurement to LoRaMessage");
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
    }

    void App::node_on_receive(char* data, uint8_t length, uint8_t port) {
        if(port == 10 && length == 2) {
            uint16_t new_wait_time = data[0]<<8 | data[1];
            app_DEBUG("Received message to set wait_time to %d s", new_wait_time);
            if(eeprom.write_config_wait_time(new_wait_time)) {
                app_DEBUG("Failed to modify wait_time");
            }
            else {
                auto config = eeprom.read_config();
                wait_time = config.wait_time;
                app_DEBUG("Modified wait_time to %d s", wait_time);
            }
        }
    }
};