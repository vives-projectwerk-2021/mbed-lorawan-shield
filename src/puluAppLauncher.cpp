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
            printf("Launcher: eeprom error\n");
            while(true);
        }
        if(eeprom_valid) {
            printf("Launcher: eeprom valid\n");
            // run App
            App* app = new App(config, eeprom_config);
            app->run();
        }
        else {
            printf("Launcher: eeprom invalid\n");
            // re-initialize device
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