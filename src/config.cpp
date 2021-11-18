#include "config.h"

#include "PinNames.h"

namespace Pulu {
    I2C i2c_1(D14,D15);

    config default_config = {
        .lorawan = {
            .pins = { D11, D12, D13, A0, A1, D2, D3 }  // mosi, miso, clk, nss, reset, dio0, dio1
        },
        .eeprom = {
            .i2c = &Pulu::i2c_1,
            .address = 0b1010000 << 1
        }
    };
};