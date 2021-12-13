#include "mbed.h"
#include "USBSerial.h"

#if !MBED_CONF_APP_NUCLEO
FileHandle* console_pointer = nullptr;

FileHandle *mbed::mbed_override_console(int) {
  return console_pointer;
}
#endif

#include "puluAppLauncher.h"

Pulu::AppLauncher appLauncher;

int main(void)
{
  #if !MBED_CONF_APP_NUCLEO
  {
    USBSerial usb(false, 0x0483, 0x5740);
    usb.connect();
    uint8_t connection_try = 0;
    while(connection_try++ < 10 && !usb.ready()) {
      ThisThread::sleep_for(1s);
    }
    if(usb.ready()) {
      console_pointer = &usb;
      appLauncher.launch();
    }
  } // destroy USBSerial object
  UnbufferedSerial serial(PA_2, PA_3);
  console_pointer = &serial;
  #endif
  appLauncher.launch();
  return 0;
}