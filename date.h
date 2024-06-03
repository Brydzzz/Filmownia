#pragma once
#include <iostream>
class Date {
   private:
    unsigned int day;
    unsigned int month;
    unsigned int year;
    bool isValidDate(unsigned int day, unsigned int month,
                     unsigned int year) const;
    unsigned int daysInMonth(unsigned int month, unsigned int year) const;
    bool isLeapYear(unsigned int year) const;

   public:
    Date(unsigned int day, unsigned int month, unsigned int year);
    unsigned int getDay() const;
    unsigned int getMonth() const;
    unsigned int getYear() const;
    bool isEqualOrGreater(const Date& other) const;
    friend std::ostream& operator<<(std::ostream& os, Date const& d);
    // TODO implement operator>>
};
