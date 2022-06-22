#include "Series.h"

void Series::copy(const Series& other){
    this->datePublishing = other.datePublishing;
    this->issue = other.issue;

    this->hasIsbn_issn = other.hasIsbn_issn;
    strcpy(this->issn, other.issn);

    this->articlesCount = other.articlesCount;
    this->content = new Article[articlesCount];

    for(int i = 0; i < articlesCount; i++){
        this->content[i] = other.content[i];
    }
}

void Series::erase(){
    delete[] this->content;
}

Series::Series() : Paper(){
    this->type = SERIES;
    this->issue = 1;
    strcpy(this->issn, "0000-0000");
    this->articlesCount = 0;
    this->content = new Article[0];
}

Series::Series(const String& title, const String& publisher, const String& genre, const String& description, float rating, const String& datePublishing, int issue, Article* content, int articlesCount, const char* issn) : 
Paper(title, publisher, genre, description, rating, SERIES){
    this->hasIsbn_issn = true;
    try{
        setDatePublishing(datePublishing);
        setIssue(issue);
        setIssn(issn);
        setContent(content, articlesCount);
    }
    catch(const char* msg){
        std::cout << msg << "An object with default values is going to be created!" << std::endl;
        setIssue(1);
        this->articlesCount = 0;
        this->content = new Article[articlesCount];
        setIssn("0000-0000");
    }
}

Series::Series(const String& title, const String& publisher, const String& genre, const String& description, float rating, const String& datePublishing, int issue, Article* content, int articlesCount) : 
Paper(title, publisher, genre, description, rating, SERIES){
    this->hasIsbn_issn = false;
    setIssn("0000-0000");

    try{
        setDatePublishing(datePublishing);
        setIssue(issue);
        setContent(content, articlesCount);
    }
    catch(const std::invalid_argument& msg){
        std::cout << msg.what() << "An object with default value is going to be created!" << std::endl;
        setIssue(1);
        this->articlesCount = 0;
        this->content = new Article[articlesCount];
    }
}

Series::Series(const Series& other) : Paper(other){
    this->copy(other);
}

Series& Series::operator=(const Series& other){
    if(this != &other){
        Paper::operator=(other);
        this->erase();
        this->copy(other);
    }
    return *this;
}

Series::~Series(){
    this->erase();
}

void Series::setDatePublishing(const String& datePublishing){
    this->datePublishing = datePublishing;
}

void Series::setIssue(int issue){
    if(issue <= 0){
        throw "Invalid value for issue!";
    }
    this->issue = issue;
}

void Series::setIssn(const char* issn){
    if(!isValidIssn(issn)){
        throw "Invalid value for ISSN!";
    }
    strcpy(this->issn, issn);
}

void Series::setContent(const Article* articles, int articlesCount){
    if(articles == nullptr){
        throw "Invalid value for articles!";
    }
    this->content = new Article[articlesCount];
    for(int i = 0; i < articlesCount; i++){
        this->content[i] = articles[i];
    }
    this->articlesCount = articlesCount;
}

const String& Series::getDatePublishing() const{ return this->datePublishing; }
unsigned Series::getIssue() const{ return this->issue; }
const char* Series::getIssn() const{ return this->issn; }
const Article* Series::getContent() const{ return this->content; }
unsigned Series::getArticlesCount() const{ return this->articlesCount; }

Paper* Series::clone() const{
    return new Series(*this);
}

void Series::writeInFile(std::ofstream& output) const{
    output << "S[" << id << "|" << title << "|" << publisher << "|" << genre << "|" << description << "|" << datePublishing << "|" << issue << "|" << rating << "|" << hasIsbn_issn << "|";
    if(hasIsbn_issn){
        output << issn << "|";
    }
    output << articlesCount << "\n"; 

    for(int i = 0; i < articlesCount; ++i){
        output << "{" << content[i] << "}";

        if(i == articlesCount - 1)
            output << "]";
        else
            output << "\n";
    }
}

