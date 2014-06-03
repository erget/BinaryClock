#include <time.h>
#include <string>
#include <bitset>

#include "clock.hpp"

/**
 * Initialize ``BinaryDate`` and get current time.
 */
BinaryDate::BinaryDate(): year(0), month(0), day(0), hour(0), minute(0),
second(0), day_of_week(0) {
	this->update_time();
}

/**
 * Update ``BinaryDate``s time slots to current system time.
 */
void BinaryDate::update_time() {
	time_t rawtime = time(NULL);
	tm * timeinfo = localtime(&rawtime);
	year = timeinfo->tm_year + 1900;
	month = timeinfo->tm_mon + 1;
	day = timeinfo->tm_mday;
	hour = timeinfo->tm_hour;
	minute = timeinfo->tm_min;
	second = timeinfo->tm_sec;
	day_of_week = timeinfo->tm_wday;
}

/**
 * Update time and report year in little endian binary.
 */
std::string BinaryDate::get_year() {
	update_time();
	return std::bitset<11>(year).to_string();
}

/**
 * Update time and report month in little endian binary.
 */
std::string BinaryDate::get_month() {
	update_time();
	return std::bitset<4>(month).to_string();
}

/**
 * Update time and report day of month in little endian binary.
 */
std::string BinaryDate::get_day() {
	update_time();
	return std::bitset<5>(day).to_string();
}

/**
 * Update time and report hour in little endian binary.
 */
std::string BinaryDate::get_hour() {
	update_time();
	return std::bitset<5>(hour).to_string();
}

/**
 * Update time and report minute in little endian binary.
 */
std::string BinaryDate::get_minute() {
	update_time();
	return std::bitset<6>(minute).to_string();
}

/**
 * Update time and report second in little endian binary.
 */
std::string BinaryDate::get_second() {
	update_time();
	return std::bitset<6>(second).to_string();
}

/**
 * Update time and report day of week in little endian binary.
 */
std::string BinaryDate::get_day_of_week() {
	update_time();
	return std::bitset<3>(day_of_week).to_string();
}
