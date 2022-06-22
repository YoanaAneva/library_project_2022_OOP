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

    this->type = READER;
    this->borrowedItems = new BorrowedPaper[capacity];
}

Reader::Reader(const String& username, const String& password, const Date& regDate, const Date& lastVisit)
 : User(username, password, regDate, lastVisit, READER){
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

const BorrowedPaper& Reader::getBItem(unsigned ind) const{
    if(ind >= this->size){
        std::cout << "Index out of range, first element will be returned" << std::endl;
        return borrowedItems[0];
    }
    return borrowedItems[ind];
}

unsigned Reader::getBItemsCount() const{ return this->size; }

void Reader::borrowItem(Paper* newItem){
    BorrowedPaper newBorrowedItem(newItem);
    
    this->borrowedItems[size] = newBorrowedItem;
    this->size++;
}

void Reader::addItemToList(const BorrowedPaper& newBorrowedItem){
    this->borrowedItems[size] = newBorrowedItem;
    this->size++;
}

void Reader::removeItemFromList(unsigned id){
    for(int i = 0; i < size; ++i){
        if(borrowedItems[i].getItemPtr()->getId() == id){
            for(int j = i; j < size; ++j){
                borrowedItems[j] = borrowedItems[j + 1];
            }
        }
        --size;
        return;
    }
    std::cout << "You have not borrowed an item with id:" << id << std::endl;
}

void Reader::writeInFile(std::ofstream& output) const{
    User::writeInFile(output);
    output << size << '\n';
    for(int i = 0; i < size; ++i){
        borrowedItems[i].writeInFile(output);

        if(i != size - 1)
            output << '\n';
    }
    output << "]\n\n";
}

void Reader::readFromFile(std::ifstream& input){
    User::readFromFile(input);

    unsigned bufferLen = 1024;
    char buffer[bufferLen];
    unsigned borrowedItemsCount;

    input >> borrowedItemsCount;

    input.getline(buffer, bufferLen);

    BorrowedPaper borrowedItems[borrowedItemsCount];
    for(int i = 0; i < borrowedItemsCount; ++i){
        borrowedItems[i].readFromFile(input);
        addItemToList(borrowedItems[i]);

        if(i == borrowedItemsCount - 1){
            input.get(buffer, 2);
        }
        else{
            input.getline(buffer, bufferLen);
        }
    }
    // input.getline(buffer, bufferLen);
    input.getline(buffer, bufferLen);
    input.getline(buffer, bufferLen);
}

User* Reader::clone() const{
    return new Reader(*this);
}

void Reader::print() const{
    User::print();
    std::cout << "borrowed items: " << std::endl;
    for(int i = 0; i < size; ++i){
        borrowedItems[i].print();
    }
}
