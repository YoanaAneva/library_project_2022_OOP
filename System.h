#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include "Reader.h"
#include "Administrator.h"

class System{
private:
    User** users;
    unsigned size;
    unsigned capacity;

    void copy(const System& other);
    void resize();
    void erase();
public:
    System();
    System(User** users, int usersCount);

    System(const System& other);
    System& operator=(const System& other);

    ~System();

    unsigned getSize() const;

    bool addUser(User* user);
    bool removeUser(const String& username);

    bool sameUsernameExists(const String& username);
    bool samePasswordExists(const String& password);

    void print() const;
};

#endif