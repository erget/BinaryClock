#ifndef LED_ARRAY_HPP_
#define LED_ARRAY_HPP_

#include <string>

#include "../external/rpi-rgb-led-matrix/gpio.h"
#include "../external/rpi-rgb-led-matrix/led-matrix.h"
#include "clock.hpp"

/**
 * A display for a BinaryClock.
 *
 * The LED matrix is assumed to have dimensions 16x32.
 */
class LedClock: public RGBMatrixManipulator {
public:
	LedClock();
	virtual ~LedClock();
	void Run();
	std::string report_time();
private:
	BinaryDate binclock;
	GPIO io;
	RGBMatrix matrix;
};

#endif /* LED_ARRAY_HPP_ */
