#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include "Date.h"

enum Type{
    dummy,
    BOOK,
    SERIES
};

///Клас представляващ общите данни за артикулите от библиотеката. Класът е абстрактен, от него не се създават обекти.
///Целта му е да бъде наследен от различти видове артикули, които да го допълнят и осмислят.
class Item{
protected:
    String title;
    String publisher;
    String genre;
    String description;
    float rating;
    unsigned id;
    bool hasIsbn_issn;

    Type type;

    bool isTaken;

private:
    void copy(const Item& other);

protected:
    static unsigned uniqueNumLib;

    static unsigned nextId;
    static unsigned generateNextId();

public:
    ///Генерира се нов уникален идентификатор.
    Item();
    ///конструктор с параметри - инициализира стойностите на променливите. Използва се статичната функция generateNextId(), която генерира уникален идентификационен номер на всеки артикул.
    ///Проверява за изключения, и при прихванато такова, задава подразбиращи се стойности на променливите.
    ///Вероятността за възникване на изключение, заради невалидни стойнтости, е минимална, понеже невалидни данни от потребителя не се подават, а файловете,
    ///от които идват данните са създадени от валидни обекти.
    Item(const String& title, const String& publisher, const String& genre, const String& description, float rating, const Type& type);
    
    Item(const Item& other);

    virtual ~Item() = default;

    ///Не се използва системно генерирания, за да се избегне присвояването на идентификационния номер.
    Item& operator=(const Item& other);

    void setTitle(const String& title);
    void setPublisher(const String& publisher);
    void setGenre(const String& genre);
    void setDescription(const String& description);
    void setRating(float rating);
    void setId(int id);
    void setHasIsbn_issn(bool hasIsbn_issn);
    void setIsTaken(bool isTaken);

    ///Статична функция, която задава уникалния номер на библиотеката, който е статична променлива, обща за всички обекти от типа Item.
    static void setUniqueNumLib(int uniqueNum);

    const String& getTitle() const;
    const String& getPublisher() const;
    const String& getGenre() const;
    const String& getDescription() const;
    float getRating() const;
    unsigned getId() const;
    const Type& getType() const;
    bool showHasIsbn_issn() const;
    bool getIsTaken() const;

    ///Статична функция, която връща уникалния номер на библиотеката, който е статична променлива, обща за всички обекти от типа Item.
    static unsigned getUniqueNumLib();

    ///Функция, която е чисто виртуална и няма имплементация, понеже наслидниците влагат своя различна логика в изреждането на данните си.
    ///Всички наследници са длъжни да я предефинират.
    virtual void writeInFile(std::ofstream& output) const = 0;
    
    ///Функция, която е чисто виртуална и няма имплементация, понеже наслидниците влагат своя различна логика в изреждането на данните си.
    ///Всички наследници са длъжни да я предефинират.
    virtual void readFromFile(std::ifstream& input) = 0;
   
    ///Виртуална функция със своя имплементация, която наследниците ще предефинират, но и освен това, могат да използват при четене на наследените данни от класа от потребителя.
    virtual void readFromUser();

    ///Функция, чиято цел е да улеснява извеждането на данните за функциите Commands::books_all(), Commands::series_all(), Commands::listAll(). 
    void listAll() const;

    virtual void print() const;

    ///Чисто виртуална функция, която всеки наследник трябва да предефинира. Повече за нея Book::clone(), Series::clone().
    virtual Item* clone() const = 0;

    ///Функция, която приема string и проверява дали е валидна стойност за жанр, т.е. не съдържа символи различни от буква, тире, разстояние.
    bool isValidGenre(const String& genre);
    
    ///Функция, която приема string и използва strtof(), която преобразува const char* към float, за да го валидира. Използва се при въвеждането 
    ///на рейтинг от потребителя, за да се обхванат случаите, в които потребителят би въвел символ различен от цифра или би натиснал "Enter".
    bool isValidRating(const String& rating);

    ///Функция, която приема два символни низа, разделя първия на отделни думи и проверява за съвпадение между втория символен низ и една от думите.
    static bool isAmongKeywords(const String& keywords, const String& word);
};

#endif
