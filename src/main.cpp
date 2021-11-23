#include "mbed.h"
#include "USBSerial.h"
USBSerial serial;

FileHandle *mbed::mbed_override_console(int) {
  return &serial;
}

#include "puluAppLauncher.h"

Pulu::AppLauncher appLauncher;

int main(void)
{
  appLauncher.launch();
  return 0;
}