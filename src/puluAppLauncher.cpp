#include "puluAppLauncher.h"
#include "puluApp.h"
#include "SerialListener.h"

namespace Pulu {
    AppLauncher::AppLauncher() {
        EEPROM_Organizer eeprom(Pulu::default_config.eeprom.i2c, Pulu::default_config.eeprom.address);
        eeprom_config = eeprom.read_config(&eeprom_valid, &eeprom_error);
    }

    void AppLauncher::setSerial(BufferedSerial* bufferedSerial) {
        this->bufferedSerial = bufferedSerial;
    }
    void AppLauncher::setSerial(USBSerial* usb) {
        this->usb = usb;
    }

    void AppLauncher::launch() {
        if(DigitalIn(D7).read()) {
            clear_eeprom();
        }

        if(eeprom_error) {
            // Error with eeprom --> device cannot work
            appLauncher_DEBUG("Error with eeprom");
            appLauncher_DEBUG("Blocking application");
            while(true);
        }

        launch_serialListener();

        if(eeprom_valid) {
            // run App
            appLauncher_DEBUG("Launching APP");
            launch_app();
        }
        else {
            appLauncher_DEBUG("Invalid eeprom configuration");
            appLauncher_DEBUG("Blocking application");
            while(true);
        }
    }

    void AppLauncher::clear_eeprom() {
        EEPROM_Organizer eeprom(Pulu::default_config.eeprom.i2c, Pulu::default_config.eeprom.address);
        if(eeprom.clear()) {
            appLauncher_DEBUG("Error while clearing eeprom");
            while(true);
        }
        eeprom_error = false;
        eeprom_valid = false;
        appLauncher_DEBUG("Cleared eeprom");
    }

    void AppLauncher::launch_serialListener() {
        SerialListener* serial;
        if(this->usb) {
            serial = new SerialListener(this->usb);
        }
        else if(this->bufferedSerial) {
            serial = new SerialListener(this->bufferedSerial);
        }
        else {
            appLauncher_DEBUG("No serial interface configured");
            return;
        }
        
        if(!serial->cmd_IS_request_id()) {
            appLauncher_DEBUG("Flashing canceled");
            delete serial;
            return;
        }
        serial->print_id();
        if(!serial->cmd_IS_reset()) {
            appLauncher_DEBUG("No reset command");
            appLauncher_DEBUG("Flashing canceled");
            delete serial;
            return;
        }
        clear_eeprom();
        serial->print_id();
        bool error;
        eeprom_config = serial->read_conf(error);
        if(error) {
            appLauncher_DEBUG("Invalid config");
            appLauncher_DEBUG("Flashing canceled");
            appLauncher_DEBUG("Blocking application");
            while(true);
        }
        appLauncher_DEBUG("Valid config");

        EEPROM_Organizer eeprom(Pulu::default_config.eeprom.i2c, Pulu::default_config.eeprom.address);
        if(eeprom.write_config(eeprom_config)) {
            appLauncher_DEBUG("Couldn't flash new config");
            while(true);
        }
        appLauncher_DEBUG("Flashed new config");
        eeprom_valid = true;
        delete serial;
    }

    void AppLauncher::launch_app() {
        mbed_file_handle(STDIN_FILENO)->enable_input(false);

        App* app = new App(eeprom_config);
        app->run();
        delete app;
        while(true);
    }
};