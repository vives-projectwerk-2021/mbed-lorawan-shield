#pragma once
#include "config.h"
#include "eepromOrganizer.h"

namespace Pulu {
    class AppLauncher {
        public:
            AppLauncher();

            void launch();

        private:
            Pulu::config config;
            bool eeprom_valid;
            bool eeprom_error;
            Pulu::EEPROM_Config eeprom_config;
    };
};