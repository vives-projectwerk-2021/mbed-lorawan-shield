#pragma once
#include "config.h"
#include "eepromOrganizer.h"
#include "Simple-LoRaWAN.h"
#include "sensorManager.h"

#define app_DEBUG(x, ...)   //set as comment to enable debugging
#ifndef app_DEBUG
#define app_DEBUG(x, ...) printf("[app]\t" x "\r\n", ##__VA_ARGS__)
#endif

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