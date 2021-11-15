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
            void send_boot_message();

            void node_on_receive(char* data, uint8_t length, uint8_t port);
        
        private:
            uint16_t wait_time;

            EEPROM_Organizer eeprom;
            SimpleLoRaWAN::Node node;
            Pulu::sensorManager sensors;

    };
};