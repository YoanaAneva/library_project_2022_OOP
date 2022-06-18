#ifndef BORROWED_PAPER_H_INCLUDED
#define BORROWED_PAPER_H_INCLUDED

#include "Paper.h"
#include "Book.h"
#include "Series.h"

class BorrowedPaper /*: virtual public Paper*/{
private:
    Paper* paper;
    Date checkoutDate;
    Date returnDate;

    void copy(const BorrowedPaper& other);

public:
    BorrowedPaper();
    // BorrowedPaper(const String& title, const String& publisher, const String& genre, const String& description, 
    // float rating, const Type& type, const Date& checkoutDate, const Date& returnDate);
    BorrowedPaper(Paper* paper, const Date& d1, const Date& d2);
    BorrowedPaper(Paper* paper);

    BorrowedPaper(const BorrowedPaper& other);

    ~BorrowedPaper();

    BorrowedPaper& operator=(const BorrowedPaper& other);

    Paper* getPaperPtr() const;

    void writeInFile(std::ofstream& output) const;

    // virtual BorrowedPaper* clone() const = 0;
    void print() const;
};


#endif