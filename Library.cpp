#include "Library.h"

void Library::copy(const Library& other){
    this->capacity = other.capacity;
    this->size = other.size;

    this->catalog = new Paper*[capacity];
    for(int i = 0; i < size; ++i){
        this->catalog[i] = other.catalog[i]->clone();
    }
}

void Library::resize(){
    this->capacity *= 2;
    
    Paper** bigger = new Paper*[capacity];
    for(int i = 0; i < size; ++i){
        bigger[i] = this->catalog[i]->clone();
    }

    erase();
    this->catalog = bigger;
}

void Library::erase(){
    for(int i = 0; i  < size; ++i){
        delete this->catalog[i];
    }
    delete[] catalog;
}

Library::Library(){
    this->capacity = 16;
    this->size = 1;

    this->catalog = new Paper*[capacity];
    Paper* divider = new Book("Divider1", " ", " ", "divides books from series", 0, "divider", 2000, " ");
    catalog[0] = divider;
}

Library::Library(const Library& other){
    copy(other);
}

Library& Library::operator=(const Library& other){
    if(this != &other){
        erase();
        copy(other);
    }
    return *this;
}

Library::~Library(){
    erase();
}

void Library::addItemToCatalog(Paper* newItem){
    if(size + 1 >= capacity)
        resize();
    
    if(newItem->getType() == BOOK){
        for(int i = 0; i < size; ++i){
            if(catalog[i]->getTitle() == "Divider1"){
                catalog[i + 1] = catalog[i];
                catalog[i] = newItem->clone();
                break;
            }
            if(strcmp(dynamic_cast<Book*>(newItem)->getAuthor().getData(), dynamic_cast<Book*>(catalog[i])->getAuthor().getData()) < 0){
                for(int j = size; j > i; --j){
                    catalog[j] = catalog[j - 1]->clone(); 
                }
                catalog[i] = newItem->clone();
                break;
            }
        }
    }
    if(newItem->getType() == SERIES){
        unsigned dividerInd;
        for(int i = 0; i < size; ++i){
            if(catalog[i]->getTitle() == "Divider1"){
                dividerInd = i;
                break;
            }
        }
        
        if(size == dividerInd + 1){
            catalog[size] = newItem->clone();
            ++size;
            return;
        }

        for(int i = dividerInd + 1; i < size; ++i){
            if(strcmp(newItem->getTitle().getData(), catalog[i]->getTitle().getData()) < 0){
                for(int j = size; j > i; --j){
                    catalog[j] = catalog[j - 1];
                }
                catalog[i] = newItem->clone();
                ++size;
                return;
            }
        }
        catalog[size] = newItem->clone();
    }
    ++size;
}

void Library::removeItemFromCatalog(const String& title){
    for(int i = 0; i < size; ++i){
        if(catalog[i]->getTitle() == title){
            for(int j = i; j < size; ++j){
                catalog[j] = catalog[j + 1];
            }
            --size;
            return;
        }
    }
    std::cout << "No title from our catalog matches: " << title << std::endl;
    return; 
}

void Library::writeInFile(std::ofstream& output) const{
    for(int i = 0; i < size; ++i){
        if(catalog[i]->getTitle() == "Divider1")
            continue;

        catalog[i]->writeInFile(output);
        output << '\n';
    }
}

void Library::createFromFile(){
    std::ifstream input("library_catalog.txt");
    if(!input){
        std::cout << "Cannot open file library_catalog.txt!" << std::endl;
        return;
    }

    char type[2];
    while(input){
        input.get(type, 2);
        if(type[0] == 'B'){
            Book* newBook = new Book();
            newBook->readFromFile(input);
            addItemToCatalog(newBook);
        }
        if(type[0] == 'S'){
            Series* newSeries = new Series();
            newSeries->readFromFile(input);
            addItemToCatalog(newSeries);
        }
    }

    input.close();
}

void Library::print() const{
    for(int i = 0; i < size; ++i){
        std::cout << "position: " << i << std::endl;
        catalog[i]->print();
        std::cout << std::endl;
    }
}