#include "led-clock.hpp"
#include "../external/rpi-rgb-led-matrix/led-matrix.h"

#include <unistd.h>

/**
 * Initialize BinaryClock and store BinaryDate to report from.
 */
BinaryClock::BinaryClock(): binclock(BinaryDate()) {}

/**
 * Return current time as a string compatible with the RGB LED matrix.
 */
std::string BinaryClock::report_time() {
	return std::string("") +
"* *                 # # #       \n" +
"***    " + binclock.get_hour() + "        # # # " +
	binclock.get_day_of_week() + "   \n" +
"* *                  # #        \n" +
"                                \n" +
" * *                            \n" +
"* * *  " + binclock.get_minute() + "                   \n" +
"* * *                           \n" +
"                                \n" +
"****                            \n" +
"**                              \n" +
"  **   " + binclock.get_second() + "                   \n" +
"****                            \n" +
"                                \n" +
" # #            ###         \n" +
"# # #  " + binclock.get_month() + "     #  # " + binclock.get_day() + "  \n" +
"# # #           ###  ";
}

/**
 * Initialize LedClock and store objects needed for time reporting.
 */
LedClock::LedClock(): BinaryClock(), io(), matrix(&io),
RGBMatrixManipulator(&matrix) {
	io.Init();
}

/**
 * Clear screen to ensure that display is blank when object is destroyed.
 */
LedClock::~LedClock() {
	matrix.ClearScreen();
	matrix.UpdateScreen();
}

/**
 * Update LED matrix to match current time as long as thread is running.
 */
void LedClock::Run() {
	std::string current_time = report_time();
	int i, r, g, b;
	i = r = g = b = 0;
	while (running_) {
		for (int x = 0; x < matrix.width(); ++x) {
			for (int y = 0; y < matrix.height(); ++y) {
				auto symbol = current_time[i];
				switch (symbol) {
				case '*': r = b = 0; g = 255; break;
				case '#': g = b = 0; r = 255; break;
				case '0': r = g = 0; b = 255; break;
				case '1': r = g = 255; b = 0; break;
				default: r = g = b = 0; break;
				}
				matrix.SetPixel(x, y, r, g, b);
				i++;
			}
			i++;
		}
		usleep(5000);
	}
}

