#include "puluAppLauncher.h"
#include "puluApp.h"
#include "SerialListener.h"

namespace Pulu {
    AppLauncher::AppLauncher() {
        Pulu::config config;
        EEPROM_Organizer eeprom(config.eeprom.sda, config.eeprom.scl, config.eeprom.address);
        eeprom_config = eeprom.read_config(&eeprom_valid, &eeprom_error);
    }

    void AppLauncher::launch() {
        if(DigitalIn(D7).read()) {
            clear_eeprom();
        }
        
        if(!eeprom_error && !eeprom_valid) {
            // flash valid eeprom config
            appLauncher_DEBUG("Invalid eeprom config");
            appLauncher_DEBUG("Launching serial listener");
            launch_serialListener();
        }

        if(eeprom_error) {
            // Error with eeprom --> device cannot work
            appLauncher_DEBUG("Error with eeprom");
            appLauncher_DEBUG("Blocking application");
            while(true);
        }
        if(eeprom_valid) {
            // run App
            appLauncher_DEBUG("Launching APP");
            launch_app();
        }        
    }

    void AppLauncher::clear_eeprom() {
        Pulu::config config;
        EEPROM_Organizer eeprom(config.eeprom.sda, config.eeprom.scl, config.eeprom.address);
        if(eeprom.clear()) {
            appLauncher_DEBUG("Error while clearing eeprom");
            while(true);
        }
        eeprom_error = false;
        eeprom_valid = false;
        appLauncher_DEBUG("Cleared eeprom");
    }

    void AppLauncher::launch_serialListener() {
        SerialListener serial;
        if(!serial.cmd_IS_request_id()) {
            appLauncher_DEBUG("Flashing canceled");
            while(true);
        }
        serial.print_id();
        bool error;
        eeprom_config = serial.read_conf(error);
        if(error) {
            appLauncher_DEBUG("Invalid config");
            appLauncher_DEBUG("Flashing canceled");
            appLauncher_DEBUG("Blocking application");
            while(true);
        }
        appLauncher_DEBUG("Valid config");

        Pulu::config config;
        EEPROM_Organizer eeprom(config.eeprom.sda, config.eeprom.scl, config.eeprom.address);
        if(eeprom.write_config(eeprom_config)) {
            appLauncher_DEBUG("Couldn't flash new config");
            while(true);
        }
        appLauncher_DEBUG("Flashed new config");
        eeprom_valid = true;
    }

    void AppLauncher::launch_app() {
        Pulu::config config;
        App* app = new App(config, eeprom_config);
        app->run();
        delete app;
        while(true);
    }
};