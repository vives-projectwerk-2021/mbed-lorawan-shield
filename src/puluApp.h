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
            SimpleLoRaWAN::Node node;
            Pulu::sensorManager sensors;
            EEPROM_24AA64 eeprom;
    };
};