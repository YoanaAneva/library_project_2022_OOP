#include <iostream>
#include <cstring>
#include "String.h"

class Names{
private:
    String* names;
    int size;
    int capacity;
public:
    Names(){
        this->capacity = 24;
        this->size = 1;
        this->names = new String[capacity];
        this->names[0] = "Divider";
    }
    void addName(const String& newName){
        for(int i = 0; i < size; i++){
            if(names[i] == "Divider"){
                names[i + 1] = names[i];
                names[i] = newName;
            }
            if(strcmp(newName.getData(), names[i].getData()) < 0){
                for(int j = size; j > i; --j){
                    names[j] = names[j - 1];
                }
                names[i] = newName;
                break;
            }
        }
        ++size;
    }

    void print(){
        for(int i = 0; i < size; i++){
            std::cout << names[i] << std::endl;
        }
    }
};

// int main(){
//     // std::cout << strcmp("Nilsen", "Nolsen") << std::endl;
//     // std::cout << strcmp("Ivana", "Ivan") << std::endl;
//     std::cout << strcmp("Mom", "Alabala") << std::endl;

//     Names n;
//     n.addName("Hole");
//     n.addName("Hello world");
//     n.addName("Yoana");
//     n.addName("Ivana");
//     n.addName("Natali");
//     n.addName("Gosho");
//     n.addName("Fuck you");
//     n.print();
// }