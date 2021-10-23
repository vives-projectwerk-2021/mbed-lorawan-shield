#include "puluAppLauncher.h"
#include "puluApp.h"

namespace Pulu {
    AppLauncher::AppLauncher() {
        EEPROM_Organizer eeprom(config.eeprom.sda, config.eeprom.scl, config.eeprom.address);
        eeprom_config = eeprom.read_config(&eeprom_valid, &eeprom_error);
    }

    void AppLauncher::launch() {
        if(eeprom_error) {
            // Error with eeprom --> device cannot work
            appLauncher_DEBUG("Error with eeprom");
            appLauncher_DEBUG("Blocking application");
            while(true);
        }
        if(eeprom_valid) {
            // run App
            appLauncher_DEBUG("Launching APP");
            App* app = new App(config, eeprom_config);
            app->run();
        }
        else {
            // flash valid eeprom config
            appLauncher_DEBUG("Invalid eeprom config");
            appLauncher_DEBUG("Launching EEPROM FLASHER");
            // TODO: read keys from serial
            Pulu::EEPROM_Config newConfig = {
                0x02,
                config.lorawan.keys,
                30
            };
            EEPROM_Organizer eeprom(config.eeprom.sda, config.eeprom.scl, config.eeprom.address);
            eeprom.write_config(newConfig);
        }
        
    }
};