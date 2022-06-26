#include "Book.h"

Book::Book() : Item(){
    this->type = BOOK;
    this->isbn = "978-0-0000-0000-0";
}

Book::Book(const String& title, const String& publisher, const String& genre, const String& description, float rating, const String& author, int yearOfPublishing, const String& keywords, const String& isbn) : 
Item(title, publisher, genre, description, rating, BOOK){
    this->hasIsbn_issn = true;
    try{
        setAuthor(author);
        setYearOfPublishing(yearOfPublishing);
        setKeywords(keywords);
        setIsbn(isbn);
    }
    catch(const char* msg){
        std::cout << msg <<  "Object with default values is going to be created!" <<std::endl;
        setAuthor("Unknown");
        setYearOfPublishing(1);
        setKeywords("Unknown");
        setIsbn("978-0-0000-0000-0");
    }
}

Book::Book(const String& title, const String& publisher, const String& genre, const String& description, float rating, const String& author, int yearOfPublishing, const String& keywords) : 
Item(title, publisher, genre, description, rating, BOOK){
    this->hasIsbn_issn = false;
    try{
        setAuthor(author);
        setYearOfPublishing(yearOfPublishing);
        setKeywords(keywords);
    }
    catch(const char* msg){
        std::cout << msg << " Object with default values is going to be created!" << std::endl;
        setAuthor("Unknown");
        setYearOfPublishing(1);
        setKeywords("Unknown");
    }
}

void Book::setAuthor(const String& author){
    if(author.getData() == nullptr || author.getSize() == 0){
        throw "Invalid value for author!";
    }
    this->author = author;
}

void Book::setYearOfPublishing(int yearOfPublishing){
    if(yearOfPublishing <= 1000 || yearOfPublishing > Date::getThisYear()){
        throw "Invalid value for year of publishing!";
    }
    this->yearOfPublishing = yearOfPublishing;
}

void Book::setKeywords(const String& keywords){
    if(keywords.getData() == nullptr || keywords.getSize() <= 0){
        throw "Invalid value for keywords!";
    }
    this->keywords = keywords;
}

void Book::setIsbn(const String& isbn){
    if(!isValidIsbn(isbn)){
        throw "Invalid value for isbn!";
    }
    this->isbn = isbn;
}


const String& Book::getAuthor() const { return this->author; }
int Book::getYearOfPublishing() const { return this->yearOfPublishing; }
const String& Book::getKeywords() const { return this->keywords; }
const String& Book::getIsbn() const { return this->isbn; }

void Book::writeInFile(std::ofstream& output) const{
    output << "B[" << id << "|" << title << "|" << author << "|" << publisher << "|" << genre << "|" << description << "|" 
    << yearOfPublishing << "|" << keywords << "|" << rating << "|" << isTaken << "|" << hasIsbn_issn;
    if(hasIsbn_issn){
        output << "|" << isbn << "]";
    }
    else{
        output << "]";
    }
}

void Book::readFromFile(std::ifstream& input){
    const unsigned bufferLen = 1024;
    char buffer[bufferLen];

    input.get(buffer, 2);

    String title, author, publisher, genre, description, keywords;
    unsigned id, yearOfPublishing, isTaken, hasIsbn_issn;
    float rating;

    input >> id;

    input.get(buffer, 2);
    input.getline(buffer, bufferLen, '|');
    title = buffer;

    input.getline(buffer, bufferLen, '|');
    author = buffer;

    input.getline(buffer, bufferLen, '|');
    publisher = buffer;

    input.getline(buffer, bufferLen, '|');
    genre = buffer;

    input.getline(buffer, bufferLen, '|');
    description = buffer;

    input >> yearOfPublishing;
    input.get(buffer, 2);
    
    input.getline(buffer, bufferLen, '|');
    keywords = buffer;

    input >> rating;
    setRating(rating);

    input.get(buffer, 2);

    input >> isTaken;
    input.get(buffer, 2);

    input >> hasIsbn_issn;
    
    if(hasIsbn_issn){
        input.get(buffer, 2);
        input.getline(buffer, bufferLen, ']');
        char isbn[18];
        strcpy(isbn, buffer);
        try{
            setIsbn(isbn);
        }catch(const char* msg){
            std::cout << msg << std::endl;
        }
    }
    else{
        input.get(buffer, 2);
    }

    try{
        setId(id);
        setTitle(title);
        setAuthor(author);
        setPublisher(publisher);
        setGenre(genre);
        setDescription(description);
        setYearOfPublishing(yearOfPublishing);
        setKeywords(keywords);
        setIsTaken(isTaken);
        setHasIsbn_issn(hasIsbn_issn);
    }
    catch(const char* msg){
        std::cout << msg << "Default values are going to be set\n\n";
        setTitle("Unknown");
        setAuthor("Unknown");
        setPublisher("Unknown");
        setGenre("Unknown");
        setDescription("Unknown");
        setYearOfPublishing(1000);
        setKeywords("Unknown");
    }
}

void Book::readFromUser(){
    String author, yearOfPublishingStr, keywords;
    do{
        std::cout << "\nEnter author: ";
        std::cin >> author;
    }while(author == "" || author == " ");

    Item::readFromUser();

    if(this->hasIsbn_issn){
        do{
            std::cout << "\nEnter ISBN number: ";
            std::cin >> isbn;
        }while(!isValidIsbn(isbn));
        this->isbn = isbn;
    }

    do{
        std::cout << "\nEnter year of publishing: ";
        std::cin >> yearOfPublishingStr;
    }while(!(Date::isValidYear(yearOfPublishingStr)));

    do{
        std::cout << "\nEnter keywords: ";
        std::cin >> keywords;
    }while(keywords == " " || keywords == "");

    int yearOfPubl = String::convertToNumber(yearOfPublishingStr);

    this->author = author;
    this->yearOfPublishing = yearOfPubl;
    this->keywords = keywords;
}

void Book::print() const{
    Item::print();
    if(hasIsbn_issn)
        std::cout << author << "|" <<  yearOfPublishing << "|" << keywords << "|" << isbn << std::endl;
    else
        std::cout << author << "|" <<  yearOfPublishing << "|" << keywords << std::endl;
}

Item* Book::clone() const{
    return new Book(*this);
}

bool Book::isValidIsbn(const String& isbn){
    if(isbn.getData() == nullptr || isbn.getSize() != 17 || isbn[0] != '9' || isbn[1] != '7' || (isbn[2] != '8' && isbn[2] != '9') || isbn[3] != '-' || isbn[15] != '-'){
        std::cout << "\nInvalid ISBN number: correct form: 978-0-0000-0000-0 where 0 can be any number\n\n";
        return false;
    }
    return true;
}
