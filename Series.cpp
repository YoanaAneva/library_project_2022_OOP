#include "Series.h"

void Series::copy(const Series& other){
    this->datePublishing = other.datePublishing;
    this->issue = other.issue;

    this->hasIsbn_issn = other.hasIsbn_issn;
    this->issn = other.issn;

    this->articlesCount = other.articlesCount;
    this->content = new Article[articlesCount];

    for(int i = 0; i < articlesCount; i++){
        this->content[i] = other.content[i];
    }
}

void Series::erase(){
    delete[] this->content;
}

Series::Series() : Item(){
    this->type = SERIES;
    this->issue = 1;
    this->issn = "0000-0000";
    this->articlesCount = 0;
    this->content = new Article[0];
}

Series::Series(const String& title, const String& publisher, const String& genre, const String& description, float rating, const String& datePublishing, int issue, Article* content, int articlesCount, const String& issn) : 
Item(title, publisher, genre, description, rating, SERIES){
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
Item(title, publisher, genre, description, rating, SERIES){
    this->hasIsbn_issn = false;
    setIssn("0000-0000");

    try{
        setDatePublishing(datePublishing);
        setIssue(issue);
        setContent(content, articlesCount);
    }
    catch(const std::invalid_argument& msg){
        std::cout << msg.what() << "An object with default values is going to be created!" << std::endl;
        setIssue(1);
        this->articlesCount = 0;
        this->content = new Article[articlesCount];
    }
}

Series::Series(const Series& other) : Item(other){
    this->copy(other);
}

Series& Series::operator=(const Series& other){
    if(this != &other){
        Item::operator=(other);
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

void Series::setIssn(const String& issn){
    if(!isValidIssn(issn)){
        throw "Invalid value for ISSN!";
    }
    this->issn = issn;
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
const String& Series::getIssn() const{ return this->issn; }
const Article* Series::getContent() const{ return this->content; }
unsigned Series::getArticlesCount() const{ return this->articlesCount; }

Item* Series::clone() const{
    return new Series(*this);
}

void Series::writeInFile(std::ofstream& output) const{
    output << "S[" << id << "|" << title << "|" << publisher << "|" << genre << "|" << description << "|" << datePublishing << "|" << issue << "|" << rating << "|" << isTaken << "|" << hasIsbn_issn << "|";
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

    String title, publisher, genre, description, datePublishing, issn;
    unsigned issue, id, isTaken, hasIsbn_issn, articlesCount;
    float rating;

    input >> id;
    input.get(buffer, 2);

    input.getline(buffer, bufferLen, '|');
    title = buffer;

    input.getline(buffer, bufferLen, '|');
    publisher = buffer;

    input.getline(buffer, bufferLen, '|');
    genre = buffer;

    input.getline(buffer, bufferLen, '|');
    description = buffer;
 
    input.getline(buffer, bufferLen, '|');
    datePublishing = buffer;

    input >> issue;
    input.get(buffer, 2);

    input >> rating;
    input.get(buffer, 2);
  
    input >> isTaken;
    input.get(buffer, 2);

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
        setIsTaken(isTaken);
        setHasIsbn_issn(hasIsbn_issn);
        setContent(articles, articlesCount);
    }catch(const char* msg){
        std::cout << msg << " Object with deffault values is going to be created" << std::endl;
        setTitle("Unknown");
        setPublisher("Unknown");
        setGenre("Unknown");
        setDescription("Unknown");
        setDatePublishing("Unknown");
        setIssue(1);
        setRating(1);
    }
}

void Series::readFromUser(){
    String yearOfPubl, monthOfPubl, issueStr, articlesCountStr, issn;
    int issue, articlesCount;
    
    Item::readFromUser();

    if(hasIsbn_issn){
        char issn[10];
        do{
            std::cout << "\nEnter ISSN number: ";
            std::cin >> issn;
        }while(!isValidIssn(issn));
        this->issn = issn;
    }

    do{
        std::cout << "\nEnter year of publishing: ";
        std::cin >> yearOfPubl;
    }while(!Date::isValidYear(yearOfPubl));

    do{
        std::cout << "\nEnter month of publishing: ";
        std::cin >> monthOfPubl;
    }while(!Date::isValidMonth(monthOfPubl));

    do{
        std::cout << "\nEnter issue: ";
        std::cin >> issueStr;
        issue = String::convertToNumber(issueStr);
    }while(issue == -1);
    
    do{
        std::cout << "\nEnter number of articles: ";
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

bool Series::isValidIssn(const String& issn){
    if(issn.getSize() != 9 || !isdigit(issn[0]) || !isdigit(issn[1]) || !isdigit(issn[2]) || !isdigit(issn[3]) || !isdigit(issn[5]) || !isdigit(issn[6]) || !isdigit(issn[7]) || !isdigit(issn[8]) || issn[4] != '-'){
        std::cout << "\nInvalid value for ISSN! should have form: 0000-0000 where 0 can be any number\n\n";
        return false;
    }
    return true;
}

void Series::print() const{
    Item::print();
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
        std::cout << "\nEnter article header: ";
        std::cin >> header;
    }while(header == "" || header == " ");

    do{
        std::cout << "\nEnter article author: ";
        std::cin >> author;
    }while(author == "" || author == " ");

    do{
        std::cout << "\nEnter article keywords: ";
        std::cin >> keywords;
    }while(keywords == "" || keywords == " ");

    this->header = header;
    this->author = author;
    this->keywords = keywords;
}
