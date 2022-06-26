#ifndef BORROWED_ITEM_H_INCLUDED
#define BORROWED_ITEM_H_INCLUDED

#include "Item.h"
#include "Book.h"
#include "Series.h"

///Клас, чиято идея е да "разшири" класовете Book и Series, като им добави дата на взимане и връщане.
///Целта на обектите от този клас е да съдържат информацията за книгата или изданието и съответните дати, 
///за да бъдат включени в записа на всеки читател.
///@param item сочи към съответния обект от тип Item*, като това може да бъде книга или издание.
///@param checkoutDate дата на заемане на артикула @param returnDate дата на връщане на артикула, може да е датата, на която е бил заеман 
///или датата, на която трябва да се върне
class BorrowedItem{
private:
    Item* item;
    Date checkoutDate;
    Date returnDate;

    void copy(const BorrowedItem& other);

public:
    ///Пренасочва указателя на артикула към nullptr.
    BorrowedItem();

    ///Присвоява стойности на съответните параметри.Използва се при създаването на артикул, който да се включи към списъка на читателя,
    /// но не се заема на момента.
    BorrowedItem(Item* item, const Date& d1, const Date& d2);
    
    ///Приема само указател към Item*, присвоява на датата на заемане сегашната дата, а на датата на връщане - сегашната с един месец напред.
    ///Използва се при заумането на артикул на момента.
    BorrowedItem(Item* item);

    ///Извиква се private функцията copy(), която от своя страна използва фукнцията Book::clone() или Series::clone, за да създаде копие на
    ///данните, към които сочи указателя на обекта const BorrowedItem& other и указателят на текущия обект да сочи към свое копие на тези данни. 
    BorrowedItem(const BorrowedItem& other);

    ///Проверява се дали не се прави опит данните на обекта да се присвоят на същия този обект. Ако не  
    BorrowedItem& operator=(const BorrowedItem& other);

    ~BorrowedItem();

    void setItemPtr(Item* item);
    void setCheckoutDate(const Date& checkoutDate);
    void setReturnDate(const Date& returnDate);

    ///Селектор, който връща указател, към това къв което сочи this->item
    Item* getItemPtr() const;
    const Date& getCheckoutDate() const;
    const Date& getReturnDate() const;

    ///В зависимост от типа на сочения артикул използва функцията Book::writeInFile() или Series::writeInFile(), за да запише наследените му в текстов файл. След това добавя датите.
    ///Използва се явно преобразуване на указателя от Item* към Book* или Series*, за да се използват съответните им функции.
    ///@param output потокът за записване на данните
    void writeInFile(std::ofstream& output) const;
   
    ///Предефинира функцията Item::readFromFile() на базовия си клас Item и я използва, за да прочете наследените от Item данни от текстов файл
    ///Използва char buffer[120], за да прочита текста и да го присвоява на променливите, или за да изчита ненужния текст(като '|' или ']') и да мести указателя. В зависимост от прочетения символ,
    ///който може да бъде 'B'(за книга) или 'S'(за печатно издание) се създава нов обект от съответния тип и се използва неговия метод за четене от файл.
    ///Типът на функцията е void, тя променя обекта, използвайки мутаторите му и при възникване на изключение от тях, го прихваща и задава подразбиращи се стойностти на променливите.
    ///@param input потокът за четене на данните
    void readFromFile(std::ifstream& input);

    void print() const;
};


#endif