#include <iostream>
#include <cstring>
#include "Date.h"
// class Names{
// private:
//     String* names;
//     int size;
//     int capacity;
// public:
//     Names(){
//         this->capacity = 24;
//         this->size = 1;
//         this->names = new String[capacity];
//         this->names[0] = "Divider";
//     }
//     void addName(const String& newName){
//         for(int i = 0; i < size; i++){
//             if(names[i] == "Divider"){
//                 names[i + 1] = names[i];
//                 names[i] = newName;
//             }
//             if(strcmp(newName.getData(), names[i].getData()) < 0){
//                 for(int j = size; j > i; --j){
//                     names[j] = names[j - 1];
//                 }
//                 names[i] = newName;
//                 break;
//             }
//         }
//         ++size;
//     }

//     void print(){
//         for(int i = 0; i < size; i++){
//             std::cout << names[i] << std::endl;
//         }
//     }
// };

void function(int a, String* strs){
    if(a == 1){
        strs = new String[3];
        strs[0] = "one";
        strs[1] = "what shall I do?";
        strs[2] = "end";
    }
    else{
        strs[0] = "number";
        strs[1] = "what shall I do?";
        strs[2] = "end";
    }
}

void readFromUser(){
    String title, publisher, genre, description;
    float rating;
    std::cout << "Enter title: ";
    std::cin >> title;
    std::cout << "Enter publisher: ";
    std::cin >> publisher;

    do{
        std::cout << "Enter genre: ";
        std::cin >> genre;
    }while(genre[0] != 'a');

    std::cout << "Enter description: ";
    std::cin >> description;

    do{
        std::cout << "Enter rating: ";
        std::cin >> rating;
    }while(rating < 0);

    std::cout << title << " " << publisher << " " << genre << " " << description;
}

// int main(){
    // std::cout << strcmp("Nilsen", "Nolsen") << std::endl;
    // std::cout << strcmp("Ivana", "Ivan") << std::endl;
    // std::cout << strcmp("Mom", "Alabala") << std::endl;

    // Names n;
    // n.addName("Hole");
    // n.addName("Hello world");
    // n.addName("Yoana");
    // n.addName("Ivana");
    // n.addName("Natali");
    // n.addName("Gosho");
    // n.addName("Fuck you");
    // n.print();

    // std::ofstream out("t.txt");
    // out << "{{alabala\nhello";
    // out.close();

    // char str[] = "books find title Learn to cook";
    // char command[1024];
    // int i = 0;
    // for(; str[i] != ' '; ++i){
    //     command[i] = str[i];
    // }
    // std::cout << command << std::endl;
    // if(strcmp(command, "books") == 0){
    //     command[i] = ' ';
    //     std::cout << "dkwoefj" << std::endl;
    //     i++;
    //     for(; str[i] != ' '; ++i){
    //         command[i] = str[i];
    //         std::cout << command[i] << " " << str[i] << std::endl;
    //     }
    //     command[i] = '\0';
    //     std::cout << command << std::endl;
    //     if (strcmp(command, "books find") == 0){
    //         std::cout << "its fine" << std::endl;
    //     }
    //     else{
    //         std::cout << "fuck" << std::endl;
    //     }
    // }

    // String* newStrs;
    // function(3, newStrs);
    // for(int i = 0; i < 3; ++i){
    //     std::cout << newStrs[i] << std::endl;
    // }
    // readFromUser();
    // char str[] = "";
    // float num = strtof(str, nullptr);
    // std::cout << num + 0.03 << std::endl;
// }

