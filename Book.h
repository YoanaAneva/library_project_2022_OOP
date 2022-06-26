#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED

#include "Item.h"

///Клас Book наследяващ Item, представлява данните за артикул от библиотеката от тип книга.
///@param author име на автор @param yearOfPublishing година на издаване @param keywords ключови думи @param isbn ISBN номер
class Book : virtual public Item{
private:
    String author;
    int yearOfPublishing;
    String keywords;
    String isbn;

private:
    void copy(const Book& other);

public:
    ///Извиква конструктора по подразбиране на базовия си клас Item, задава типа и подразбираща се стойсност на ISBN номера
    Book();
    
    ///Извиква конструктора с параметри на базовия си клас и проверява за възникване на изключение в "сетърите". При прихващане на такова, const String&
    ///задава подразбиращи се стойности на променливите.
    ///Вероятността за възникване на изключение, заради невалидни стойнтости, е минимална, понеже невалидни данни от потребителя не се подават, а файловете,
    ///от които идват данните са създадени от валидни обекти.
    ///Има два конструктора с параметри - единия приема ISBN номер, а другият - не.
    Book(const String& title, const String& publisher, const String& genre, const String& description, float rating, const String& author, int yearOfPublishing, const String& keywords, const String& isbn);
    Book(const String& title, const String& publisher, const String& genre, const String& description, float rating, const String& author, int yearOfPublishing, const String& keywords);
    
    ///Поради липсата на динамично заделена памет се посочва, че ще се използва системният копиращ конструктор(което разбира се може да се изпусне, правя го за да е нагледно).
    Book(const Book& other) = default;

    Book& operator=(const Book& other) = default;
    ///Не е задължителен
    virtual ~Book() = default;
    
    void setAuthor(const String& author);
    void setYearOfPublishing(int yearOfPublishing);
    void setKeywords(const String& keywords);
    void setIsbn(const String& isbn);

    const String& getAuthor() const;
    int getYearOfPublishing() const;
    const String& getKeywords() const;
    const String& getIsbn() const;

    ///Предефинира функцията Item::writeInFile() на базовия си клас Item, и я използва, за да запише наследените от Item данни в текстов файл. Записва различни данни спрямо това дали обектът има ISBN номер.
    ///@param output потокът за записване на данните
    virtual void writeInFile(std::ofstream& output) const override;
    
    ///Предефинира функцията Item::readFromFile() на базовия си клас Item и я използва, за да прочете наследените от Item данни от текстов файл
    ///Използва char buffer[1024], за да прочита текста и да го присвоява на променливите, или за да изчита ненужния текст(като '|' или ']') и да мести указателя.
    ///Типът на функцията е void, тя променя обекта, използвайки "сетърите" му и при възникване на изключение от тях, го прихваща и задава подразбиращи се стойностти на променливите.
    ///@param input потокът за четене на данните
    virtual void readFromFile(std::ifstream& input) override;
    
    ///Предефинира функцията "readFromUser" на базовия си клас Item, и я използва, за да прочете от конзолата данните от потребителя
    ///Потребителят е принуждаван да въвежда текст, докато не попаде валидни данни, затова използването на мутаторите се прескача.
    virtual void readFromUser() override;
    
    ///Извежда данните на обекта, предефинира функцията Item::print() на базовия си клас Item и я използва, за да изведе данните, част от класа Item. Извежда различни данни спрямо това дали обектът има ISBN номер.
    virtual void print() const override;
    
    ///Предефинира чисто абстрактната функция на базовия си клас Item, връща копие на себе си (използва копиращия си конструктор),
    ///прави се "deep copy", за да може обект от тип Item* да има собствено копие от данните на Book. 
    virtual Item* clone() const override;

    ///Валидира ISBN номера, като проверява дали размерът му е различен от 17 и дали съдържа нужните символи.
    static bool isValidIsbn(const String& isbn);
};

#endif
