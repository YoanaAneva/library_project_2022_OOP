#include "Administrator.h"

Administrator::Administrator() : User(){
    this->type = ADMINISTRATOR;
}

Administrator::Administrator(const String& username, const String& password, const Date& regDate, const Date& lastVisit, const String& email, const String& department)
 : User(username, password, regDate, lastVisit, ADMINISTRATOR) {
    try{
        setEmail(email);
        setDepartment(department);
    }catch(const char* msg){
        std::cout << msg << std::endl;
        setEmail("Unknown");
        setDepartment("Unknown");
    }
}

void Administrator::setEmail(const String& email){
    if(!isValidEmail(email)){
        throw "Invalid email!";
    }
    this->email = email;
}

void Administrator::setDepartment(const String& department){
    if(!isValidDepartment(department)){
        throw "Invalid department";
    }
    this->department = department;
}

void Administrator::writeInFile(std::ofstream& output) const{
    User::writeInFile(output);
    output << email << "|" << department << "]\n\n";
}

void Administrator::readFromFile(std::ifstream& input){
    User::readFromFile(input);

    String email, department;
    unsigned bufferLen = 1024;
    char buffer[bufferLen];

    input.getline(buffer, bufferLen, '|');
    email = buffer;

    input.getline(buffer, bufferLen, ']');
    department = buffer;
    
    // input.get(buffer, 2);
    // input.getline(buffer, bufferLen);
    input.getline(buffer, bufferLen);
    input.getline(buffer, bufferLen);

    try{
        setEmail(email);
        setDepartment(department);
    }
    catch(const char* msg){
        std::cout << msg << std::endl;
        return;
    }
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
        return false;

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

bool Administrator::isValidDepartment(const String& department){
    if (department == "" || department == " "){
        std::cout << "Invalid value for department" << std::endl;
        return false;
    }
    for(int i = 0; i < department.getSize(); ++i){
        if((department[i] < 'A' || department[i] > 'Z') && (department[i] < 'a' || department[i] > 'z') && department[i] != ',' && department[i] != ' '){
            std::cout << "Invalid value for department" << std::endl;
            return false;
        }  
    }
    return true;
}
