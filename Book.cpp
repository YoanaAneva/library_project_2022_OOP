#include "Book.h"

Book::Book() : Paper(){
    this->type = BOOK;
    this->yearOfPublishing = 1;
    strcpy(this->isbn, "978-0-0000-0000-0");
    this->hasIsbn_issn = false;
}

Book::Book(const String& title, const String& publisher, const String& genre, const String& description, float rating, const String& author, int yearOfPublishing, const String& keywords, const char* isbn) : 
Paper(title, publisher, genre, description, rating, BOOK){
    this->hasIsbn_issn = true;
    try{
        setAuthor(author);
        setYearOfPublishing(yearOfPublishing);
        setKeywords(keywords);
        setIsbn(isbn);
    }
    catch(const std::invalid_argument& msg){
        std::cout << msg.what() << " Object with default values is going to be created!" << std::endl;
        setAuthor("Unknown");
        setYearOfPublishing(1);
        setKeywords("Unknown");
        setIsbn("978-0-0000-0000-0");
    }
}

Book::Book(const String& title, const String& publisher, const String& genre, const String& description, float rating, const String& author, int yearOfPublishing, const String& keywords) : 
Paper(title, publisher, genre, description, rating, BOOK){
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
    if(yearOfPublishing <= 0){
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

void Book::setIsbn(const char* isbn){
    if(!isValidIsbn(isbn)){
        throw "Invalid value for isbn!";
    }
    strcpy(this->isbn, isbn);
}


const String& Book::getAuthor() const { return this->author; }
int Book::getYearOfPublishing() const { return this->yearOfPublishing; }
const String& Book::getKeywords() const { return this->keywords; }
const char* Book::getIsbn() const { return this->isbn; }


// void Book::writeBookInBin(std::ofstream& output){
//     this->author.writeInBin(output);
//     this->title.writeInBin(output);
//     this->publisher.writeInBin(output);
//     this->genre.writeInBin(output);
//     this->description.writeInBin(output);
//     output.write(reinterpret_cast<const char*> (&yearOfPublishing), sizeof(yearOfPublishing));
//     this->keywords.writeInBin(output);
//     output.write(reinterpret_cast<const char*> (&rating), sizeof(rating));
//     output.write(reinterpret_cast<const char*> (&uniqueNumLib), sizeof(uniqueNumLib));
//     output.write(isbn, 18);
// }

// void Book::readBookFromBin(std::ifstream& input, Book& book){
//     String::readFromBin(input, book.author);
//     String::readFromBin(input, book.title);
//     String::readFromBin(input, book.publisher);
//     String::readFromBin(input, book.genre);
//     String::readFromBin(input, book.description);
//     input.read(reinterpret_cast<char*> (&book.yearOfPublishing), sizeof(book.yearOfPublishing));
//     String::readFromBin(input, book.keywords);
//     input.read(reinterpret_cast<char*> (&book.rating), sizeof(book.rating));
//     input.read(reinterpret_cast<char*> (&uniqueNumLib), sizeof(uniqueNumLib));
//     input.read(book.isbn, 18);
// }

void Book::writeInFile(std::ofstream& output) const{
    output << "B[" << this->id << "|" << this->title << "|" << this->author << "|" << this->publisher << "|" << this->genre << "|" << this->description << "|" 
    << this->yearOfPublishing << "|" << this->keywords << "|" << this->rating << "|" << this->hasIsbn_issn;
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
    unsigned id, yearOfPublishing, hasIsbn_issn;
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
        setHasIsbn_issn(hasIsbn_issn);
    }
    catch(const char* msg){
        std::cout << msg << std::endl;
    }
}

void Book::readFromUser(){
    String author, yearOfPublishingStr, keywords;
    do{
        std::cout << "Enter author: ";
        std::cin >> author;
    }while(author == "" || author == " ");

    Paper::readFromUser();

    if(this->hasIsbn_issn){
        char isbn[18];
        do{
            std::cout << "Enter ISBN number: ";
            std::cin.getline(isbn, 18);
        }while(!isValidIsbn(isbn));
        strcpy(this->isbn, isbn);
    }

    do{
        std::cout << "Enter year of publishing: ";
        std::cin >> yearOfPublishingStr;
    }while(!(Date::isValidYear(yearOfPublishingStr)));

    do{
        std::cout << "Enter keywords: ";
        std::cin >> keywords;
    }while(keywords == " " || keywords == "");

    int yearOfPubl = String::convertToNumber(yearOfPublishingStr);

    this->author = author;
    this->yearOfPublishing = yearOfPubl;
    this->keywords = keywords;
}

void Book::print() const{
    Paper::print();
    if(hasIsbn_issn)
        std::cout << author << "|" <<  yearOfPublishing << "|" << keywords << "|" << isbn << std::endl;
    else
        std::cout << author << "|" <<  yearOfPublishing << "|" << keywords << std::endl;
}

Paper* Book::clone() const{
    return new Book(*this);
}

bool Book::isValidIsbn(const char* isbn){
    if(isbn == nullptr || strlen(isbn) != 17 || isbn[0] != '9' || isbn[1] != '7' || (isbn[2] != '8' && isbn[2] != '9') || isbn[3] != '-' || isbn[15] != '-'){
        std::cout << "Invalid ISBN number" << std::endl;
        return false;
    }
    return true;
}

// BorrowedBook::BorrowedBook(const String& title, const String& publisher, const String& genre, const String& description, float rating, 
//     const String& author, int yearOfPublishing, const String& keywords, const char* isbn, const Date& checkoutDate, const Date& returnDate) :
//     Paper(title, publisher, genre, description, rating, BOOK),
//     Book("will", "be", "ignored", "!", 0, author, yearOfPublishing, keywords, isbn),
//     BorrowedPaper(" ", " ", " ", " ", 0, BOOK, checkoutDate, returnDate) {}


// BorrowedBook::BorrowedBook(const String& title, const String& publisher, const String& genre, const String& description, float rating, 
//     const String& author, int yearOfPublishing, const String& keywords, const Date& checkoutDate, const Date& returnDate) :
//     Paper(title, publisher, genre, description, rating, BOOK),
//     Book("will", "be", "ignored", "!", 0, author, yearOfPublishing, keywords),
//     BorrowedPaper(title, publisher, genre, description, rating, BOOK, checkoutDate, returnDate) {}

// BorrowedBook::BorrowedBook(const Book& book) : Paper(book), Book(book){
//     // this->title = book.getTitle();
//     // this->publisher = book.getPublisher();
//     // this->genre = book.getGenre();
//     // this->description = book.getDescription();
//     // this->rating = book.getRating();
//     // this->author = book.getAuthor();
//     // this->yearOfPublishing = book.getYearOfPublishing();
//     // this->keywords = book.getKeywords();
   
//     // this->checkoutDate = Date::getNow();
//     // this->returnDate = checkoutDate.addMonth(); 
//     // this->id = book.getId();

//     // this->type = BOOK;   
//     // this->hasIsbn_issn = book.showHasIsbn_issn();
//     // char isbn[18];
//     // if(book.showHasIsbn_issn())
//     //     strcpy(this->isbn, book.getIsbn());
//     // else
//     //     strcpy(this->isbn, "000-0-0000-0000-0"

//     this->checkoutDate = Date::getNow();
//     this->returnDate = checkoutDate;
//     this->returnDate.addMonth(); 
//     this->id = book.getId();
// }

// BorrowedPaper* BorrowedBook::clone() const{
//     return new BorrowedBook(*this);
// }

// void BorrowedBook::print() const{
//     Book::print();
//     std::cout << checkoutDate << "|" << returnDate << std::endl;
// }