/*
 * Testing ground for the binary clock.
 */

#include <iostream>
#include <unistd.h>
#include "led-clock.hpp"
#include "../external/rpi-rgb-led-matrix/led-matrix.h"

    /*
class LedClock {
public:
  //LedClock() : io(), matrix(NULL), manipulator(NULL), updater(NULL) {
  LedClock() : io(){
    // TODO: Raise error if unsuccessful
    std::cout << "Initializing LedClock" << std::endl;
    io.Init();
    RGBMatrix matrix(&io);
    BinaryClockReporter manipulator(&matrix);
    DisplayUpdater updater(&matrix);
  }
  void start() {
    updater.Start(10);
    manipulator.Start();
  }
private:
  GPIO io;
  RGBMatrix * matrix;
  BinaryClockReporter * manipulator;
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
    BinaryClockReporter pulse_generator(&m);
    DisplayUpdater updater(&m);
    updater.Start(10);
    pulse_generator.Start();
    getchar();
	return 0;
}
