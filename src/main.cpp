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

#include <iostream>
#include <unistd.h>
#include "led-clock.hpp"
#include "../external/rpi-rgb-led-matrix/led-matrix.h"

/*
 * Initialize GPIO pins and RGB matrix, then create and run LedClock.
 */
int main(int argc, char *argv[]) {
  GPIO io;
  if (!io.Init()) {
    std::cerr << "Couldn't access GPIO pins." << std::endl;
    return 1;
  }
  RGBMatrix matrix(&io);
  LedClock clock(matrix);
  clock.run();
  getchar();
  return 0;
}
