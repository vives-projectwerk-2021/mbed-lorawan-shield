#include "mbed.h"
#include "USBSerial.h"
#include "BufferedSerial.h"

FileHandle* console_pointer = nullptr;

FileHandle *mbed::mbed_override_console(int) {
  return console_pointer;
}

#include "puluAppLauncher.h"

Pulu::AppLauncher appLauncher;

int main(void)
{
  #if !MBED_CONF_APP_NUCLEO
  {
    USBSerial usb(false, 0x0483, 0x5740);
    usb.connect();
    uint8_t connection_try_count = 10;
    while(connection_try_count-- && !usb.ready()) {
      ThisThread::sleep_for(1s);
    }
    if(usb.ready()) {
      appLauncher.setSerial(&usb);
      console_pointer = &usb;
      appLauncher.launch();
    }
  } // destroy USBSerial object
  #endif
  BufferedSerial bufferedSerial(PA_2, PA_3, 115200);
  appLauncher.setSerial(&bufferedSerial);
  console_pointer = &bufferedSerial;
  appLauncher.launch();
  return 0;
}