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

    extern I2C i2c_1;
    extern I2C i2c_3;
    extern config default_config;
};
