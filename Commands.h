#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

#include "Library.h"
#include "System.h"

enum SupportedCommands{
    Help, Exit,
    Login, Logout,
    BooksAll, BooksFind, BooksAdd, BooksRemove, BooksView,
    SeriesAll, SeriesFind, SeriesAdd, SeriesRemove, SeriesView, 
    ListAll, ListFind, ListInfo, 
    UserFind, UserAdd, UserRemove, UserChange,
    Take, Return,
    Invalid
};


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
    CommandInfo() = default;
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


class Commands{
public:
    String commands[21]{
        "help", "login", "logout", 
        "books all", "books find"/**/, "books add", "books remove",
        "series all",  "series find"/**/, "series add",  "series remove",
        "list all", "list info"/**/,  "list find"/**/, 
        "user find"/**/, "user add"/**/, "user remove"/**/, "user change"/**/, 
        "take"/**/, "return"/**/, "exit"
    };

public:
    static CommandInfo recognizeCommand(const char* str);
    static void reverseArr(Paper** items, unsigned size);

    //commands
    static void help();
    static void login(UserBase&);
    static void logout(UserBase&);
    static void books_all(const Library&);
    static void books_find(const Library&, const CommandInfo&);
    static void books_add(Library&);
    static void books_remove(Library&);
    static void books_view(const Library&, const CommandInfo&);
    static void series_all(const Library&);
    static void series_find(const Library&, const CommandInfo&);
    static void series_add(Library&);
    static void series_remove(Library&);
    static void series_view(const Library& library, const CommandInfo& command);
    static void list_all(const Library&);
    static void list_find(const CommandInfo&);
    static void list_info(const Library&, const CommandInfo&);
    static void user_find(const Library&, const UserBase&, const CommandInfo&);
    static void user_add(UserBase&, const CommandInfo&);
    static void user_remove(UserBase&, const CommandInfo&);
    static void user_change(UserBase&, const CommandInfo&);
    static void take(Library&, UserBase&, const CommandInfo&);
    static void return_(Library&, UserBase&, const CommandInfo&);
};

#endif