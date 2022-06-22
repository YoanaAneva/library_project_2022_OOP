#ifndef ADMINISTRATOR_H_INCLUDED
#define ADMINISTRATOR_H_INCLUDED

#include "User.h"

class Administrator : public User {
private:
    String email;
    String department;
public:
    Administrator();

    Administrator(const String& username, const String& password, const Date& regDate, const Date& lastVisit, const String& email, const String& department);
    Administrator(const Administrator& other) = default;

    Administrator& operator=(const Administrator& other) = default;

    ~Administrator() = default;

    void setEmail(const String& email);
    void setDepartment(const String& department);

    virtual void writeInFile(std::ofstream& output) const override;
    virtual void readFromFile(std::ifstream& input) override;

    virtual User* clone() const override;
    virtual void print() const override;

    static bool isValidEmail(const String& str);
    static bool isValidDepartment(const String& department);
};

#endif