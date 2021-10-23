#pragma once
#include "config.h"
#include "eepromOrganizer.h"
#include "Simple-LoRaWAN.h"
#include "sensorManager.h"

namespace Pulu {
    class App {
        public:
            App(Pulu::config config, Pulu::EEPROM_Config eeprom_config);

            void run();
        
        private:
            uint16_t wait_time;

            EEPROM_Organizer eeprom;
            SimpleLoRaWAN::Node node;
            Pulu::sensorManager sensors;

    };
};