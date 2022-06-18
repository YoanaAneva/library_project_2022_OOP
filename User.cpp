#include "User.h"

User::User(const String& username, const String& password, const Date& regDate, const Date& lastVisit){
    try{
        setUsername(username);
        setPassword(password);
        setRegDate(regDate);
        setLastVisit(lastVisit);
    }
    catch(const char* msg){
        std::cout << msg << std::endl;
        throw;
    }
}

void User::setUsername(const String& username){
    if(username.getData() == nullptr || username.getSize() == 0){
        throw "Invalid value for username!";
    }
    this->username = username;
}

void User::setPassword(const String& password){
    if(password.getData() == nullptr || password.getSize() == 0){
        throw "Invalid value for password!";
    }
    this->password = password;
}

// void User::add(BorrowedPaper* p){
//     return;
// }

void User::setRegDate(const Date& regDate){
    this->regDate = regDate;
}

void User::setLastVisit(const Date& lastVisit){
    this->lastVisit = lastVisit;
}

const String& User::getUsername() const {
    return this->username;
}
const String& User::getPassword() const{
    return this->password;
}
const Date& User::getRegDate() const{
    return this->regDate;
}
const Date& User::getLastVisit() const{
    return this->lastVisit;
}

void User::writeInFile(std::ofstream& output) const{    
    output << "[" << username << "|" << password << "|" << lastVisit << "|" << regDate << "|";
}

void User::print() const{
    std::cout << username << "|" << password << "|" << regDate << "|" << lastVisit << "|";
}