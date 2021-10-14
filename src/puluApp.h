#pragma once
#include "Simple-LoRaWAN.h"
#include "sensorManager.h"
#include "config.h"

namespace Pulu {
    class App {
        public:
            App(Pulu::config config);

            void run();
        
        private:
            SimpleLoRaWAN::Node node;
            Pulu::sensorManager sensors;
    };
};