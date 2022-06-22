#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

#include "Paper.h"
#include "Book.h"
#include "Series.h"


class Library{
private:
    Paper** catalog;

    unsigned catalogSize;
    unsigned catalogCapacity;

    unsigned dividerInd;

public:
    void copy(const Library& other);
    void resize();
    void erase();

public:
    Library();
    Library(Paper** items, int count);
    Library(const Library& other);

    Library& operator=(const Library& other);

    ~Library();

    Paper* operator[](int index) const;
    Paper*& operator[](int index);

    Paper* getItemById(unsigned id) const;
    Paper** getItems() const;

    unsigned getCatalogSize() const;
    unsigned getDividerInd() const;

    void addItemToCatalog(Paper* newItem);
    void removeItemFromCatalog(unsigned id);

    void writeInFile() const;
    void readFromFile();

    void print() const;
};

#endif