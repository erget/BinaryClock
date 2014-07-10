/*
 * Testing ground for the binary clock.
 */

#include <iostream>
#include <unistd.h>
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

class LedClockMatrixManipulator : public RGBMatrixManipulator, public BinaryClock {
public:
  LedClockMatrixManipulator(RGBMatrix *m) : RGBMatrixManipulator(m), BinaryClock() {}
  ~LedClockMatrixManipulator() {
    matrix_->ClearScreen();
    matrix_->UpdateScreen();
  }
  void Run() {
    std::string current_time = report_time();
    int i, r, g, b;
    i = r = g = b = 0;
    while (running_) {
      for (int x = 0; x < matrix_->width(); ++x) {
        for (int y = 0; y < matrix_->height(); ++y) {
          auto symbol = current_time[i];
          switch (symbol) {
            case '*': r = b = 0; g = 255; break;
            case '#': g = b = 0; r = 255; break;
            case '0': r = g = 0; b = 255; break;
            case '1': r = g = 255; b = 0; break;
            default: r = g = b = 0; break;
          }
          matrix_->SetPixel(x, y, r, g, b);
          i++;
        }
      i++;
      }
    }
  usleep(5000);
  }
};

class LedClock {
public:
  LedClock() : io(), matrix(NULL), manipulator(NULL), updater(NULL) {
    // TODO: Raise error if unsuccessful
    io.Init();
    RGBMatrix matrix(&io);
    LedClockMatrixManipulator manipulator(&matrix);
    DisplayUpdater updater(&matrix);
  }
  void start() {
    updater.Start(10);
    manipulator.Start();
  }
private:
  GPIO io;
  RGBMatrix matrix;
  LedClockMatrixManipulator manipulator;
  DisplayUpdater updater;
};

int main(int argc, char *argv[]) {
    // TODO: Implement as something like this (works for displaying on CL)
//	BinaryClock clock;
//	std::cout << clock.report_time() << std::endl;

    // TODO: Remove, this was just for testing and yes, it works
    /*
    GPIO io;
    if (!io.Init()) return 1;
    RGBMatrix m(&io);
    ColorPulseGenerator pulse_generator(&m);
    DisplayUpdater updater(&m);
    updater.Start(10);
    pulse_generator.Start();
    getchar();
    */
    LedClock clock;
    clock.start();
    getchar();
	return 0;
}
