#include "settings.h"
#include "puluApp.h"

Pulu::config config;
Pulu::App app(config);

int main(void)
{
  app.run();
}