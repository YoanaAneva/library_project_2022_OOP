#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include "Library.h"
#include "UserBase.h"
#include "Commands.h"

class System{
private:
    Library library;
    UserBase userBase;

    System(const System& other);
    System& operator=(const System& other);

public:
    System() = default;

    void getCommands();
};

#endif