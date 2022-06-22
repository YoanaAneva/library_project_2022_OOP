#ifndef BORROWED_PAPER_H_INCLUDED
#define BORROWED_PAPER_H_INCLUDED

#include "Paper.h"
#include "Book.h"
#include "Series.h"

class BorrowedPaper{
private:
    Paper* paper;
    Date checkoutDate;
    Date returnDate;

    void copy(const BorrowedPaper& other);

public:
    BorrowedPaper();

    BorrowedPaper(Paper* paper, const Date& d1, const Date& d2);
    BorrowedPaper(Paper* paper);

    BorrowedPaper(const BorrowedPaper& other);

    BorrowedPaper& operator=(const BorrowedPaper& other);

    ~BorrowedPaper();

    void setPaperPtr(Paper* paper);
    void setCheckoutDate(const Date& checkoutDate);
    void setReturnDate(const Date& returnDate);

    Paper* getItemPtr() const;
    const Date& getCheckoutDate() const;
    const Date& getReturnDate() const;

    void writeInFile(std::ofstream& output) const;
    void readFromFile(std::ifstream& input);

    // virtual BorrowedPaper* clone() const = 0;
    void print() const;
};


#endif