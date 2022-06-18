#include "Date.h"
Date::Date(){
    // std::cout << "Default ctor for Date" << std::endl;
    setNow();
}

Date::Date(int year, int month, int day){
    try{
        setYear(year);
        setMonth(month);
        setDay(day);
    }
    catch(const char* msg){
        std::cout << msg << " Default values are going to be set!" << std::endl;
        setNow();
    }
}


void Date::setNow(){
    std::time_t now = std::time(0);
    std::tm* lTime = localtime(&now);
    this->year = 1900 + lTime->tm_year;
    this->month = 1 + lTime->tm_mon;
    this->day = lTime->tm_mday;
}

void Date::setYear(int year){
    if(year < 1500){
        throw "Invalid value for year!";
    }
    this->year = year;
}

void Date::setMonth(int month){
    if(month < 1 || month > 12){
        throw "Invalid value for month!";
    }
    this->month = month;
}

void Date::setDay(int day){
    if(day < 1 || (this->month == 2 && day > 29) || ((this->month == 4 || this->month == 6 || this->month == 9 || this->month == 11) && day > 30) || day > 31){
        throw "Invalid value for day!";
    }
    this->day = day;
}

unsigned Date::getYear() const { return this->year; }
unsigned Date::getMonth() const { return this->month; }
unsigned Date::getDay() const { return this->day; }

unsigned Date::getThisYear(){
    Date now;
    return now.year;
}
unsigned Date::getThisMonth(){
    Date now;
    return now.month;
}
unsigned Date::getThisDay(){
    Date now;
    return now.day;
}

Date Date::getNow(){
    Date now;
    return now;
} 

std::ostream& operator<<(std::ostream& output, const Date& date){
    output << date.year << '-' << (date.month < 10 ? "0" : "") << date.month << '-' << (date.day < 10 ? "0" : "") << date.day;
}

std::istream& operator>>(std::istream& input, Date& date){
    char buffer[2];
    unsigned year, month, day;
    input >> year;
    input.get(buffer, 2);
    input >> month;
    input.get(buffer, 2);
    input >> day;

    try{
        date.setYear(year);
        date.setMonth(month);
        date.setDay(day);
    }catch(const char* msg){
        std::cout << msg << std::endl;
    }

    return input;
}

bool Date::operator==(const Date& other){
    return (this->year == other.year && this->month == other.month && this->day == other.day);
}

bool Date::operator!=(const Date& other){
    return !(*this == other);
}

bool Date::operator<(const Date& other){
    if(this->year < other.year)
        return true;
    if(this->month < other.month && this->year == other.year)
        return true;
    if(this->day < other.day && this->month == other.month && this->year == other.year)
        return true;
    return false;
}

bool Date::operator<=(const Date& other){
    return (*this == other || *this < other);
}

bool Date::operator>(const Date& other){
    return !(*this <= other);
}

bool Date::operator>=(const Date& other){
    return (*this == other || *this > other);
}

bool Date::isValid(int year, int month, int day){
    if(year < 1500 || (year > Date::getThisYear() && Date::getThisMonth() != 12) || month < 1 || month > 12 || (month == 2 && day > 28) || ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) || day > 31){
        return false;
    }
    return true;
}

bool Date::isValidYear(const String& str){
    if(str[0] != '1' && str[0] != '2' || str.getSize() != 4)
        return false;
    for(int i = 1; i < 4; ++i){
        if(str[i] < '0' || str[i] > '9')
            return false;
    }
    if(String::convertToNumber(str) > Date::getThisYear())
        return false;

    return true;
}

bool Date::isValidMonth(const String& str){
    if(str[0] < '0' || str[0] > '9' || str[1] < '0' || str[1] > '9')
        return false;

    if(str.getSize() < 1 || str.getSize() > 2)
        return false;
    
    if(String::convertToNumber(str) < 1 || String::convertToNumber(str) > 12)
        return false;

    return true;
}

Date& Date::addMonth(){
    if(this->month == 12)
        this->year++;
    this->month++;
}  