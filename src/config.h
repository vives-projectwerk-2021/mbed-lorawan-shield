#pragma once

#include "simple-lorawan-config.h"

namespace Pulu {
    struct config {
        struct lorawan {
            SimpleLoRaWAN::Pinmapping pins = { D11, D12, D13, A0, A1, D2, D3 };  // mosi, miso, clk, nss, reset, dio0, dio1
        } lorawan;
        struct eeprom {
            PinName sda = D14;
            PinName scl = D15;
            uint16_t address = 0b1010000 << 1;
        } eeprom;
    };
};
