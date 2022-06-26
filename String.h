#ifndef String_H_INCLUDED
#define String_H_INCLUDED

#include <cstring>
#include <iostream>
#include <fstream>

///Клас представляващ текст, с различни удобни свойства
class String{
private:
    char* data;
    unsigned size;

    void copy(const String& other);
    void erase();

public:
    String();
    ///Копира данните на подадения const char* в this->data, като заделя точното колечиство памет, задава размера спрямо дължината на параметъра.
    String(const char* data);
    ///Използва функцията copy(), която копира размера и данните на other.
    String(const String& other); 

    ///Проверява се дали подаденият обект е различен от текущият, преди да се освободи заделената памет за масива и да се извика copy. 
    String& operator=(const String& str);

    ///Освобождава заделената памет.
    ~String();

    ///Константният вариант на оператора []. Връща елементът на подадената позиция, той е константа. 
    const char operator[](int index) const;
    ///Неконстантният вариант на оператора []. Връща елементът на подадената позиция. Използва се в случаи като str[0] = 's'.
    char& operator[](int index);

    unsigned getSize() const;
    const char* getData() const;

    ///Предефинира оператора ""<<" за извеждане на данните на обект от тип String. Използва се при записване във файл и извеждане на текста в конзолата. Връща се промененият поток.
    friend std::ostream& operator<<(std::ostream& output, const String& str);
    ///Предефинира оператора ">>" за четене на данните на обект от тип String. Използва се при четене на дата от файл и от стандартния изход. Връща се промененият поток.
    friend std::istream& operator>>(std::istream& input, String& str);

    ///Предефинира оператора "==", който сравнява дали данните на нашия обект са същите като тези на обекта отдясно на равното.
    bool operator==(const String& other);
    ///Използва предефинирания оператор "==", сравнява дали данните на нашия обект са различни от тези на обекта отдясно на равното.
    bool operator!=(const String& other);
    ///Предефинира оператора "==", който сравнява дали данните на обекта отляво са същите като тези на обекта отдясно на равното.
    friend bool operator==(const String& lhs, const String& rhs);
    ///Използва предефинирания оператор "==", като сравнява дали данните на обекта отляво са различни от тези на обекта отдясно на равното.
    friend bool operator!=(const String& lhs, const String& rhs);

    ///Добавя нов обект от тип String към нашия обект, променя размера.
    String& operator+=(const String& rhs);
    ///Добавя нов символ към нашия обект, променя размера.
    String& operator+=(char symbol);

    ///Статична функция, която проверява дали подаденият параметър е положително число, ако не е връща -1.
    static int convertToNumber(const String& str);
    ///Статична функция, която връща последното име от подадения String.
    static String getSurname(const String& name);
};

#endif

