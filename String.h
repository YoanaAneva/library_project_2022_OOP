#ifndef String_H_INCLUDED
#define String_H_INCLUDED

#include <cstring>
#include <iostream>
#include <fstream>

class String{
private:
    char* data;
    unsigned size;

    void copy(const String& other);
    void erase();

public:
    String();
    String(const char* data);
    String(const String& other); 

    String& operator=(const String& str);

    ~String();

    const char operator[](int index) const;
    char& operator[](int index);

    unsigned getSize() const;
    const char* getData() const;

    friend std::ostream& operator<<(std::ostream& output, const String& str);
    friend std::istream& operator>>(std::istream& input, String& str);

    bool operator==(const String& other);
    bool operator!=(const String& other);
    friend bool operator==(const String& lhs, const String& rhs);
    friend bool operator!=(const String& lhs, const String& rhs);

    String& operator+=(const String& rhs);
    String& operator+=(char symbol);

    static int convertToNumber(const String& str);
    static String getSurname(const String& name);

    void writeInBin(std::ofstream& output);
    static void readFromBin(std::ifstream& input, String& str);
};

#endif

