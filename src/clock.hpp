#ifndef CLOCK_HPP_
#define CLOCK_HPP_

#include <string>

/**
 * A clock that reports time in binary.
 */
class BinaryDate {
public:
	BinaryDate();
	std::string get_year();
	std::string get_month();
	std::string get_day();
	std::string get_hour();
	std::string get_minute();
	std::string get_second();
	std::string get_day_of_week();
private:
	int year, month, day, hour, minute, second, day_of_week;
	void update_time();
};

#endif /* CLOCK_HPP_ */
