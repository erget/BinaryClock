/*
 * Testing ground for the binary clock.
 */

#include "led-clock.hpp"

int main(int argc, char *argv[]) {
	LedClock led;
	led.Start(10);
	return 0;
}
