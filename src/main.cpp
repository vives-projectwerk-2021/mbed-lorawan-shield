#include "mbed.h"
#include "USBSerial.h"
USBSerial serial(false, 0x0483, 0x5740);

FileHandle *mbed::mbed_override_console(int) {
  return &serial;
}

#include "puluAppLauncher.h"

Pulu::AppLauncher appLauncher;

int main(void)
{
  serial.connect();

  appLauncher.launch();
  return 0;
}