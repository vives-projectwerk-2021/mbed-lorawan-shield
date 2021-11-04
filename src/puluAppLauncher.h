#pragma once
#include "config.h"
#include "eepromOrganizer.h"

#define appLauncher_DEBUG(x, ...)   //set as comment to enable debugging
#ifndef appLauncher_DEBUG
#define appLauncher_DEBUG(x, ...) printf("[appLauncher]\t" x "\r\n", ##__VA_ARGS__)
#endif

namespace Pulu {
    class AppLauncher {
        public:
            AppLauncher();

            void launch();

        private:
            void clear_eeprom();
            void launch_serialListener();
            void launch_app();

        private:
            bool eeprom_valid;
            bool eeprom_error;
            Pulu::EEPROM_Config eeprom_config;
    };
};