#pragma once
#include "config.h"
#include "EEPROM_24AA64.h"
#include "Simple-LoRaWAN.h"
#include "sensorManager.h"

namespace Pulu {
    class App {
        private:
            Pulu::config config;

        public:
            App();

            void run();

        private:
            SimpleLoRaWAN::LoRaWANKeys get_LoRaWAN_keys();
            bool get_wait_time(uint16_t &wait_time);    // success = 0
            bool set_wait_time(uint16_t wait_time);     // success = 0
        
        private:
            uint16_t wait_time;

            EEPROM_24AA64 eeprom;
            SimpleLoRaWAN::Node node;
            Pulu::sensorManager sensors;

    };
};