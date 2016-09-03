#include <iostream>
#include <string>
#include <sstream>
#include "Date.hpp"

using std::stringstream;
Date::Date() {
	m_year = 0;
	m_month = 0;
	m_day = 0;
	m_hour = 0;
	m_minute = 0;
}

Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute) {
	m_year = t_year;
	m_month = t_month;
	m_day = t_day;
	m_hour = t_hour;
	m_minute = t_minute;
}


Date::Date(std::string dateString) {
  (*this) = stringToDate(dateString);
}

int Date::getYear(void) const {
  return m_year;
}

void Date::setYear(const int t_year) {
		m_year = t_year;
}

int Date::getMonth(void) const {
	return m_month;
}

void Date::setMonth(const int t_month) {
	m_month = t_month;
}

int Date::getDay(void) const {
	return m_day;
}

void Date::setDay(const int t_day) {
	m_day = t_day;
}

int Date::getHour(void) const {
	return m_hour;
}

void Date::setHour(const int t_hour) {
	m_hour = t_hour;
}

int Date::getMinute(void) const {
	return m_minute;
}

void Date::setMinute(const int t_minute) {
	m_minute = t_minute;
}

bool Date::isValid(const Date t_date) {
	
	if (t_date.getYear() < 1000 || t_date.getYear() > 9999) return false;
	if (t_date.getMonth() < 0 || t_date.getMonth() > 12) return false;
	//juding days whether fits

	if (t_date.getMonth() % 2 != 0 && t_date.getMonth() < 8) {
		if (t_date.getDay() < 0 || t_date.getDay() > 31) return false;
	}
	if (t_date.getMonth() % 2 != 0 && t_date.getMonth() > 8) {
		if (t_date.getDay() < 0 || t_date.getDay() > 30) return false;
	}
	if (t_date.getMonth() % 2 == 0 && t_date.getMonth() >= 8 &&
	  t_date.getMonth() != 2) {
		if (t_date.getDay() < 0 || t_date.getDay() > 31) return false;
	}
	if (t_date.getMonth() % 2 == 0 && t_date.getMonth() < 8 &&
	  t_date.getMonth() != 2) {
		if (t_date.getDay() < 0 || t_date.getDay() > 30) return false;
	}
	if (t_date.getMonth()  == 2) {
		if (t_date.getYear() % 4 == 0 && t_date.getYear() % 100 != 0) {
			if (t_date.getDay() < 0 || t_date.getDay() > 29) return false;
		} else if (t_date.getYear() % 400 == 0) {
			if (t_date.getDay() < 0 || t_date.getDay() > 29) return false;
		} else {
			if (t_date.getDay() < 0 || t_date.getDay() > 28) return false;
		}
		
	}
	//end of days judgement
	if (t_date.getHour() < 0 || t_date.getHour() > 23) return false;
	if (t_date.getMinute() < 0 || t_date.getMinute() > 59) return false;
	return true;
}
	

Date Date::stringToDate(const std::string t_dateString) {
	int i = 0;
	if (t_dateString.length() != 16) {
		Date newone;
		return newone;
	}
	for (i = 0; i < 16; i++) {
		if (i == 4 || i == 7 || i == 10 || i == 13) continue;
		if (t_dateString[i] < '0' || t_dateString[i] > '9') {
			Date newone;
			return newone;
		}
	}
	if (t_dateString[4]!='-' || t_dateString[7]!='-' || t_dateString[10]!='/'
	|| t_dateString[13] != ':') {
			Date newone;
			return newone;
	}
	Date newone;
	newone.setYear((t_dateString[0]-'0')*1000+(t_dateString[1]-'0')*100+(t_dateString[2]-'0')*10+(t_dateString[3]-'0'));
	newone.setMonth((t_dateString[5]-'0')*10+(t_dateString[6]-'0'));
	newone.setDay((t_dateString[8]-'0')*10+(t_dateString[9]-'0'));
	newone.setHour((t_dateString[11]-'0')*10+(t_dateString[12]-'0'));
	newone.setMinute((t_dateString[14]-'0')*10+(t_dateString[15]-'0'));
	return newone;
}

std::string Date::dateToString(Date t_date) {
	if (isValid(t_date)) {
		stringstream sstr, s2, s3, s4, s5;
	std::string str, upmon, upday, upmin, uphour;
	sstr << t_date.getYear();
	sstr >> str;
	if (str == "0") str += "000";
	s2 << t_date.getMonth();
	s2 >> upmon;
	str += '-';
	if (t_date.getMonth() < 10) str += '0';
	str += upmon;
	s3 << t_date.getDay();
	s3 >> upday;
	str += '-';
	if (t_date.getDay() < 10) str += '0';
	str += upday;
	s4 << t_date.getHour();
	s4 >> uphour;
	str += '/';
	if (t_date.getHour() < 10) str += '0';
	str += uphour;
	s5 << t_date.getMinute();
	s5 >> upmin;
	str += ':';
	if (t_date.getMinute() < 10) str += '0';
	str += upmin;
	return str;
	} else {
		return ("0000-00-00/00:00");
	}
}

Date& Date::operator=(const Date &t_date) {
	m_year = t_date.getYear();
	m_month = t_date.getMonth();
	m_day = t_date.getDay();
	m_hour = t_date.getHour();
	m_minute = t_date.getMinute();
	return (*this);
}

bool Date::operator==(const Date &t_date) const {
	if (m_year != t_date.getYear()) return false;
	if (m_month != t_date.getMonth()) return false;
	if (m_day != t_date.getDay()) return false;
	if (m_hour != t_date.getHour()) return false;
	if (m_minute != t_date.getMinute()) return false;
	return true;
}

bool Date::operator>(const Date &t_date) const {
	if (m_year < t_date.getYear()) {
		return false;
	} else if (m_year > t_date.getYear()) {
		return true;
	} else {
		if (m_month < t_date.getMonth()) {
			return false;
		} else if (m_month > t_date.getMonth()) {
			return true;
		} else {
			if (m_day < t_date.getDay()) {
				return false;
			} else if (m_day >t_date.getDay()) {
				return true;
			} else {
				if (m_hour < t_date.getHour()) {
					return false;
				} else if (m_hour > t_date.getHour()) {
					return true;
				} else {
					if (m_minute <= t_date.getMinute()) {
						return false;
					}
					return true;
				}
			}
		}
	}
}

bool Date::operator<(const Date &t_date) const {
	if (((*this)==t_date) || ((*this) > t_date)) return false;
	return true;
}

bool Date::operator>=(const Date &t_date) const {
	if (((*this)==t_date) || ((*this) > t_date)) return true;
	return false;
}


bool Date::operator<=(const Date &t_date) const {
	if ((*this) > t_date) return false;
	return true;
}




