/*
 * This file is part of BinaryClock.
 *
 * BinaryClock is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * BinaryClock is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * BinaryClock.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "led-clock.hpp"
#include "../external/rpi-rgb-led-matrix/led-matrix.h"

#include <stdexcept>
#include <iostream>
#include <stdlib.h> 
#include <unistd.h>

BinaryClock::BinaryClock(): bindate(BinaryDate()) {}

std::string BinaryClock::report_time() {
	return std::string("\n") +
"* *                  # #\n" +
"***                 # # #\n" +
"***     " + bindate.get_hour() + "       # # #  " + bindate.get_month() + "\n" +
"* *                 # # #\n" +
"\n" +
" * *                ###\n" +
"* * *               #  #\n" +
"* * *  " + bindate.get_minute() + "       #  #  " + bindate.get_day() + "\n" +
"* * *               ###\n" +
"\n" +
"****                # # #\n" +
"**                  # # #\n" +
"  **   " + bindate.get_second() + "       # # #   " + bindate.get_day_of_week() + "\n" +
"****                 # #\n";
}

StringReporter::StringReporter(RGBMatrix *m) : RGBMatrixManipulator(m) {}

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

BinaryClockReporter::BinaryClockReporter(RGBMatrix *m) :
  StringReporter(m), BinaryClock() {}

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

LedClock::LedClock() : io() {
  if (!io.Init()) {
    throw std::runtime_error("Couldn't access GPIO pins.");
  }
  matrix = new RGBMatrix(&io);
  reporter = new BinaryClockReporter(matrix);
  updater = new DisplayUpdater(matrix);
  run();
}

LedClock::~LedClock() {
  delete updater;
  delete reporter;
  delete matrix;
}

void LedClock::run() {
  updater->Start(10);
  reporter->Start();
}
