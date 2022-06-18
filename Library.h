#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

#include "Paper.h"
#include "Book.h"
#include "Series.h"


class Library{
private:
    Paper** catalog;

    unsigned size;
    unsigned capacity;

    void copy(const Library& other);
    void resize();
    void erase();

public:
    Library();
    Library(Paper** items, int count);
    Library(const Library& other);

    Library& operator=(const Library& other);

    ~Library();

    void addItemToCatalog(Paper* newItem);
    void removeItemFromCatalog(const String& title);

    void writeInFile(std::ofstream& output) const;
    void createFromFile();

    void print() const;
};

#endif