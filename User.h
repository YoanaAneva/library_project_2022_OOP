#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include "String.h"
#include "Date.h"
#include "Item.h"

enum UserType{
    DUMMY,
    READER,
    ADMINISTRATOR
};

///Клас представляващ общите данни за потребителите на библиотеката. Класът е абстрактен, от него не се създават обекти.
///Целта му е да бъде наследен от различти видове потребители, които да го допълнят и осмислят.
class User{
protected:
    String username;
    String password;
    Date regDate;
    Date lastVisit;

    UserType type;

public:
    User() = default;
    ///конструктор с параметри - инициализира стойностите на променливите. 
    ///Проверява за изключения, и при прихванато такова, задава подразбиращи се стойности на променливите.
    ///Вероятността за възникване на изключение, заради невалидни стойнтости, е минимална, понеже невалидни данни от потребителя не се подават, а файловете,
    ///от които идват данните са създадени от валидни обекти.
    User(const String& username, const String& password, const Date& regDate, const Date& lastVisit, const UserType type);
    ///Не е задължителен, поради липсата на динамично задалени данни може да се използва системния.
    User(const User& other) = default;

    User& operator=(const User& other) = default;

    virtual ~User() = default;

    void setUsername(const String& username);
    void setPassword(const String& password);
    void setRegDate(const Date& regDate);
    void setLastVisit(const Date& lastVisit);

    const String& getUsername() const;
    const String& getPassword() const;
    const Date& getRegDate() const;
    const Date& getLastVisit() const;
    const UserType& getType() const;

    ///Виртуална функция, която записва данните на обекта в текстов файл. Тя ще бъде използвана и предефинирана от наследниците.
    /// Първо се записва символ, определящ типа на потребителя, което е полезно при четенето на множество потребители.
    virtual void writeInFile(std::ofstream& output) const;

    ///Виртуална функция която записва данните на обекта в текстов файл. Тя ще бъде използвана и предефинирана от наследниците.
    ///Използва char buffer[1024], за да запазва в него проченетия текст, да изчита ненужните символи и да мести указателя. Използва 
    /// мутаторите и при прихващане на изключение, задава подразбиращи се стойности.
    virtual void readFromFile(std::ifstream& input);

    ///Чисто виртуална функция, която всеки наследник трябва да предефинира. Повече за нея Reader::clone(), Administrator::clone().
    virtual User* clone() const = 0;

    ///Статична функция, която проверява дали две пароли съвпадат.
    static bool areSamePasswords(const String& p1, const String& p2);

    static bool isValidPasswords(const String& str);

    ///Виртуална функция, която изкарва данните за всеки потребител в конзалата, предефинира се и се използва от наследниците.
    virtual void print() const;
};

#endif