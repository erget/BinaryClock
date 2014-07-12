#include <iostream>
#include <unistd.h>
#include "led-clock.hpp"
#include "../external/rpi-rgb-led-matrix/led-matrix.h"

/*
 * Initialize GPIO pins and RGB matrix, then create and run LedClock.
 */
int main(int argc, char *argv[]) {
  GPIO io;
  if (!io.Init()) {
    std::cerr << "Couldn't access GPIO pins." << std::endl;
    return 1;
  }
  RGBMatrix matrix(&io);
  LedClock clock(matrix);
  clock.run();
  return 0;
}
