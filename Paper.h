#ifndef PAPER_H_INCLUDED
#define PAPER_H_INCLUDED

#include "Date.h"

enum Type{
    dummy,
    BOOK,
    SERIES
};

class Paper{
protected:
    String title;
    String publisher;
    String genre;
    String description;
    float rating;
    unsigned id;
    bool hasIsbn_issn;

    Type type;

private:
    void copy(const Paper& other);

protected:
    static unsigned uniqueNumLib;

    static unsigned nextId;
    static unsigned generateNextId();

public:
    Paper();
    Paper(const String& title, const String& publisher, const String& genre, const String& description, float rating, const Type& type);
    Paper(const Paper& other);
    // Paper(Paper* other);

    ~Paper() = default;

    Paper& operator=(const Paper& other);

    void setTitle(const String& title);
    void setPublisher(const String& publisher);
    void setGenre(const String& genre);
    void setDescription(const String& description);
    void setRating(float rating);
    void setId(int id);
    void setHasIsbn_issn(bool hasIsbn);

    static void setUniqueNumLib(int uniqueNum);

    const String& getTitle() const;
    const String& getPublisher() const;
    const String& getGenre() const;
    const String& getDescription() const;
    float getRating() const;
    unsigned getId() const;
    const Type& getType() const;
    bool showHasIsbn_issn() const;

    static unsigned getUniqueNumLib();

    virtual void writeInFile(std::ofstream& output) const = 0;
    virtual void readFromFile(std::ifstream& input) = 0;

    virtual void print() const;
    virtual Paper* clone() const = 0;
};

#endif