void Series::readFromFile(std::ifstream& input){
    const unsigned bufferLen = 1024;
    char buffer[bufferLen];

    input.get(buffer, 2);

    String title, publisher, genre, description, datePublishing;
    unsigned issue, id, hasIsbn_issn, articlesCount;
    float rating;

    input >> id;
    input.get(buffer, 2);
    // std::cout << id << "|";

    input.getline(buffer, bufferLen, '|');
    title = buffer;
    // std::cout << title << "|";

    input.getline(buffer, bufferLen, '|');
    publisher = buffer;
    // std::cout << publisher << "|";


    input.getline(buffer, bufferLen, '|');
    genre = buffer;
    // std::cout << genre << "|";


    input.getline(buffer, bufferLen, '|');
    description = buffer;
    // std::cout << description << "|";
 
    input.getline(buffer, bufferLen, '|');
    datePublishing = buffer;
    // std::cout << datePublishing << "|";

    input >> issue;
    input.get(buffer, 2);
    // std::cout << issue << "|";

    input >> rating;
    input.get(buffer, 2);
    // std::cout << rating << "|";

    input >> hasIsbn_issn;
    input.get(buffer, 2);
    // std::cout << hasIsbn_issn << "|";

    if(hasIsbn_issn){
        char issn[10];
        input.getline(issn, 10, '|');
        try{
            setIssn(issn);
        }
        catch(const char* msg){
            std::cout << msg << std::endl;
        }
    }

    input >> articlesCount;
    // std::cout << articlesCount << std::endl;
    input.getline(buffer, bufferLen);

    Article articles[articlesCount];
    for(int i = 0; i < articlesCount; ++i){
        input.get(buffer, 2);
        input >> articles[i];
        if(i == articlesCount - 1){
            input.get(buffer, 2);
        }
        else{
            input.getline(buffer, bufferLen);
        }
    }

    try{
        setId(id);
        setTitle(title);
        setPublisher(publisher);
        setGenre(genre);
        setDescription(description);
        setDatePublishing(datePublishing);
        setIssue(issue);
        setRating(rating);
        setHasIsbn_issn(hasIsbn_issn);
        setContent(articles, articlesCount);
    }catch(const char* msg){
        std::cout << msg << std::endl;
    }
}

void Series::readFromUser(){
    String yearOfPubl, monthOfPubl, issueStr, articlesCountStr;
    int issue, articlesCount;
    
    Paper::readFromUser();

    if(hasIsbn_issn){
        char issn[10];
        do{
            std::cout << "Enter ISSN number: ";
            std::cin.getline(issn, 10);
        }while(!isValidIssn(issn));
        strcpy(this->issn, issn);
    }

    do{
        std::cout << "Enter year of publishing: ";
        std::cin >> yearOfPubl;
    }while(!Date::isValidYear(yearOfPubl));

    do{
        std::cout << "Enter month of publishing: ";
        std::cin >> monthOfPubl;
    }while(!Date::isValidMonth(monthOfPubl));

    do{
        std::cout << "Enter issue: ";
        std::cin >> issueStr;
        issue = String::convertToNumber(issueStr);
    }while(issue == -1);
    
    do{
        std::cout << "Enter number of articles: ";
        std::cin >> articlesCountStr;
        articlesCount = String::convertToNumber(articlesCountStr);
    }while(articlesCount == -1);

    Article articles[articlesCount];
    for(int i = 0; i < articlesCount; ++i){
        articles[i].readFromUser();
    }

    String datePubl;
    datePubl += yearOfPubl; datePubl += '-';
    if(monthOfPubl.getSize() == 1){
        datePubl += '0';
    }
    datePubl += monthOfPubl;

    this->datePublishing = datePubl;
    this->issue = issue;
    setContent(articles, articlesCount);
}

// void Periodic::writeInBin(std::ofstream& output){
//     title.writeInBin(output);
//     publisher.writeInBin(output);
//     genre.writeInBin(output);
//     description.writeInBin(output);
//     datePublishing.writeInBin(output);
//     output.write(reinterpret_cast<const char*>(&issue), sizeof(issue));
//     output.write(reinterpret_cast<const char*>(&rating), sizeof(rating));
//     output.write(reinterpret_cast<const char*>(&uniqueNumLib), sizeof(uniqueNumLib));
//     output.write(issn, 10);
//     output.write(reinterpret_cast<const char*>(&articlesCount), sizeof(articlesCount));
//     for(int i = 0; i < articlesCount; i++){
//         content[i].writeInBin(output);
//     }
// }

// void Periodic::readFromBin(std::ifstream& input, Periodic& periodic){
//     String title, publisher, genre, description, datePublishing;
//     int issue, uniqueNumLib_, articlesCount;
//     float rating = 0;
//     char issn[10];

//     String::readFromBin(input, title);
//     String::readFromBin(input, publisher);
//     String::readFromBin(input, genre);
//     String::readFromBin(input, description);
//     String::readFromBin(input, datePublishing);
//     input.read(reinterpret_cast<char*>(&issue), sizeof(issue));
//     input.read(reinterpret_cast<char*>(&rating), sizeof(rating));
//     input.read(reinterpret_cast<char*>(&uniqueNumLib_), sizeof(uniqueNumLib_));
//     input.read(issn, 10);
//     input.read(reinterpret_cast<char*>(&articlesCount), sizeof(articlesCount));

