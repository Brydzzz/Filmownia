#include "date.h"

#include <iomanip>
#include <stdexcept>

Date::Date(unsigned int day, unsigned int month, unsigned int year) {
    if (!isValidDate(day, month, year))
        throw std::invalid_argument("Invalid date");
    this->day = day;
    this->month = month;
    this->year = year;
}

unsigned int Date::getDay() const { return day; }

unsigned int Date::getMonth() const { return month; }

unsigned int Date::getYear() const { return year; }

unsigned int Date::daysInMonth(unsigned int month, unsigned int year) const {
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 ||
        month == 10 || month == 12) {
        return 31;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    } else if (month == 2) {
        if (isLeapYear(year))
            return 29;
        else
            return 28;
    } else {
        return 0;
    }
}

bool Date::isLeapYear(unsigned int year) const {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

bool Date::isValidDate(unsigned int day, unsigned int month,
                       unsigned int year) const {
    if (month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }
    if (day > daysInMonth(month, year)) {
        return false;
    }
    return true;
}

bool Date::isEqualOrGreater(const Date& other) const {
    if (year > other.year)
        return true;
    else if (year == other.year && month > other.month)
        return true;
    else if (year == other.year && month == other.month && day >= other.day)
        return true;
    return false;
}

std::ostream& operator<<(std::ostream& os, Date const& d) {
    os << std::setw(2) << std::setfill('0') << d.getDay() << '/';
    os << std::setw(2) << std::setfill('0') << d.getMonth() << '/';
    os << d.getYear();
    return os;
}
