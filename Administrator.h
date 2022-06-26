#ifndef ADMINISTRATOR_H_INCLUDED
#define ADMINISTRATOR_H_INCLUDED

#include "User.h"
///Клас, който наследява клас User, съдържа информацията относно потребител от тип "Администратор".
///@param email служебен имейл @param department отдел, за който отговаря администраторът
class Administrator : public User {
private:
    String email;
    String department;
public:
    ///конструктор по подразбиране - извиква конструкторa по подразбиране на User и посочва типа на потребителя.
    Administrator();
    ///конструктор с параметри - извиква конструкторa с параметри на User, като му подава съответните параметри и инициализира специалните за клас Administrator.
    ///Проверява за изключения, и при прихванато такова, задава подразбиращи се стойности на променливите.
    ///Вероятността за възникване на изключение, заради невалидни стойнтости, е минимална, понеже невалидни данни от потребителя не се подават, а файловете,
    ///от които идват данните са създадени от валидни обекти.
    Administrator(const String& username, const String& password, const Date& regDate, const Date& lastVisit, const String& email, const String& department);
    ///Посочвам, че знам, че няма нужда да пиша свой копиращ конструктор, понеже нямам заделяне на динамична памет и ще използвам системно генерирания.
    Administrator(const Administrator& other) = default;

    Administrator& operator=(const Administrator& other) = default;

    ///Посочвам, че използвам системния, понеже нямам заделена динамична памет
    virtual ~Administrator() = default;

    ///@param email с него се инициализира служебният имейл, ако е невалиден се хвърля изключение 
    void setEmail(const String& email);
    ///@param department с него се инициализира отделът, ако е невалиден се хвърля изключение 
    void setDepartment(const String& department);
    
    ///Предефинира функцията User::writeInFile() на базовия си клас User, и я използва, за да запише наследените от User данни
    ///@param output потокът за записване на данните
    virtual void writeInFile(std::ofstream& output) const override;
    ///Предефинира функцията User::readFromFile() на базовия си клас User и я използва, за да прочете наследените от User данни
    ///@param input потокът за четене на данните
    virtual void readFromFile(std::ifstream& input) override;

    ///Предефинира чисто абстрактната функция на базовия си клас User, връща копие на себе си (използва копиращия конструктор),
    ///прави се "deep copy", за да може обект от тип User* да има собствено копие от данните на Administrator. 
    virtual User* clone() const override;
    ///Извежда данните на обект от тип Administrator, предефинира функцията User::print() на базовия си клас User и я използва, за да изведе данните, част от класа User. 
    virtual void print() const override;

    ///Валидира имейл като за невалиден имейл се счита такъв, който не съдържа '@', съдържа две последователни точки, започва с точка, 
    ///с "local" част по-дълга от 64 символа, такъв, който съдържа някой от специалните символи "(),:;<>@[\], но той не се намира между кавички
    ///,или "domain" частта му съдържа символи различни от буква, точка или тире
    static bool isValidEmail(const String& str);
    ///Валидира отдел, като за невалиден отдел счита такъв без текст или съдържащ символ различен от буква, запетая, тире.
    static bool isValidDepartment(const String& department);
};

#endif