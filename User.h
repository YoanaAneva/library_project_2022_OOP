#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include "String.h"
#include "Date.h"
#include "Paper.h"

enum UserType{
    DUMMY,
    READER,
    ADMINISTRATOR
};

class User{
protected:
    String username;
    String password;
    Date regDate;
    Date lastVisit;

    UserType type;

public:
    User() = default;
    User(const String& username, const String& password, const Date& regDate, const Date& lastVisit, const UserType type);
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
    const UserType& getType() const;

    virtual void writeInFile(std::ofstream& output) const;
    virtual void readFromFile(std::ifstream& input);

    // void add(BorrowedPaper* p);
    virtual User* clone() const = 0;
    virtual ~User() = default;

    static bool areSamePasswords(const String& p1, const String& p2);

    virtual void print() const;

    void test();
};

#endif