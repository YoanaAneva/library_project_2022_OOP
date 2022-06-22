#include "Library.h"

void Library::copy(const Library& other){
    this->catalogCapacity = other.catalogCapacity;
    this->catalogSize = other.catalogSize;

    this->catalog = new Paper*[catalogCapacity];
    for(int i = 0; i < catalogSize; ++i){
        this->catalog[i] = other.catalog[i]->clone();
    }
    this->dividerInd = other.dividerInd;
}

void Library::resize(){
    this->catalogCapacity *= 2;
    
    Paper** bigger = new Paper*[catalogCapacity];
    for(int i = 0; i < catalogSize; ++i){
        bigger[i] = this->catalog[i]->clone();
    }

    erase();
    this->catalog = bigger;
}

void Library::erase(){
    for(int i = 0; i  < catalogSize; ++i){
        delete this->catalog[i];
    }
    delete[] catalog;
}

Library::Library(){
    this->catalogCapacity = 16;
    this->catalogSize = 1;

    this->catalog = new Paper*[catalogCapacity];
    Paper* divider = new Book("Divider1", " ", " ", "divides books from series", 0, "divider", 2000, " ");
    catalog[0] = divider;
    dividerInd = 0;
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

unsigned Library::getCatalogSize() const {
    return this->catalogSize;
}
unsigned Library::getDividerInd() const {
    return this->dividerInd;
}

Paper* Library::operator[](int index) const{
    if(index >= catalogSize){
        std::cout << "index out of bound" << std::endl;
        return this->catalog[dividerInd];
    }
    return this->catalog[index];
}

Paper*& Library::operator[](int index){
    if(index >= catalogSize){
        std::cout << "index out of bound" << std::endl;
        return this->catalog[dividerInd];
    }
    return this->catalog[index];
}

Paper* Library::getItemById(unsigned id) const{
    for(int i = 0; i < catalogSize; i++){
        if(catalog[i]->getId() == id){
            return catalog[i];
        }
    }
    return nullptr;
}

Paper** Library::getItems() const{
    return this->catalog;
}

void Library::addItemToCatalog(Paper* newItem){
    if(catalogSize + 1 >= catalogCapacity)
        resize();
    if(newItem->getType() == BOOK){
        for(int i = 0; i < catalogSize; ++i){
            if(catalog[i]->getTitle() == "Divider1"){
                for(int j = catalogSize; j > i; --j){
                    catalog[j] = catalog[j - 1]; 
                }
                catalog[i] = newItem->clone();
                ++dividerInd;
                ++catalogSize;
                return;
            }
            String surname1 = String::getSurname(dynamic_cast<Book*>(newItem)->getAuthor());
            String surname2 = String::getSurname(dynamic_cast<Book*>(catalog[i])->getAuthor());
            if(strcmp(surname1.getData(), surname2.getData()) < 0){
                for(int j = catalogSize; j > i; --j){
                    catalog[j] = catalog[j - 1]; 
                }
                catalog[i] = newItem->clone();
                ++dividerInd;
                ++catalogSize;
                return;
            }
        }
    }
    if(newItem->getType() == SERIES){
        if(catalogSize == dividerInd + 1){
            catalog[catalogSize] = newItem->clone();
            ++catalogSize;
            return;
        }

        for(int i = dividerInd + 1; i < catalogSize; ++i){
            if(strcmp(newItem->getTitle().getData(), catalog[i]->getTitle().getData()) < 0){
                for(int j = catalogSize; j > i; --j){
                    catalog[j] = catalog[j - 1];
                }
                catalog[i] = newItem->clone();
                ++catalogSize;
                return;
            }
        }
        catalog[catalogSize] = newItem->clone();
    }
    ++catalogSize;
}

void Library::removeItemFromCatalog(unsigned id){
    for(int i = 0; i < catalogSize; ++i){
        if(catalog[i]->getId() == id && i != dividerInd){
            for(int j = i; j < catalogSize; ++j){
                catalog[j] = catalog[j + 1];
            }
            --catalogSize;
            std::cout << "Item with id:" << id << " successfully removed from the catalog" << std::endl;
            return;
        }
    }
    std::cout << "No item from our catalog matches id:" << id << std::endl;
    return; 
}

void Library::writeInFile() const{
    std::ofstream output("library_catalog.txt");

    if(!output){
        std::cout << "Cannot open file library_catalog.txt for writing!" << std::endl;
        return;
    }

    for(int i = 0; i < catalogSize; ++i){
        if(catalog[i]->getTitle() == "Divider1")
            continue;

        catalog[i]->writeInFile(output);
        output << '\n';
    }

    output.close();
}

void Library::readFromFile(){
    std::ifstream input("library_catalog.txt");
    if(!input){
        std::cout << "Cannot open file library_catalog.txt for reading!" << std::endl;
        return;
    }

    unsigned bufferLen = 1024;
    char buffer[bufferLen];
    char type[2];
    while(input){
        input.get(type, 2);
        if(type[0] == 'B'){
            Book* newBook = new Book();
            newBook->readFromFile(input);
            addItemToCatalog(newBook);
            input.getline(buffer, bufferLen);
        }
        if(type[0] == 'S'){
            Series* newSeries = new Series();
            newSeries->readFromFile(input);
            addItemToCatalog(newSeries);
            input.getline(buffer, bufferLen);
        }
    }

    input.close();
}

void Library::print() const{
    for(int i = 0; i < catalogSize; ++i){
        std::cout << "position: " << i << std::endl;
        catalog[i]->print();
        std::cout << std::endl;
    }
}