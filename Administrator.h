#ifndef ADMINISTRATOR_H_INCLUDED
#define ADMINISTRATOR_H_INCLUDED

#include "User.h"

class Administrator : public User {
private:
    String email;
    String department;
public:
    Administrator() = default;

    Administrator(const String& username, const String& password, const Date& regDate, const Date& lastVisit, const String& email, const String& department);
    Administrator(const Administrator& other) = default;

    Administrator& operator=(const Administrator& other) = default;

    ~Administrator() = default;

    virtual User* clone() const override;
    virtual void print() const override;

    bool isValidEmail(const String& str);
};

#endif