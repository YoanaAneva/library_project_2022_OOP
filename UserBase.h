#ifndef USERBASE_H_INCLUDED
#define USERBASE_H_INCLUDED

#include "Reader.h"
#include "Administrator.h"


///Клас, който съхранява информацията за всички потребители на библиотеката. Съдържа полиморфен контейнер от тип User*. 
///Може да се разглежда като саморазширяващ се масив от различни типове потребители, които се съхраняват сортирани по тип.
///@param users хетерогенен контейнер от тип User*, съхраняващ потребителите @param usersCount броят на потребителите в полиморфния контейнер @param usersCapacity капацитетът на полиморфния контейнер
/// @param firstAdminInd указва индекса на първия администратор в масива @param hasLoggedIn указва дали в системата има логнат потребител @param loggedUser указател към логнатия потребител
class UserBase{
private:
    User** users;
    unsigned usersCount;
    unsigned usersCapacity;

    bool hasLoggedIn;
    User* loggedUser;

    unsigned firstAdminInd;

private:
    void copy(const UserBase& other);
    void resize();
    void erase();

public:
    ///Задава капацитета и заделя толкава памет за полиморфния контейнер. Създава един регистриран администратор.
    ///При създаването на обекта няма логнат потребител.
    UserBase();

    ///Копиращ конструктор, използва функцията copy(), която за this->users[i] създава копие на данните, към които сочи всеки от указателите на other.users[i]. 
    ///****************************************************************************
    ///for(int i = 0; i < other.usersCount; ++i)           
    ///    this->users[i] = other.users[i]->clone();    
    ///****************************************************************************
    UserBase(const UserBase& other);

    UserBase& operator=(const UserBase& other);

    ///Изтрива указателите към всеки един обект и след това изтрива указателят към масива.
    ~UserBase();

    ///Предефинира оператора []. Връща указател от тип User*, т.е. елемета от масива User** users с посочения индекс.
    User* operator[](int index) const;

    void setHasLoggedIn(bool hasLoggedIn);
    void logInUser(const User* user);
    void logOutUser();

    unsigned getUsersCount() const;
    bool showIfHasLoggedIn() const;
    User* getLoggedUser() const;
    unsigned getFirstAdminInd() const;

    ///Функция, която добавя нов потребител към полиморфния контейнер. Ако е читател се добавя непосредствено след първия администратор,
    /// ако е администратор се добавя в края.
    void addUser(User* user);
    
    ///Премахва потребител от системата по подадено потребителско име. Ако такъв не е намерен се извежда съобщение. 
    ///Премахването става като всеки указател след този към потребителя се пренасочват към това, което е сочил предходния.
    bool removeUser(const String& username);

    
    ///Функция, която записва във файла, определен да съхранява данните за потребителите, информацията за всеки един потребител. 
    ///Проверява се дали състоянието на потокът е различно от "good". Всеки елемент от масива използва своя метод за записване във файл с подадения поток.
    void writeInFile() const;

    ///Функция, която приема поток и "зарежда" данни от съответния текстов файл. Първо се изчита символът('R'/'A'), указващ типа на съответния потребител.
    ///След това се създава потребител от съответния тип, изчитат се данните му от файла и се добавя в масива.
    void readFromFile(std::ifstream& input);

    ///Масивът се обхожда и се проверява дали вече съществува потребител със същото потребителско име.
    bool sameUsernameExists(const String& username);
    ///Масивът се обхожда и се проверява дали вече съществува потребител със същата парола.
    bool samePasswordExists(const String& password);

    ///За всеки потребител се извиква съответната функция print().
    void print() const;
};

#endif