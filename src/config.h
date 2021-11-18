#pragma once

#include "simple-lorawan-config.h"
#include "I2C.h"

namespace Pulu {
    struct config {
        struct lorawan {
            SimpleLoRaWAN::Pinmapping pins;
        } lorawan;
        struct eeprom {
            I2C* i2c;
            uint8_t address;
        } eeprom;
    };

    extern I2C i2c_1;
    extern config default_config;
};
