#ifndef SERIES_H_INCLUDED
#define SERIES_H_INCLUDED

#include "Item.h"
///Структура, обединяваща данните за една статия 
struct Article{
private:
    String header;
    String author;
    String keywords;
public:
    ///Поради наличието на конструктор с параметри, системен подразбиращ се конструктор няма да се генерира, ако не му посочим.
    Article() = default;

    Article(const String& header, const String& author, const String& keywords);
    ///Не е задължителен.
    Article& operator=(const Article& other) = default;

    const String& getAuthor() const;
    const String& getKeywords() const;
    ///Предефинира оператора ""<<" за извеждане на данните на обект от тип Article. Използва се при записване във файл и извеждане на статия в конзолата.
    friend std::ostream& operator<<(std::ostream& output, const Article& article);
    ///Предефинира оператора ">>" за четене на данните на обект от тип Article. Използва се при четене на статия от файл и от стандартния изход.
    friend std::istream& operator>>(std::istream& input, Article& article);

    ///Чете данни подадени от потребителя в конзолата, не допуска въвеждането на невалидни данни.
    void readFromUser();

    void print() const;
};


///Клас Series наследяващ Item, представлява данните за артикул от библиотеката от тип печатно издание.
///@param dateOfPublishing дата на публикуване - месец и година @param issue брой @param issn ISSN номер 
///@param content масив от статии @param articlesCount размер на масива от статии
class Series : virtual public Item{
private:
    String datePublishing;
    unsigned issue;
    String issn;
    Article* content;
    unsigned articlesCount;

    void copy(const Series& other);
    void erase();
public:
    ///Извиква конструктора по подразбиране на базовия си клас Item, задава стойности по подразбиране, задава типа.
    Series();

    /////Извиква конструктора с параметри на базовия си клас и проверява за възникване на изключение в "сетърите". При прихващане на такова,
    ///задава подразбиращи се стойности на променливите.
    ///Вероятността за възникване на изключение, заради невалидни стойнтости, е минимална, понеже невалидни данни от потребителя не се подават, а файловете,
    ///от които идват данните са създадени от валидни обекти.
    ///Има два конструктора с параметри - единия приема ISSN номер, а другият - не.
    Series(const String& title, const String& publisher, const String& genre, const String& description, float rating, const String& datePublishing, int issue, Article* content, int articlesCount, const String& issn);
    Series(const String& title, const String& publisher, const String& genre, const String& description, float rating, const String& datePublishing, int issue, Article* content, int articlesCount);
    
    ///Извиква копиращия конструктор на Item и функцията copy, която създава "deep copy" за новия обект. Поради наличието на заделяне на динамична памет не може да се използва системния копиращ конструктор.
    Series(const Series& other);

    ///Проверява се дали подаденият обект е различен от текущият, преди да се освободи заделената памет за масива и да се извика copy, извиква се и оператора= на базовия клас Item. 
    Series& operator=(const Series& other);

    ///Освобождава заделената памет за масива от статии.
    virtual ~Series();

    void setDatePublishing(const String& datePublishing);
    void setIssue(int issue);
    void setIssn(const String& issn);
    void setContent(const Article* articles, int articlesCount);

    const String& getDatePublishing() const;
    unsigned getIssue() const;
    const String& getIssn() const;
    const Article* getContent() const;
    unsigned getArticlesCount() const;

    ///Предефинира функцията Item::writeInFile() на базовия си клас Item, и я използва, за да запише наследените от Item данни в текстов файл. 
    ///Записва различни данни спрямо това дали обектът има ISSN номер. Записва броят на статиите и за всяка една използва предефинирания оператор "<<".
    ///@param output потокът за записване на данните
    virtual void writeInFile(std::ofstream& output) const override;

    ///Предефинира функцията Item::readFromFile() на базовия си клас Item и я използва, за да прочете наследените от Item данни от текстов файл.
    ///Използва char buffer[1024], за да прочита текста и да го присвоява на променливите, или за да изчита ненужния текст(като '|' или ']') и да мести указателя.
    ///Типът на функцията е void, тя променя обекта, използвайки "сетърите" му и при възникване на изключение от тях, го прихваща и задава подразбиращи се стойностти на променливите.
    ///@param input потокът за четене на данните
    virtual void readFromFile(std::ifstream& input) override;

    
    ///Предефинира функцията readFromUser() на базовия си клас Item, и я използва, за да прочете от конзолата данните от потребителя
    ///Потребителят е принуждаван да въвежда текст, докато не попаде валидни данни, затова използването на мутаторите се прескача.
    virtual void readFromUser() override;

    ///Предефинира чисто абстрактната функция на базовия си клас Item, връща копие на себе си (използва копиращия си конструктор),
    ///прави се "deep copy", за да може обект от тип Item* да има собствено копие от данните на Book. 
    virtual Item* clone() const override;

    ///Извежда данните на обекта, предефинира функцията Item::print() на базовия си клас Item и я използва, за да изведе данните, част от класа Item. Извежда различни данни спрямо това дали обектът има ISSN номер.
    virtual void print() const override;

    ///Валидира ISBN номера, като проверява дали размерът му е различен от 9 и дали съдържа нужните символи.
    static bool isValidIssn(const String& issn);
};

#endif
