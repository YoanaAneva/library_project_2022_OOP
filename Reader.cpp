#include "Reader.h"

void Reader::copy(const Reader& other){
    this->capacity = other.capacity;
    this->size = other.size;

    this->borrowedItems = new BorrowedPaper[capacity];
    for(int i = 0; i < size; ++i){
        this->borrowedItems[i] = other.borrowedItems[i];
    }
}

void Reader::resize(){
    this->capacity *= 2;

    BorrowedPaper* bigger = new BorrowedPaper[capacity];
    for(int i = 0; i < size; ++i){
        bigger[i] = this->borrowedItems[i];
    }

    erase();
    this->borrowedItems = bigger;
}

void Reader::erase(){
    delete[] this->borrowedItems;
}

Reader::Reader() : User() {
    this->capacity = 8;
    this->size = 0;

    this->borrowedItems = new BorrowedPaper[capacity];
}

Reader::Reader(const String& username, const String& password, const Date& regDate, const Date& lastVisit) : User(username, password, regDate, lastVisit){
    this->capacity = 8;
    this->size = 0;

    this->borrowedItems = new BorrowedPaper[capacity];
}

Reader::Reader(const Reader& other) : User(other){
    copy(other);
}

Reader& Reader::operator=(const Reader& other){
    if(this != &other){
        erase();
        copy(other);
    }
}

Reader::~Reader(){
    erase();
}

void Reader::addItemToList(Paper* newItem){
    BorrowedPaper newBorrowedItem(newItem);

    this->borrowedItems[size] = newBorrowedItem;
    this->size++;
}

void Reader::writeInFile(std::ofstream& output) const{
    User::writeInFile(output);
    output << size << '\n';
    for(int i = 0; i < size; ++i){
        borrowedItems[i].writeInFile(output);
        
        if(i == size - 1)
            output << "]";
        else
            output << '\n';
    }
}

User* Reader::clone() const{
    return new Reader(*this);
}

void Reader::print() const{
    User::print();
    std::cout << "borrowed items: " << std::endl;
    for(int i = 0; i < size; ++i){
        borrowedItems[i].getPaperPtr()->print();
        std::cout << std::endl;
    }
}
