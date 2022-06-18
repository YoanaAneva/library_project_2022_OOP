#include "System.h"

void System::copy(const System& other){
    this->capacity = other.capacity;
    this->size = other.size;

    this->users = new User*[capacity];
    for(int i = 0; i < size; ++i){
        this->users[i] = other.users[i]->clone();
    }
}

void System::resize(){
    capacity *= 2;

    User** bigger = new User*[capacity];
    for(int i = 0; i < size; ++i){
        bigger[i] = users[i]->clone();
    }

    erase();
    this->users = bigger;
}

void System::erase(){
    for(int i = 0; i < size; ++i){
        delete users[i];
    }
    delete[] users;
}

System::System(){
    this->capacity = 16;
    this->size = 0;

    this->users = new User*[capacity];
}

System::System(User** users, int usersCount){
    this->capacity = usersCount + 64;
    this->size = usersCount;

    this->users = new User*[capacity];
    for(int i = 0; i < size; ++i){
        this->users[i] = users[i]->clone();
    }
}

System::System(const System& other){
    copy(other);
}

System& System::operator=(const System& other){
    if(this != &other){
        erase();
        copy(other);
    }
    return *this;
}

System::~System(){
    erase();
}

unsigned System::getSize() const { return this->size; }

bool System::addUser(User* user){
    if(size >= capacity){
        resize();
    }

    users[size] = user->clone();
    ++size;
    return true;
}

bool System::removeUser(const String& username){
    if(!sameUsernameExists(username)){
        std::cout << "No user with username: " << username << " exists in our system!" << std::endl;
        return false;
    }

    for(int i = 0; i < size; ++i){
        if(users[i]->getUsername() == username){
            for(int j = i; j < size - 1; ++j){
                users[j] = users[j + 1]->clone();
            }
        }
    }
    --size;
    return true;
}


bool System::sameUsernameExists(const String& username){
    for(int i = 0; i < size; ++i){
        if(users[i]->getUsername() == username)
            return true;
    }
    return false;
}

bool System::samePasswordExists(const String& password){
    for(int i = 0; i < size; ++i){
        if(users[i]->getPassword() == password)
            return true;
    }
    return false;
}

void System::print() const {
    for(int i = 0; i < size; ++i){
        users[i]->print();
    }
}

