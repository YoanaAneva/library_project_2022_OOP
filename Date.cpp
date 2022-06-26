#include "Date.h"
Date::Date(){
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

bool operator==(const Date& lhs, const Date& rhs){
    return (lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day);
}

bool operator!=(const Date& lhs, const Date& rhs){
    return !(lhs == rhs);
}

bool operator<(const Date& lhs, const Date& rhs){
    if(lhs.year < rhs.year)
        return true;
    if(lhs.month < rhs.month && lhs.year == rhs.year)
        return true;
    if(lhs.day < rhs.day && lhs.month == rhs.month && lhs.year == rhs.year)
        return true;
    return false;
}

bool operator<=(const Date& lhs, const Date& rhs){
    return (lhs == rhs || lhs < rhs);
}

bool operator>(const Date& lhs, const Date& rhs){
    return !(lhs <= rhs);
}

bool operator>=(const Date& lhs, const Date& rhs){
    return (lhs == rhs || lhs > rhs);
}

bool Date::isValid(int year, int month, int day){
    if(year < 1500 || (year > Date::getThisYear() && Date::getThisMonth() != 12) || month < 1 || month > 12 || (month == 2 && day > 28) || ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) || day > 31){
        return false;
    }
    return true;
}

bool Date::isValidYear(const String& str){
    if(str[0] != '1' && str[0] != '2' || str.getSize() != 4){
        std::cout << "\nInvalid value for year\n\n";
        return false;
    }
    for(int i = 1; i < 4; ++i){
        if(str[i] < '0' || str[i] > '9'){
            std::cout << "\nInvalid value for year\n\n";
            return false;
        }
    }
    if(String::convertToNumber(str) > Date::getThisYear()){
        std::cout << "\nInvalid value for year\n\n";
        return false;
    }

    return true;
}

bool Date::isValidMonth(const String& str){
    if(str.getSize() == 1 && (str[0] < '1' || str[0] > '9')){
        std::cout << "\nInvalid value for month\n\n";
        return false;
    }
    if(str.getSize() == 2){
        if(str[0] != '0' && str[0] != '1'){
            std::cout << "\nInvalid value for month\n\n";
            return false;
        }
        if(str[0] == '0' && (str[1] < '1' || str[1] > '9')){
            std::cout << "\nInvalid value for month\n\n";
            return false;
        }
        if(str[0] == '1' && str[1] != '1' && str[1] != '2'){
            std::cout << "\nInvalid value for month\n\n";
            return false;
        }
    }
    if(str.getSize() > 2){
        std::cout << "\nInvalid value for month\n\n";
        return false;
    }
    
    return true;
}

Date& Date::addMonth(){
    if(this->month == 12)
        this->year++;
    this->month++;
} 
Date& Date::removeMonth(){
    if(this->month == 1)
        this->year--;
    this->month--;
} 

Date Date::convertToDate(const String& str){
    String dayStr, monthStr, yearStr;
    int dashesCout = 0, year, month, day;

    for(int i = 0; i < str.getSize(); ++i){
        if(str[i] == '-')
            dashesCout++;
    }

    int i = 0;
    for(; str[i] != '-'; ++i){
        yearStr += str[i];
    }
    year = String::convertToNumber(yearStr);

    ++i;

    if(dashesCout == 2){
        for(; str[i] != '-'; ++i){
            monthStr += str[i];
        }
        month = String::convertToNumber(monthStr);

        ++i;

        for(; i < str.getSize(); ++i){
            dayStr += str[i];
        }
        day = String::convertToNumber(dayStr);

        return Date(year, month, day);
    }

    for(; i < str.getSize(); ++i){
        monthStr += str[i];
    }
    month = String::convertToNumber(monthStr);      
   
    return Date(year, month, 1);
}