//     Article* as = new Article[articlesCount];

//     for(int i = 0; i < articlesCount; i++){
//         as[i].readFromBin(input);
//     }

//     periodic.setTitle(title);
//     periodic.setPublisher(publisher);
//     periodic.setGenre(genre);
//     periodic.setDescription(description);
//     periodic.setDatePublishing(datePublishing);
//     periodic.setIssue(issue);
//     periodic.setRating(rating);
//     Periodic::setUniqueNumLib(uniqueNumLib_);
//     periodic.setIssn(issn);
//     periodic.setContent(as, articlesCount);
//     delete[] as;
// }

bool Series::isValidIssn(const char* issn){
    if(strlen(issn) != 9 || !isdigit(issn[0]) || !isdigit(issn[1]) || !isdigit(issn[2]) || !isdigit(issn[3]) || !isdigit(issn[5]) || !isdigit(issn[6]) || !isdigit(issn[7]) || !isdigit(issn[8]) || issn[4] != '-'){
        std::cout << "Invalid value for ISSN!" << std::endl;
        return false;
    }
    return true;
}

void Series::print() const{
    Paper::print();
    std::cout << datePublishing << '|' << issue << '|' << (hasIsbn_issn ? issn : "") << std::endl << "Content:" << std::endl;
    for(int i = 0; i < articlesCount; i++){
        content[i].print();
    }
}

Article::Article(const String& header, const String& author, const String& keywords){
    this->header = header;
    this->header = header;
    this->author = author;
    this->keywords = keywords;
}

const String& Article::getAuthor() const{
    return this->author;
}

const String& Article::getKeywords() const{
    return this->keywords;
}

// void Article::writeInBin(std::ofstream& output){
//         header.writeInBin(output);
//         author.writeInBin(output);
//         keywords.writeInBin(output);
//     }

// void Article::readFromBin(std::ifstream& input){
//         String::readFromBin(input, this->header);
//         String::readFromBin(input, this->author);
//         String::readFromBin(input, this->keywords);
//     }

void Article::print() const{
        std::cout << "{" << header << '|' << author << '|' << keywords << "}" << std::endl;
    }

std::ostream& operator<<(std::ostream& output, const Article& article){
    output << article.header << "/" << article.author << "/" << article.keywords;
}

std::istream& operator>>(std::istream& input, Article& article){
    const unsigned bufferLen = 1024;
    char buffer[bufferLen];

    input.getline(buffer, bufferLen, '/');
    article.header = buffer;

    input.getline(buffer, bufferLen, '/');
    article.author = buffer;

    input.getline(buffer, bufferLen, '}');
    article.keywords = buffer;

    return input;
}

void Article::readFromUser(){
    String header, author, keywords;

    do{
        std::cout << "Enter article header: ";
        std::cin >> header;
    }while(header == "" || header == " ");

    do{
        std::cout << "Enter article author: ";
        std::cin >> author;
    }while(author == "" || author == " ");

    do{
        std::cout << "Enter article keywords: ";
        std::cin >> keywords;
    }while(keywords == "" || keywords == " ");

    this->header = header;
    this->author = author;
    this->keywords = keywords;
}

// BorrowedSeries::BorrowedSeries(const String& title, const String& publisher, const String& genre, const String& description, float rating, 
//     const String& datePublishing, int issue, Article* content, int articlesCount, const char* issn, const Date& checkoutDate, const Date& returnDate) : 
//     Paper(title, publisher, genre, description, rating, SERIES),
//     Series(title, publisher, genre, description, rating, datePublishing, issue, content, articlesCount, issn),
//     BorrowedPaper(title, publisher, genre, description, rating, SERIES, checkoutDate, returnDate) {}


// BorrowedSeries::BorrowedSeries(const String& title, const String& publisher, const String& genre, const String& description, float rating, 
//     const String& datePublishing, int issue, Article* content, int articlesCount, const Date& checkoutDate, const Date& returnDate) : 
//     Paper(title, publisher, genre, description, rating, SERIES),
//     Series(title, publisher, genre, description, rating, datePublishing, issue, content, articlesCount),
//     BorrowedPaper(title, publisher, genre, description, rating, SERIES, checkoutDate, returnDate) {}


// BorrowedPaper* BorrowedSeries::clone() const{
//     return new BorrowedSeries(*this);
// }

// void BorrowedSeries::print() const{
//     Series::print();
//     std::cout << checkoutDate << "|" << returnDate << std::endl;
// }