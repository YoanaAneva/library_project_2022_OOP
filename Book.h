#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED

#include "Paper.h"

class Book : virtual public Paper{
protected:
    String author;
    int yearOfPublishing;
    String keywords;
    char isbn[18];

private:
    void copy(const Book& other);

public:
    Book();
    Book(const String& title, const String& publisher, const String& genre, const String& description, float rating, const String& author, int yearOfPublishing, const String& keywords, const char* isbn);
    Book(const String& title, const String& publisher, const String& genre, const String& description, float rating, const String& author, int yearOfPublishing, const String& keywords);

    Book(const Book& other) = default;

    Book& operator=(const Book& other) = default;

    virtual ~Book() = default;

    void setAuthor(const String& author);
    void setYearOfPublishing(int yearOfPublishing);
    void setKeywords(const String& keywords);
    void setIsbn(const char* isbn);

    const String& getAuthor() const;
    int getYearOfPublishing() const;
    const String& getKeywords() const;
    const char* getIsbn() const;

    // void writeBookInBin(std::ofstream& outf);
    // static void readBookFromBin(std::ifstream& inf, Book& book);

    virtual void writeInFile(std::ofstream& output) const override;
    virtual void readFromFile(std::ifstream& input) override;

    virtual void print() const override;
    virtual Paper* clone() const override;
};


// class BorrowedBook : public Book, public BorrowedPaper{
// public:
//     BorrowedBook() = default;

//     BorrowedBook(const String& title, const String& publisher, const String& genre, const String& description, float rating, 
//     const String& author, int yearOfPublishing, const String& keywords, const char* isbn, const Date& checkoutDate, const Date& returnDate);
//     BorrowedBook(const String& title, const String& publisher, const String& genre, const String& description, float rating, 
//     const String& author, int yearOfPublishing, const String& keywords, const Date& checkoutDate, const Date& returnDate);

//     BorrowedBook(const Book& book);

//     ~BorrowedBook() = default;

//     // virtual BorrowedPaper* clone() const override;

//     virtual void print() const override;
// };

#endif
