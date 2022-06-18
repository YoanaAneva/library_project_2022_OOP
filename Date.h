#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED
#include "String.h"

#include <iostream>
#include <ctime>

class Date{
private:
    unsigned year;
    unsigned month;
    unsigned day;

public:
    Date();
    Date(int day, int month, int year);
    Date(const Date& other) = default;

    void setNow();
    void setYear(int day);
    void setMonth(int month);
    void setDay(int day);

    unsigned getYear() const;
    unsigned getMonth() const;
    unsigned getDay() const;

    static unsigned getThisYear();
    static unsigned getThisMonth();
    static unsigned getThisDay();
    static Date getNow();

    Date& operator=(const Date& other) = default;
    ~Date() = default;

    friend std::ostream& operator<<(std::ostream&, const Date& date);
    friend std::istream& operator>>(std::istream&, Date& date);

    bool operator==(const Date& other);
    bool operator!=(const Date& other);
    bool operator<(const Date& other);
    bool operator<=(const Date& other);
    bool operator>(const Date& other);
    bool operator>=(const Date& other);

    static bool isValid(int year, int month, int day);
    static bool isValidYear(const String& str);
    static bool isValidMonth(const String& str);

    static unsigned convertToYearMonth(const String& str);

    Date& addMonth();
};

#endif