#include "Administrator.h"

Administrator::Administrator(const String& username, const String& password, const Date& regDate, const Date& lastVisit, const String& email, const String& department) : User(username, password, regDate, lastVisit) {
    this->email = email;
    this->department = department;
}

User* Administrator::clone() const {
    return new Administrator(*this);
}

void Administrator::print() const {
    User::print();
    std::cout << email << "|" << department << std::endl;
}

bool Administrator::isValidEmail(const String& str){
    unsigned length = str.getSize();

    bool hasA = false;
    for(int i = 0; i < length; ++i)
        if(str[i] == '@'){
            hasA = true;
        }
    if(!hasA)
        return false;

    for(int i = 0; i < length; ++i){
        if(str[i] == '.' && str[i + 1] == '.')
            return false;
    }

    unsigned domainLen = 0; 
    for(int i = length - 1; str[i] != '@'; --i)
        domainLen++;

    unsigned localPartLen = length - domainLen - 1;

    if(localPartLen > 64)
        return false;

    if(str[0] == '.') 
        return true;


    //characters with restrictions - "(),:;<>@[\] 
    for(int i = 0; i < localPartLen; ++i){
        bool hasQuotationMark = false;
        if(str[i] == '"' || str[i] == '-' || str[i] == '(' || str[i] == ')' || str[i] == ',' || str[i] == ':' || str[i] == '<' || str[i] == '>' || str[i] == '@' || str[i] == '[' || str[i] ==']'){
            for(int j = 0; j < i; ++j){
                if(str[j] == '"')
                    hasQuotationMark = true;
            }
            if(!hasQuotationMark){
                return false;
            }

            hasQuotationMark = false;
            for(int j = i + 1; j < localPartLen; ++j){
                if(str[j] == '"'){
                    hasQuotationMark = true;
                }
            } 
            if(!hasQuotationMark){
                return false;
            }
        }
    }

    for(int i = localPartLen + 1; i < length; ++i){
        if((str[i] < 'A' || str[i] > 'Z') && (str[i] < '0' || str[i] > '9') && (str[i] < 'a' || str[i] > 'z') && str[i] != '.' && str[i] != '-')
            return false;
    }
    return true;
}