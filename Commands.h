#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

#include "System.h"

enum SupportedCommands{
    Help, Exit,
    Login, Logout,
    BooksAll, BooksFind, BooksAdd, BooksRemove, BooksView,
    SeriesAll, SeriesFind, SeriesAdd, SeriesRemove, SeriesView, 
    ListAll, ListFind, ListInfo, 
    UserFind, UserAdd, UserRemove, UserChange,
    Take, Return,
    LoadData,
    Invalid
};

///Структура, чиято цел е да обедини информацията относно една команда
///@param type типът на командатар по който тя се разпознава  @param title името на командата(използва се само за нагледност)  
///@param values масив от "стрингове", които съдържат различни допълнения към командата  @param valuesCount броят им 
///@param hasSort пази информация дали командата има сортираща функция @param isAscending пази информация за вида на сортирането
///@param sortKey стойността, по която ще се сортира.
struct CommandInfo{
private:
    SupportedCommands type;
    String title;
    String* values;
    unsigned valuesCount;
    bool hasSort;
    bool isAscending;
    String sortKey;
public:
    ///Ако изрично не посочим, че искаме конструктор по подразбиране, компилаторът няма да генерира такъв, заради наличието на конструктор с параметри.
    CommandInfo() = default;
    
    ///За командите, състоящи се от една дума
    CommandInfo(const SupportedCommands& type, const String& text);
    CommandInfo(const SupportedCommands& type, const String& title, String* values, unsigned valuesCount, bool hasSort, bool isAscending, const String& sortKey);
    
    const SupportedCommands& getType() const;
    const String* getValues() const;
    unsigned getValuesCount() const;
    bool getHasSort() const;
    bool getIsAscending() const;
    const String& getSortKey() const;

    void print() const;
};

///Класът представлява колекция от статични команди, които системата поддържа
class Commands{
public:
    ///Функция, която приема прочетения от конзолата текст и го разпознава. Връща обект от тип CommandInfo, носещ информация за съответната команда, ако такава не е 
    ///разпозната връща обект CommandInfo от тип Invalid. 
    ///Разделя текста на думи от тип String, проверява дали първата дума съотвества на някоя от командите, това дава възможност, ако например потребителят въведе "logout some text"
    ///да разпознае командата Logout. Прави се проверка на останалите думи, като потребителят е насочван към формата на командата, която се опитва да въведе.
    static CommandInfo recognizeCommand(const char* str);
    
    ///Функция, която се използва за преобръщане на сортиран масив, за да се спестят повторни сортирания, ако функцията трябва да сортира в низходящ ред.
    static void reverseArr(Item** items, unsigned size);

    ///Функция, която извежда информация за всички поддържани команди.
    static void help();
    ///Функция, за вход на регистриран потребител.
    static void login(UserBase&);
    ///Функция, за изход на регистриран потребителл
    static void logout(UserBase&);
    ///Функция, която извежда информация(заглавие, тип, жанр, идентификационен номер) за всички книги в системата.
    static void books_all(const Library&);
    ///Функция, която филтрира и сортира книгите по зададени критерии.
    static void books_find(const Library&, const CommandInfo&);
    ///Функция, която добавя нова книга в системата, с данни въведени от конзолата. Изисква се цялостно презаписване на library във файлa понеже данните се съхраняват сортирани
    static void books_add(Library&);
    ///Функция, която премахва книга от системата по подаден идентификационен номер. Изисква се презаписване на library във файла.
    static void books_remove(Library&);
    ///Функция, която извежда подробна информация за книгата с подадения идентификационен номер.
    static void books_view(const Library&, const CommandInfo&);
    ///Функция, която извежда информация(заглавие, тип, жанр, идентификационен номер) за всички печатни издания в системата.
    static void series_all(const Library&);
    ///Функция, която 
    static void series_find(const Library&, const CommandInfo&);
    ///Функция, която филтрира и сортира печатните издания по зададени критерии.
    static void series_add(Library&);
    ///Функция, която премахва печатно издание по подаден идентификационен номер.
    static void series_remove(Library&);
    ///Функция, която извежда подробна информация за печатното издание с подадения идентификационен номер.
    static void series_view(const Library&, const CommandInfo& command);
    ///Функция, която извежда информация(заглавие, тип, жанр, идентификационен номер) за всички артикули в системата.
    static void list_all(const Library&);
    ///Функция, която филтрира и сортира артикулите от библиотеката по зададени критерии.
    static void list_find(const Library&, const CommandInfo&);
    ///Функция, която извежда подробна информация за артикула с подадения ISBN/ISSN номер.
    static void list_info(const Library&, const CommandInfo&);
    ///Функция, която извежда всички потребители от системата, отговарящи на определен критерий.
    static void user_find(const Library&, const UserBase&, const CommandInfo&);
    ///Функция, която добавя нов потребител в системата с посочени потребителско име и парола. Изисква се цялостно презаписване на userBase във файла, понеже данните се съхраняват сортирани.
    static void user_add(UserBase&, const CommandInfo&);
    ///Функция, която премахва потребител от системата с посочено потребителско име. Изисква се презаписване на userBase във файла, понеже се премахва потребител. 
    static void user_remove(UserBase&, const CommandInfo&);
    ///Функция, която променя паролата на логнатия потребител. Ако е посочено име, се изисква да е логнат admin. Изисква се презаписване на userBase, понеже се променя състоянието на даден потребител от масива.
    static void user_change(UserBase&, const CommandInfo&);
    ///Функция, която представлява заемане на книга с подаден номер. Книгата се отбелязва като заета и се добавя в списъка на потребителя. Изисква презаписване на library и userBase, понеже състоянието на обект и от двата масива се променя.
    static void take(Library&, UserBase&, const CommandInfo&);
    ///Функция, която представлява връщане на книга с подаден номер. Книгата се отбелязва като свободна. Изисква презаписване на library и userBase, понеже състоянието на обект и от двата масива се променя.
    static void return_(Library&, UserBase&, const CommandInfo&);
};

#endif