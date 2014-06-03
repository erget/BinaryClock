/*
 * Testing ground for the binary clock.
 */

#include <iostream>
#include "led-clock.hpp"

int main(int argc, char *argv[]) {
	BinaryClock clock;
	std::cout << clock.report_time() << std::endl;
	return 0;
}
