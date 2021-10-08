#include "puluApp.h"

#include "LoRaMessage.h"
#include "converters.h"

namespace Pulu {
    App::App(Pulu::config config) {
        node = new SimpleLoRaWAN::Node(config.lorawan.keys, config.lorawan.pins);
        sensors = new Pulu::sensorManager();
    };
    
    void App::run() {
        sensors->init();
        while(true) {
            LoRaMessage message = Pulu::Converters::sensorValues_to_LoRaMessage(sensors->values());
            node->send(message.getMessage(), message.getLength());
            ThisThread::sleep_for(30s);
        }
    }
};