#include "Userbase.h"

void UserBase::copy(const UserBase& other){
    this->usersCapacity = other.usersCapacity;
    this->usersCount = other.usersCount;

    this->users = new User*[usersCapacity];
    for(int i = 0; i < usersCount; ++i){
        this->users[i] = other.users[i]->clone();
    }
    this->firstAdminInd = other.firstAdminInd;

    this->hasLoggedIn = other.hasLoggedIn;
    this->loggedUser = other.loggedUser;
}

void UserBase::resize(){
    usersCapacity *= 2;

    User** bigger = new User*[usersCapacity];
    for(int i = 0; i < usersCount; ++i){
        bigger[i] = users[i]->clone();
    }

    erase();
    this->users = bigger;
}

void UserBase::erase(){
    for(int i = 0; i < usersCount; ++i){
        delete users[i];
    }
    delete[] users;
    delete loggedUser;
}

UserBase::UserBase(){
    this->usersCapacity = 16;
    this->usersCount = 1;

    this->users = new User*[usersCapacity];

    Date regDate(2020, 12, 3);
    Date lastVisit(2022, 6, 21);
    this->users[0] = new Administrator("admin", "i<3c++", regDate, lastVisit, "admin@gmail.com", "Computer Science");
    this->firstAdminInd = 0;

    this->hasLoggedIn = false;
    this->loggedUser = nullptr;
}

// UserBase::UserBase(User** users, int usersCount){
//     this->usersCapacity = usersCount + 8;
//     this->usersCount = usersCount;

//     this->users = new User*[usersCapacity];
//     for(int i = 0; i < usersCount; ++i){
//         this->users[i] = users[i]->clone();
//     }
//     this->hasLoggedIn = false;
//     this->loggedUser = nullptr;
// }

UserBase::UserBase(const UserBase& other){
    copy(other);
}

UserBase& UserBase::operator=(const UserBase& other){
    if(this != &other){
        erase();
        copy(other);
    }
    return *this;
}

UserBase::~UserBase(){
    erase();
}

User* UserBase::operator[](int index) const{
    return this->users[index];
}

void UserBase::setHasLoggedIn(bool hasLoggedIn){
    this->hasLoggedIn = hasLoggedIn;
}
void UserBase::logUser(const User* user){
    this->loggedUser = user->clone();
}

unsigned UserBase::getUsersCount() const { return this->usersCount; }
bool UserBase::showIfHasLoggedIn() const{ return this->hasLoggedIn; }
User* UserBase::getLoggedUser() const {return this->loggedUser; }
unsigned UserBase::getFirstAdminInd() const { return this->firstAdminInd; }

void UserBase::addUser(User* newUser){
    if(usersCount >= usersCapacity + 1){
        resize();
    }

    if(newUser->getType() == READER){
        for(int i = usersCount; i > firstAdminInd; --i){
            users[i] = users[i - 1];
        }
        users[firstAdminInd] = newUser->clone();
        ++usersCount;
        ++firstAdminInd;
        return;
    }

    if(newUser->getType() == ADMINISTRATOR){
        users[usersCount] = newUser->clone();
        ++usersCount;
    }
}

bool UserBase::removeUser(const String& username){
    if(!sameUsernameExists(username)){
        std::cout << "No user with username: " << username << " exists in our system!" << std::endl;
        return false;
    }

    for(int i = 0; i < usersCount; ++i){
        if(users[i]->getUsername() == username){
            for(int j = i; j < usersCount - 1; ++j){
                users[j] = users[j + 1]->clone();
            }
        }
    }
    --usersCount;
    return true;
}

void UserBase::writeInFile() const{
    std::ofstream output("users.txt");

    if(!output){
        std::cout << "Cannot open file users.txt for writing!" << std::endl;
        return;
    }

    for(int i = 0; i < usersCount; ++i){
        output << "[";
        users[i]->writeInFile(output);
    }

    output.close();
}

void UserBase::readFromFile(){
    std::ifstream input("users.txt");

    if(!input){
        std::cout << "Cannot open file users.txt for reading!" << std::endl;
        return;
    }

    unsigned bufferLen = 1024;
    char buffer[bufferLen];
    while(input){
        input.get(buffer, 2);
        input.getline(buffer, bufferLen, ']');
        if(buffer[0] == 'R'){
            User* newUser = new Reader();
            newUser->readFromFile(input);
            addUser(newUser);
        }
        if(buffer[0] == 'A'){
            User* newUser = new Administrator();
            newUser->readFromFile(input);
            addUser(newUser);
        }
    }
}

bool UserBase::sameUsernameExists(const String& username){
    for(int i = 0; i < usersCount; ++i){
        if(users[i]->getUsername() == username)
            return true;
    }
    return false;
}

bool UserBase::samePasswordExists(const String& password){
    for(int i = 0; i < usersCount; ++i){
        if(users[i]->getPassword() == password)
            return true;
    }
    return false;
}

void UserBase::print() const {
    for(int i = 0; i < usersCount; ++i){
        std::cout << "position: " << i << std::endl;
        users[i]->print();
        std::cout << std::endl;
    }
}

