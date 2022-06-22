#ifndef READER_H_INCLUDED
#define READER_H_INCLUDED

#include "BorrowedPaper.h"
#include "User.h"

class Reader : public User{
private:
    BorrowedPaper* borrowedItems;
    unsigned size;
    unsigned capacity;

    void copy(const Reader& other);
    void resize();
    void erase();

public:
    Reader();
    Reader(const String& username, const String& password, const Date& regDate, const Date& lastVisit);
    Reader(const Reader& other);

    Reader& operator=(const Reader& other);

    ~Reader();

    void borrowItem(Paper* newItem);
    void addItemToList(const BorrowedPaper& newItem);

    void removeItemFromList(unsigned id);

    const BorrowedPaper& getBItem(unsigned ind) const; 
    unsigned getBItemsCount() const;

    virtual void writeInFile(std::ofstream& output) const override;
    virtual void readFromFile(std::ifstream& input) override;

    virtual User* clone() const override;
    virtual void print() const override;
};

#endif