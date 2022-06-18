#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include "String.h"
#include "Date.h"
#include "Paper.h"

class User{
protected:
    String username;
    String password;
    Date regDate;
    Date lastVisit;

public:
    User() = default;
    User(const String& username, const String& password, const Date& regDate, const Date& lastVisit);
    User(const User& other) = default;

    User& operator=(const User& other) = default;

    void setUsername(const String& username);
    void setPassword(const String& password);
    void setRegDate(const Date& regDate);
    void setLastVisit(const Date& lastVisit);

    const String& getUsername() const;
    const String& getPassword() const;
    const Date& getRegDate() const;
    const Date& getLastVisit() const;

    virtual void writeInFile(std::ofstream& output) const;

    // void add(BorrowedPaper* p);
    virtual User* clone() const = 0;
    virtual ~User() = default;

    virtual void print() const;
};

#endif