#include "Paper.h"

unsigned Paper::nextId = 0;
unsigned Paper::uniqueNumLib = 0;

//using this function in copy ctor and operator= in order to avoid the copying of the id by the default ones
void Paper::copy(const Paper& other){ 
    this->type = other.type;
    this->title = other.title;
    this->publisher = other.publisher;
    this->genre = other.genre;
    this->description = other.description;
    this->rating = other.rating;
    this->hasIsbn_issn = other.hasIsbn_issn;
}

unsigned Paper::generateNextId(){
    unsigned idStep = 1;
    nextId += idStep;
    return nextId;
}

Paper::Paper(){
    this->id = generateNextId();
    this->rating = 0.0;
}

Paper::Paper(const String& title, const String& publisher, const String& genre, const String& description, float rating, const Type& type){
    this->id = generateNextId();
    this->type = type;
    try{
        setTitle(title);
        setPublisher(publisher);
        setGenre(genre);
        setDescription(description);
        setRating(rating);
    }catch(const char* msg){
        std::cout << msg << std::endl;
        setTitle("Unknown");
        setPublisher("Unknown");
        setGenre("Unknown");
        setDescription("Unknown");
        setRating(0.0);
    }
}

Paper::Paper(const Paper& other){
    copy(other);
    this->id = other.id;
}

Paper& Paper::operator=(const Paper& other){
        copy(other);
        return *this;
}

void Paper::setTitle(const String& title){
    if(title.getSize() == 0 || title.getData() == nullptr){
        throw "Invalid value for title!";
    }
    this->title = title;
}

void Paper::setPublisher(const String& publisher){
    if(publisher.getSize() == 0 || publisher.getData() == nullptr){
        throw "Invalid value for publisher!";
    }
    this->publisher = publisher;
}

void Paper::setGenre(const String& genre){
    if(genre.getSize() == 0 || genre.getData() == nullptr){
        throw "Invalid value for genre!";
    }
    this->genre = genre;
}

void Paper::setDescription(const String& description){
    if(description.getSize() == 0 || description.getData() == nullptr){
        throw "Invalid value for description!";
    }
    this->description = description;
}
void Paper::setRating(float rating){
    if(rating < 0 || rating > 5){
        throw "Invalid value for rating!";
    }
    this->rating = rating;
}
void Paper::setId(int id){
    if(id < 0)
        throw "Invalid value for id";
    this->id = id;
}
void Paper::setHasIsbn_issn(bool hasIsbn_issn){
    this->hasIsbn_issn = hasIsbn_issn;
}

void Paper::setUniqueNumLib(int uniqueNumLib_){
    if(uniqueNumLib_ <= 99){
        std::cout << "Invalid value for the library's unique number! A default number is going to be set!" << std::endl;
        uniqueNumLib = 123;
    }
    uniqueNumLib = uniqueNumLib_;
}

const String& Paper::getTitle() const { return this->title; }
const String& Paper::getPublisher() const { return this->publisher; }
const String& Paper::getGenre() const { return this->genre; }
const String& Paper::getDescription() const { return this->description; }
float Paper::getRating() const { return this->rating; }
unsigned Paper::getId() const { return this->id; }
const Type& Paper::getType() const { return this->type; }
bool Paper::showHasIsbn_issn() const { return this->hasIsbn_issn; }

unsigned Paper::getUniqueNumLib(){ return uniqueNumLib; }

void Paper::print() const{
    std::cout << title << "|" << publisher << "|" << genre << "|" << description << "|" << rating << "|id:" << id << "|" << uniqueNumLib << "|";
}




