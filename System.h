#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include "Library.h"
#include "UserBase.h"
#include "Commands.h"

///Клас обединяващ данните за артикулите в библиотеката и потребителите в системата.
class System{
private:
    Library library;
    UserBase userBase;

public:
    ///Функция, която при нужда може да зареди данни за системата.
    
    void loadData();
    ///Функция, която при нужда може да зареди данни за системата от текстов файл.
    ///(За проекта е избрано записването и четенето на данни от текстови файлове, заради удобството да виждаш какво записваш и какво четеш.)
    void loadDataFromFile();
    
    ///Функция, която стартира избора на команди от потребителя. Потребителят бива каран да въвежда команди до въвеждането на
    ///командата "exit". Функцията приема текста въведен в конзолата и го подава на Commands::recognizeCommand(). Тя връща обект от
    ///тип CommandInfo и според типа на командата се извиква отговарящата функция, като преди това се проверява дали потребителят отговаря 
    ///на изискванията на командата(дали е читател, дали е администратор, дали е логнат).
    void getCommands();

    void writeInFile();
};

#endif