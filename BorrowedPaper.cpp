#include "BorrowedPaper.h"

void BorrowedPaper::copy(const BorrowedPaper& other){
    this->paper = other.paper->clone();
    this->checkoutDate = other.checkoutDate;
    this->returnDate = other.returnDate;
}

BorrowedPaper::BorrowedPaper() : paper(nullptr){}

BorrowedPaper::BorrowedPaper(Paper* paper, const Date& checkoutDate, const Date& returnDate){
    this->paper = paper->clone();
    this->checkoutDate = checkoutDate;
    this->returnDate = returnDate;
}

BorrowedPaper::BorrowedPaper(Paper* paper){
    this->paper = paper->clone();

    this->checkoutDate = Date::getNow();
    this->returnDate = checkoutDate;
    this->returnDate.addMonth();
}

BorrowedPaper::BorrowedPaper(const BorrowedPaper& other){
    copy(other);
}


BorrowedPaper& BorrowedPaper::operator=(const BorrowedPaper& other){
    if(this != &other){
        delete this->paper;
        copy(other);
    }
}

BorrowedPaper::~BorrowedPaper(){
    delete this->paper;
}

void BorrowedPaper::setPaperPtr(Paper* paper){
    if(paper == nullptr){
        throw "Invalid value for paper in BorrowedPaper";
    }
    this->paper = paper->clone();
}

void BorrowedPaper::setCheckoutDate(const Date& checkoutDate){
    this->checkoutDate = checkoutDate;
}

void BorrowedPaper::setReturnDate(const Date& returnDate){
    this->returnDate = returnDate;
}

Paper* BorrowedPaper::getItemPtr() const{
    return this->paper;
}

const Date& BorrowedPaper::getCheckoutDate() const{
    return this->checkoutDate;
}

const Date& BorrowedPaper::getReturnDate() const{
    return this->returnDate;
}

void BorrowedPaper::writeInFile(std::ofstream& output) const{
    std::cout << paper->getType() << std::endl;
    if(this->paper->getType() == BOOK){
        dynamic_cast<Book*>(paper)->writeInFile(output);
    }
    if(this->paper->getType() == SERIES){
        dynamic_cast<Series*>(paper)->writeInFile(output);
    }
    output << checkoutDate << "|" << returnDate;
}

void BorrowedPaper::readFromFile(std::ifstream& input){
    char buffer[120];
    input.get(buffer, 2);

    Paper* newItem;
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
        setPaperPtr(newItem);
        setCheckoutDate(checkoutDate);
        setReturnDate(returnDate);
    }catch(const char* msg){
        std::cout << msg << std::endl;
        return;
    }
}

void BorrowedPaper::print() const{
    this->paper->print();
    std::cout << "|" << this->checkoutDate << "|" << this->returnDate << std::endl;
}

// BorrowedPaper::BorrowedPaper(const String& title, const String& publisher, const String& genre, const String& description, 
//     float rating, const Type& type, const Date& checkoutDate, const Date& returnDate) : Paper(title, publisher, genre, description, rating, type){
//         try{
//             this->checkoutDate = checkoutDate;
//             this->returnDate = returnDate;    
//         }catch(const char* msg){
//             std::cout << msg << std::endl;
//             throw;
//         }  
// }