#ifndef LED_ARRAY_HPP_
#define LED_ARRAY_HPP_

#include <string>

#include "../external/rpi-rgb-led-matrix/gpio.h"
#include "../external/rpi-rgb-led-matrix/led-matrix.h"
#include "clock.hpp"

/**
 * A binary clock that reports the time tracked by a BinaryDate.
 */
class BinaryClock {
public:
	BinaryClock();
	std::string report_time();
private:
	BinaryDate bindate;
};

/*
 * An abstract reporter that parses a string and passes it to an LED array.
 *
 * Virtual functions:
 *   get_string - Produce the string to report
 *   set_color - Set color of LED pixel based on char found with get_string
 *
 * Run() opens a separate thread from the calling stack. In this thread,
 * get_string is called continually. For each char found in get_string, a color
 * is set in the LED array using set_color.
 *
 * For some reason, the call to UpdateScreen in the destructor calls a pure
 * virtual function somewhere along the call chain. I'm not sure where, this
 * happens, but I'm leaving it there so that I always clear the screen on exit.
 */
class StringReporter : public RGBMatrixManipulator {
public:
  StringReporter(RGBMatrix *m) : RGBMatrixManipulator(m) {}
  virtual ~StringReporter();
  void Run();
protected:
  int r, g, b, x, y;
  virtual std::string get_string() = 0;
  virtual void set_color(char symbol) = 0;
};

/*
 * A concrete StringReporter that reports the time as formated by BinaryClock.
 */
class BinaryClockReporter : public StringReporter, public BinaryClock {
public:
  BinaryClockReporter(RGBMatrix *m) : StringReporter(m), BinaryClock() {}
private:
  void set_color(char symbol);
  std::string get_string();
};

/*
 * An interface between a BinaryClockReporter and the LED array.
 *
 * The LedClock takes care of managing proper threading for the
 * BinaryClockReporter and the DisplayUpdater.
 */
class LedClock {
public:
  LedClock(RGBMatrix m) : reporter(&m), updater(&m) {}
  void run();
private:
  BinaryClockReporter reporter;
  DisplayUpdater updater;
};

#endif /* LED_ARRAY_HPP_ */
