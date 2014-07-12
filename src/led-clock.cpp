#include "led-clock.hpp"
#include "../external/rpi-rgb-led-matrix/led-matrix.h"

#include <unistd.h>

/**
 * Initialize BinaryClock and store BinaryDate to report from.
 */
BinaryClock::BinaryClock(): bindate(BinaryDate()) {}

/**
 * Return current time as a string compatible with the RGB LED matrix.
 */
std::string BinaryClock::report_time() {
	return std::string("") +
"* *                 # # #\n" +
"***    " + bindate.get_hour() + "        # # # " +
	bindate.get_day_of_week() + "\n" +
"* *                  # #\n" +
"\n" +
" * *\n" +
"* * *  " + bindate.get_minute() + "\n" +
"* * *\n" +
"\n" +
"****\n" +
"**\n" +
"  **   " + bindate.get_second() + "\n" +
"****\n" +
"\n" +
" # #            ###\n" +
"# # #  " + bindate.get_month() + "     #  # " + bindate.get_day() + "\n" +
"# # #           ###  ";
}

StringReporter::~StringReporter() {
  matrix_->ClearScreen();
  matrix_->UpdateScreen();
}

void StringReporter::Run() {
  while (running_) {
    auto report_string = get_string();
    x = y = 0;
    for (unsigned int i = 0; i < report_string.length(); ++i) {
      auto symbol = report_string[i];
      set_color(symbol);
    }
    usleep(5000);
  }
}

std::string BinaryClockReporter::get_string() {
  return report_time();
}

void BinaryClockReporter::set_color(char symbol) {
  switch (symbol) {
    case '*': r = b = 0; g = 255; break;
    case '#': g = b = 0; r = 255; break;
    case '0': r = g = 0; b = 255; break;
    case '1': r = g = 255; b = 0; break;
    case '\n': x = -1; y++; break;
    default: r = g = b = 0; break;
  }
  matrix_->SetPixel(x, y, r, g, b);
  x++;
}
