#ifndef READER_H_INCLUDED
#define READER_H_INCLUDED

#include "BorrowedItem.h"
#include "User.h"

///Клас, който наследява клас User, съдържа информацията относно потребител от тип "Читател".
///@param borrowedItems масив от обекти от тип BorrowedItems, пази информацията за заетите артикули @param size размер на масива  @param capacity капацитет на масива
class Reader : public User{
private:
    BorrowedItem* borrowedItems;
    unsigned size;
    unsigned capacity;

    void copy(const Reader& other);
    void resize();
    void erase();

public:
    ///Подразбиращ се конструктор, задава типа, заделя памет за масива от заети артикули
    Reader();
    
    ///конструктор с параметри - извиква конструкторa с параметри на User, като му подава съответните параметри. Заделя памет за масива. 
    ///Всеки читател се създава с празен масив от заети артикули
    Reader(const String& username, const String& password, const Date& regDate, const Date& lastVisit);
    
    ///Извиква копиращия конструктор на User и функцията copy, която създава "deep copy" за новия обект. Поради наличието на заделяне на динамична памет не може да се използва системния копиращ конструктор.
    Reader(const Reader& other);

    ///Проверява се дали подаденият обект е различен от текущият, преди да се освободи заделената памет за масива и да се извика copy. 
    Reader& operator=(const Reader& other);

    ///Освобождава заделената памет за масива от заети артикули.
    virtual ~Reader();

    ///Представлява заемане на книга. Артикулът, към който сочи newItem, се подава на конструкторът на BorrowedItem и се създава нов обект 
    ///от тип BorrowedItem, с дата на заемане- текущата дата и дата на връщане- месец по-късно. Артикулът се добавя към списъка от заети неща на читателя.
    void borrowItem(Item* newItem);

    ///Функция, чиято цел е да добавя артикул към списъка от заети неща на читателя. Параметърът, който приема, е вече създаден обект от тип BorrowedItem, 
    ///с ръчно въведени дати. (Т.е. имитира се заемане и връщане на артикул със задна дата, за да се запише читателят във файл със заетите неща). Използва се за по-голяма възможност да се демонстрират функционалностите на проекта.
    void addItemToList(const BorrowedItem& newItem);

    const BorrowedItem& getBItem(unsigned ind) const;
    BorrowedItem& getBItemById(unsigned id) const;
    unsigned getBItemsCount() const;

    ///Предефинира функцията User::writeInFile() на базовия си клас User, и я използва, за да запише наследените от User данни. Записва се броят на заетите артикули и за всеки един се използва BorrowedItem::writeInFile().
    ///@param output потокът за записване на данните
    virtual void writeInFile(std::ofstream& output) const override;

    ///Предефинира функцията User::readFromFile() на базовия си клас User и я използва, за да прочете наследените от User данни. char buffer[1024] се използва, за да съхранява прочетения текст, да 
    ///изчита ненужните символи и да мести указателя. Прочита се броят на заетите артикули от текущия записан читател и толкова пъти се извиква функцията за четене на всеки артикул, той се прочита и се добавя в масива.
    ///@param input потокът за четене на данните
    virtual void readFromFile(std::ifstream& input) override;

    ///Предефинира чисто абстрактната функция на базовия си клас User, връща копие на себе си (използва копиращия конструктор),
    ///прави се "deep copy", за да може обект от тип User* да има собствено копие от данните на Reader. 
    virtual User* clone() const override;

    ///Извежда данните на обект от тип Reader, предефинира функцията User::print() на базовия си клас User и я използва, за да изведе данните, част от класа User. 
    virtual void print() const override;
};

#endif