/*
 * Testing ground for the binary clock.
 */

#include <iostream>
#include <unistd.h>
#include "led-clock.hpp"
#include "../external/rpi-rgb-led-matrix/led-matrix.h"

class LedClockMatrixManipulator : public RGBMatrixManipulator {
public:
  LedClockMatrixManipulator(RGBMatrix *m) : RGBMatrixManipulator(m), clock() {}
  ~LedClockMatrixManipulator() {
    matrix_->ClearScreen();
    matrix_->UpdateScreen();
  }
  // TODO: So far, so good. This now reports the right pixels (see console
  // output, remembering that no output should be in the final method).
  // However, it's not hitting the right positions on the LED. Get X and Y down
  // and you will be very happy.
  void Run() {
    int i, r, g, b;
    auto width = matrix_->width();
    auto height = matrix_->height();
    i = 0;
    while (running_) {
      std::string current_time = clock.report_time();
      for (int x = 0; x < width; ++x) {
        for (int y = height; y > 0; --y) {
          auto symbol = current_time[i];
          switch (symbol) {
            case '*': r = b = 0; g = 255; break;
            case '#': g = b = 0; r = 255; break;
            case '0': r = g = 0; b = 255; break;
            case '1': r = g = 255; b = 0; break;
            default: r = g = b = 0; break;
          }
          std::cout << symbol ;
          matrix_->SetPixel(x, y, r, g, b);
          i++;
        }
      }
      i = 0;
      std::cout << "\n" << std::endl;
      usleep(5000);
    }
  }
private:
  BinaryClock clock;
};
/*
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
*/

    /*
class LedClock {
public:
  //LedClock() : io(), matrix(NULL), manipulator(NULL), updater(NULL) {
  LedClock() : io(){
    // TODO: Raise error if unsuccessful
    std::cout << "Initializing LedClock" << std::endl;
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
  RGBMatrix * matrix;
  LedClockMatrixManipulator * manipulator;
  DisplayUpdater * updater;
};
    */

int main(int argc, char *argv[]) {
    // TODO: Implement as something like this (works for displaying on CL)
//	BinaryClock clock;
//	std::cout << clock.report_time() << std::endl;

    // TODO: Remove, this was just for testing and yes, it works
    GPIO io;
    if (!io.Init()) return 1;
    RGBMatrix m(&io);
    LedClockMatrixManipulator pulse_generator(&m);
    DisplayUpdater updater(&m);
    updater.Start(10);
    // TODO: This is causing problems
    pulse_generator.Start();
    getchar();
    /*
    LedClock clock;
    clock.start();
    std::cout << "D" << std::endl;
    getchar();
    */
	return 0;
}
