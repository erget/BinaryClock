/*
 * Testing ground for the binary clock.
 */

#include <iostream>
#include "led-clock.hpp"
#include "../external/rpi-rgb-led-matrix/led-matrix.h"

// TODO: Remove, this is only for testing purposes
class ColorPulseGenerator : public RGBMatrixManipulator {
public:
  ColorPulseGenerator(RGBMatrix *m) : RGBMatrixManipulator(m) {}
  void Run() {
    const int width = matrix_->width();
    const int height = matrix_->height();
    uint32_t count = 0;
    while (running_) {
      usleep(5000);
      ++count;
      int color = (count >> 9) % 6;
      int value = count & 0xFF;
      if (count & 0x100) value = 255 - value;
      int r, g, b;
      switch (color) {
      case 0: r = value; g = b = 0; break;
      case 1: r = g = value; b = 0; break;
      case 2: g = value; r = b = 0; break;
      case 3: g = b = value; r = 0; break;
      case 4: b = value; r = g = 0; break;
      default: r = g = b = value; break;
      }
      for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y)
          matrix_->SetPixel(x, y, r, g, b);
    }
  }
};

int main(int argc, char *argv[]) {
	//BinaryClock clock;

    // TODO: Deactivated for testing
	//LedClock clock;
	//std::cout << clock.report_time() << std::endl;

    // TODO: Remove, this was just for testing and yes, it works
    GPIO io;
    if (!io.Init()) return 1;
    RGBMatrix m(&io);
    ColorPulseGenerator pulse_generator(&m);
    DisplayUpdater updater(&m);
    updater.Start(10);
    pulse_generator.Start();
    getchar();

	return 0;
}
