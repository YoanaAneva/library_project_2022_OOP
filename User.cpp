#include "User.h"

User::User(const String& username, const String& password, const Date& regDate, const Date& lastVisit, const UserType type){
    this->type = type;
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
const UserType& User::getType() const{
    return this->type;
}

void User::writeInFile(std::ofstream& output) const{    
    output << (getType() == READER ? "R" : "A") << "]" << username << "|" << password << "|" << regDate << "|" << lastVisit << "|";
}

void User::readFromFile(std::ifstream& input){
    unsigned bufferLen = 1024;
    char buffer[bufferLen];
    String username, password;
    Date lastVisit, regDate;

    input.getline(buffer, bufferLen, '|');
    username = buffer;

    input.getline(buffer, bufferLen, '|');
    password = buffer;

    input >> regDate;
    input.get(buffer, 2);

    input >> lastVisit;
    input.get(buffer, 2);

    try{
        setUsername(username);
        setPassword(password);
        setLastVisit(lastVisit);
        setRegDate(regDate);
    }
    catch(const char* msg){
        std::cout << msg << std::endl;
        return;
    }
}

bool User::areSamePasswords(const String& p1, const String& p2){
    if(p1 != p2){
        std::cout << "This is not your password" << std::endl;
        return false;
    }
    return true;
}

void User::print() const{
    std::cout << username << "|" << password << "|" << regDate << "|" << lastVisit << "|";
}