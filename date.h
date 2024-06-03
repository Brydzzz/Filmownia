#pragma once
#include <iostream>
class Date {
   private:
    unsigned int day = 1;
    unsigned int month = 1;
    unsigned int year = 1970;
    bool isValidDate(unsigned int day, unsigned int month,
                     unsigned int year) const;
    unsigned int daysInMonth(unsigned int month, unsigned int year) const;
    bool isLeapYear(unsigned int year) const;

   public:
    Date() = default;
    Date(unsigned int day, unsigned int month, unsigned int year);
    unsigned int getDay() const;
    unsigned int getMonth() const;
    unsigned int getYear() const;
    bool isEqualOrGreater(const Date& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Date& d);
    friend std::istream& operator>>(std::istream& is, Date& d);
};
