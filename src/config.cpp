#include "config.h"

#include "PinNames.h"

namespace Pulu {
    #if MBED_CONF_APP_NUCLEO
    I2C i2c_bus2(PB_9, PB_8);     // D14, D15
    #endif
    I2C i2c_bus(PC_1, PC_0);      //  A4, A5

    config default_config = {
        .lorawan = {
            #if MBED_CONF_APP_NUCLEO
            .pins = { D11, D12, D13, A0, A1, D2, D3 }  // mosi, miso, clk, nss, reset, dio0, dio1
            #else
            .pins = { PA_7, PA_6, PA_5, PA_0, PA_1, PA_10, PB_2 }  // mosi, miso, clk, nss, reset, dio0, dio1
            #endif
        },
        .eeprom = {
            #if MBED_CONF_APP_NUCLEO
            .i2c = &Pulu::i2c_bus2,
            .address = 0b1010000 << 1
            #else
            .i2c = &Pulu::i2c_bus,
            .address = 0b1010001 << 1
            #endif
        },
        .sensors = {
            #if !MBED_CONF_PULU_SENSOR_MANAGER_FAKE_LIGHT
            .light = {{
                { &Pulu::i2c_bus, 0x29 << 1 }
            }},
            #endif
            #if !MBED_CONF_PULU_SENSOR_MANAGER_FAKE_TEMPERATURE
            .temperature = {{
                { &Pulu::i2c_bus, 0x49 << 1 },    // air
                { &Pulu::i2c_bus, 0x48 << 1 }     // ground
            }},
            #endif
            #if !MBED_CONF_PULU_SENSOR_MANAGER_FAKE_MOISTURE
            .moisture = {{
                { &Pulu::i2c_bus, 0x50 << 1 }
            }}
            #endif
        }
    };
};