#ifndef SERIES_H_INCLUDED
#define SERIES_H_INCLUDED

#include "Paper.h"

struct Article{
private:
    String header;
    String author;
    String keywords;
public:
    Article() = default;
    Article(const String& header, const String& author, const String& keywords);
    Article& operator=(const Article& other) = default;

    // void writeInBin(std::ofstream& output);
    // void readFromBin(std::ifstream& input);

    const String& getAuthor() const;
    const String& getKeywords() const;

    friend std::ostream& operator<<(std::ostream& output, const Article& article);
    friend std::istream& operator>>(std::istream& input, Article& article);

    void readFromUser();

    void print() const;
};

class Series : virtual public Paper{
private:
    String datePublishing;
    unsigned issue;
    char issn[10];
    Article* content;
    unsigned articlesCount;

    void copy(const Series& other);
    void erase();
public:
    Series();
    Series(const String& title, const String& publisher, const String& genre, const String& description, float rating, const String& datePublishing, int issue, Article* content, int articlesCount, const char* issn);
    Series(const String& title, const String& publisher, const String& genre, const String& description, float rating, const String& datePublishing, int issue, Article* content, int articlesCount);
    Series(const Series& other);

    Series& operator=(const Series& other);

    virtual ~Series();

    void setDatePublishing(const String& datePublishing);
    void setIssue(int issue);
    void setIssn(const char* issn);
    void setContent(const Article* articles, int articlesCount);

    const String& getDatePublishing() const;
    unsigned getIssue() const;
    const char* getIssn() const;
    const Article* getContent() const;
    unsigned getArticlesCount() const;

    void writeInBin(std::ofstream& output);
    static void readFromBin(std::ifstream& input, Series& Series);

    virtual void writeInFile(std::ofstream& output) const override;
    virtual void readFromFile(std::ifstream& input) override;
    virtual void readFromUser() override;

    virtual Paper* clone() const override;
    virtual void print() const override;

    static bool isValidIssn(const char* issn);
};


// class BorrowedSeries : public Series, public BorrowedPaper{
// public:
//     BorrowedSeries() = default;

//     BorrowedSeries(const String& title, const String& publisher, const String& genre, const String& description, float rating, 
//     const String& datePublishing, int issue, Article* content, int articlesCount, const Date& checkoutDate, const Date& returnDate);
   
//     BorrowedSeries(const String& title, const String& publisher, const String& genre, const String& description, float rating, 
//     const String& datePublishing, int issue, Article* content, int articlesCount, const char* issn, const Date& checkoutDate, const Date& returnDate);

//     BorrowedSeries(const Series& series);

//     ~BorrowedSeries() = default;

//     // virtual BorrowedPaper* clone() const override;

//     virtual void print() const override;
// };

#endif
