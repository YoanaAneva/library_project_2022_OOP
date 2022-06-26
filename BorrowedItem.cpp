#include "BorrowedItem.h"

void BorrowedItem::copy(const BorrowedItem& other){
    this->item = other.item->clone();
    this->checkoutDate = other.checkoutDate;
    this->returnDate = other.returnDate;
}

BorrowedItem::BorrowedItem() : item(nullptr){}

BorrowedItem::BorrowedItem(Item* item, const Date& checkoutDate, const Date& returnDate){
    this->item = item->clone();
    // this->item = item;

    this->checkoutDate = checkoutDate;
    this->returnDate = returnDate;
}

BorrowedItem::BorrowedItem(Item* item){
    this->item = item->clone();
    // this->item = item;

    this->checkoutDate = Date::getNow();
    this->returnDate = checkoutDate;
    this->returnDate.addMonth();
}

BorrowedItem::BorrowedItem(const BorrowedItem& other){
    copy(other);
}


BorrowedItem& BorrowedItem::operator=(const BorrowedItem& other){
    if(this != &other){
        delete this->item;
        copy(other);
    }
    return *this;
}

BorrowedItem::~BorrowedItem(){
    delete this->item;
}

void BorrowedItem::setItemPtr(Item* item){
    if(item == nullptr){
        throw "Invalid value for item in BorrowedItem";
    }
    this->item = item->clone();
}

void BorrowedItem::setCheckoutDate(const Date& checkoutDate){
    this->checkoutDate = checkoutDate;
}

void BorrowedItem::setReturnDate(const Date& returnDate){
    this->returnDate = returnDate;
}

Item* BorrowedItem::getItemPtr() const{
    return this->item;
}

const Date& BorrowedItem::getCheckoutDate() const{
    return this->checkoutDate;
}

const Date& BorrowedItem::getReturnDate() const{
    return this->returnDate;
}

void BorrowedItem::writeInFile(std::ofstream& output) const{
    if(this->item->getType() == BOOK){
        dynamic_cast<Book*>(item)->writeInFile(output);
    }
    if(this->item->getType() == SERIES){
        dynamic_cast<Series*>(item)->writeInFile(output);
    }
    output << checkoutDate << "|" << returnDate;
}

void BorrowedItem::readFromFile(std::ifstream& input){
    char buffer[120];
    input.get(buffer, 2);

    Item* newItem;
    if(buffer[0] == 'B'){
        newItem = new Book();
        newItem->readFromFile(input);
    }
    if(buffer[0] == 'S'){
        newItem = new Series();
        newItem->readFromFile(input);
    }

    Date checkoutDate, returnDate;
    input >> checkoutDate;
    input.get(buffer, 2);
    input >> returnDate;

    try{
        setItemPtr(newItem);
        setCheckoutDate(checkoutDate);
        setReturnDate(returnDate);
    }catch(const char* msg){
        std::cout << msg << std::endl;
    }
}

void BorrowedItem::print() const{
    this->item->print();
    std::cout << "|" << this->checkoutDate << "|" << this->returnDate << "|" << std::endl;
}
