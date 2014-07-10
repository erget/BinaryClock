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

// TODO: This class needs to be completely reworked. I've already started - I'm
// trying to get the example in main.cpp to run and display a clock, and I
// don't have any problem with writing code there directly and then moving it
// here. The problem is a matter of planning. An RGBMatrixManipulator has to
// run in order to keep the clock updating on its own thread. However, I don't
// want to have to go through all the work of manually initializing the GPIOs,
// RGBMatrix and DisplayUpdater - that should all happen in the constructor.
// The plan is now to get the naked code working in main.cpp and then transfer
// it here, but in order to do so I will probably need to encapsulate it inside
// the LedClock. ColorPulseGenerator, the class I'm using at the moment,
// inherits from RGBMatrixManipulator and passes its RGBMatrix to the
// superclass upon initialization. Since I want to initialize the RGBMatrix
// inside the class it looks like I'll have to do the following: Make a class
// that inherits from RGBMatrixManipulator in order to be able to access the
// multithreading functionality, then hide that inside the LedClock. The
// LedClock has a method start that triggers the new subclass of
// RGBMatrixManipulator's Run method. Otherwise I see no way of getting around
// requiring the user to initialize all of the component objects themselves and
// that's too much.
/**
 * A display for a BinaryClock.
 *
 * The LED matrix is assumed to have dimensions 16x32.
 */
//class LedClock: public RGBMatrixManipulator, public BinaryClock {
//public:
//	LedClock();
//	virtual ~LedClock();
//	void Run();
//private:
//	GPIO io;
//	RGBMatrix matrix;
//    DisplayUpdater updater;
//};

#endif /* LED_ARRAY_HPP_ */
