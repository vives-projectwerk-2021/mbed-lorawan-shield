#include "puluApp.h"

#include "LoRaMessage.h"
#include "converters.h"

namespace Pulu {
    App::App() :
        config(),
        eeprom(config.eeprom.sda, config.eeprom.scl, config.eeprom.address),
        node(get_LoRaWAN_keys(), config.lorawan.pins),
        sensors()
    {   
        if(get_wait_time(wait_time)) { // ERROR OCCURED
            wait_time = 30; 
        }
    };
    
    void App::run() {
        sensors.init();
        while(true) {
            LoRaMessage message = Pulu::Converters::sensorValues_to_LoRaMessage(sensors.values());
            node.send(message.getMessage(), message.getLength());
            ThisThread::sleep_for(wait_time * 1s);
        }
    }

    SimpleLoRaWAN::LoRaWANKeys App::get_LoRaWAN_keys() {
        MbedCRC<POLY_32BIT_ANSI, 32> mbedCRC;

        char data[45];
        if(eeprom.read(data, 45)) {
            return {};
        }

        SimpleLoRaWAN::LoRaWANKeys keys;
        struct LoRaWANCRC {
            uint32_t devEui;
            uint32_t appEui;
            uint32_t appKey;
        };
        LoRaWANCRC crc;
        LoRaWANCRC crcCheck;
        memcpy(keys.devEui, data+1, 8);
        memcpy(&crc.devEui, data+9, 4);
        memcpy(keys.appEui, data+13, 8);
        memcpy(&crc.appEui, data+21, 4);
        memcpy(keys.appKey, data+25, 16);
        memcpy(&crc.appKey, data+41, 4);

        mbedCRC.compute((void *)keys.devEui, 8, &crcCheck.devEui);
        mbedCRC.compute((void *)keys.appEui, 8, &crcCheck.appEui);
        mbedCRC.compute((void *)keys.appKey, 16, &crcCheck.appKey);

        if(crc.devEui == crcCheck.devEui
        && crc.appEui == crcCheck.appEui
        && crc.appKey == crcCheck.appKey)
        {
            return keys;
        }
        return {};
    }

    bool App::get_wait_time(uint16_t &wait_time) {
        return eeprom.read((char*)&wait_time, 2, 45);
    }
    bool App::set_wait_time(uint16_t wait_time) {
        if(eeprom.write((char*)&wait_time, 2, 45)) {
            return true;
        }
        this->wait_time = wait_time;
        return false;
    }
};