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
