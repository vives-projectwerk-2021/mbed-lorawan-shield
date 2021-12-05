#pragma once

#include "simple-lorawan-config.h"
#include "I2C.h"
#include "sensorConfig.h"

namespace Pulu {
    struct config {
        struct lorawan {
            SimpleLoRaWAN::Pinmapping pins;
        } lorawan;
        struct eeprom {
            I2C* i2c;
            uint8_t address;
        } eeprom;
        Sensors::config sensors;
    };

    #if MBED_CONF_APP_NUCLEO
    extern I2C i2c_bus2;
    #endif

    extern I2C i2c_bus;
    extern config default_config;
};
