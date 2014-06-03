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
	BinaryDate binclock;
};

/**
 * A display for a BinaryClock.
 *
 * The LED matrix is assumed to have dimensions 16x32.
 */
class LedClock: public RGBMatrixManipulator, public BinaryClock {
public:
	LedClock();
	virtual ~LedClock();
	void Run();
private:
	GPIO io;
	RGBMatrix matrix;
};

#endif /* LED_ARRAY_HPP_ */
