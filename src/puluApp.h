#pragma once
#include "Simple-LoRaWAN.h"
#include "sensorManager.h"
#include "config.h"
#include "EEPROM_24AA64.h"

namespace Pulu {
    class App {
        public:
            App(Pulu::config config);

            void run();

        private:
            SimpleLoRaWAN::LoRaWANKeys get_LoRaWAN_keys();
        
        private:
            EEPROM_24AA64 eeprom;
            SimpleLoRaWAN::Node node;
            Pulu::sensorManager sensors;

    };
};