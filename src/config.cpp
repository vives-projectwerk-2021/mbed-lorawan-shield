#include "config.h"

#include "PinNames.h"

namespace Pulu {
    I2C i2c_bus(PC_1, PC_0);      //  A4, A5

    config default_config = {
        .lorawan = {
            .pins = { PA_7, PA_6, PA_5, PA_0, PA_1, PA_10, PB_2 }  // mosi, miso, clk, nss, reset, dio0, dio1
        },
        .eeprom = {
            .i2c = &Pulu::i2c_bus,
            .address = 0b1010001 << 1
        },
        .sensors = {
            .temperature = {{
                { &Pulu::i2c_bus, 0x49 << 1 },    // air
                { &Pulu::i2c_bus, 0x48 << 1 }     // ground
            }},
            .light = {{
                { &Pulu::i2c_bus, 0x29 << 1 }
            }},
            .moisture = {{
                { &Pulu::i2c_bus, 0 }
            }}
        }
    };
};