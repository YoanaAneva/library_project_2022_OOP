#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include "String.h"

#include <iostream>
#include <ctime>

///Клас обединяващ информацията за една дата, чиято цел е да улесни работата с дати.
class Date{
private:
    unsigned year;
    unsigned month;
    unsigned day;

public:
    ///Датата по подразбиране е сегашната дата.
    Date();
    Date(int day, int month, int year);
    Date(const Date& other) = default;

    ///Задаване на текущата дата.
    void setNow();
    void setYear(int day);
    void setMonth(int month);
    void setDay(int day);

    unsigned getYear() const;
    unsigned getMonth() const;
    unsigned getDay() const;

    ///Връща текущата година.
    static unsigned getThisYear();
    ///Връща текущия месец.
    static unsigned getThisMonth();
    ///Връща текущия ден.
    static unsigned getThisDay();
    ///Връща текущата дата.
    static Date getNow();

    ///Предефинира оператора ""<<" за извеждане на данните на обект от тип Date. Използвам го при записване във файл и извеждане на дата в конзолата.
    ///Датата се извежда във формат "yyyy-mm-dd".
    friend std::ostream& operator<<(std::ostream&, const Date& date);
    ///Предефинира оператора ">>" за четене на данните на обект от тип Date. Използвам го при четене на дата от файл и от стандартния изход.
    ///buffer ce използва за четенето на ненужните символи и местетено на указателя.
    friend std::istream& operator>>(std::istream&, Date& date);

    friend bool operator==(const Date& lhs, const Date& rhs);
    friend bool operator!=(const Date& lhs, const Date& rhs);
    friend bool operator<(const Date& lhs, const Date& rhs);
    friend bool operator<=(const Date& lhs, const Date& rhs);
    friend bool operator>(const Date& lhs, const Date& rhs);
    friend bool operator>=(const Date& lhs, const Date& rhs);

    ///Функция, която валидира датата.
    static bool isValid(int year, int month, int day);
    ///Функция, която приема string и проверява дали е валидна година. Тази специфична функция влиза в употреба при валидирането на данни от потребителя за обект от тип Series.
    static bool isValidYear(const String& str);
    ///Функция, която приема string и проверява дали е валиден месец. Тази специфична функция влиза в употреба при валидирането на данни от потребителя за обект от тип Series.
    static bool isValidMonth(const String& str);

    ///Функция, която добавя месец към обекта, използва се при задаването на дата за връщане.
    Date& addMonth();
    ///Функция, която премахва месец от обекта.
    Date& removeMonth();
    ///Функция, която преобразува обект от тип String към обект от тип Date. Ако са подадени само месец и година, задава подразбираща се стойност на деня. Използва се за сравняването на дати при обекти от тип Series.
    static::Date convertToDate(const String& str);
};

#endif