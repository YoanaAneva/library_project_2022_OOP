#ifndef USERBASE_H_INCLUDED
#define USERBASE_H_INCLUDED

#include "Reader.h"
#include "Administrator.h"

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
    UserBase();
    // UserBase(User** users, int usersCount);

    UserBase(const UserBase& other);
    UserBase& operator=(const UserBase& other);

    ~UserBase();

    User* operator[](int index) const;

    void setHasLoggedIn(bool hasLoggedIn);
    void logUser(const User* user);

    unsigned getUsersCount() const;
    bool showIfHasLoggedIn() const;
    User* getLoggedUser() const;
    unsigned getFirstAdminInd() const;

    void addUser(User* user);
    bool removeUser(const String& username);

    void writeInFile() const;
    void readFromFile();

    bool sameUsernameExists(const String& username);
    bool samePasswordExists(const String& password);

    void print() const;
};

#endif