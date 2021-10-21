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
        
        private:
            EEPROM_24AA64 eeprom;
            SimpleLoRaWAN::Node node;
            Pulu::sensorManager sensors;

    };
};