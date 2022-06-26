#include "String.h"

void String::copy(const String& other){
    this->size = other.size;

    this->data = new char[size + 1];
    strcpy(this->data, other.data);
}

void String::erase(){
    delete[] this->data;
}

String::String(){
    this->size = 0;
    this->data = new char[1];
    this->data[0] = '\0';
}

String::String(const char* data){
    this->size = strlen(data);  
    this->data = new char[size + 1];
    strcpy(this->data, data);
}

String::String(const String& other){
    this->copy(other);
}

String& String::operator=(const String& other){
    if(this != &other){
        this->erase();
        this->copy(other);
    }
    return *this;
}

String::~String(){
    this->erase();
}

unsigned String::getSize() const {return this->size; }
const char* String::getData() const {return this->data; }

const char String::operator[](int index) const{
    return this->data[index];
}

char& String::operator[](int index){
    return this->data[index];
}

std::ostream& operator<<(std::ostream& output, const String& str){
    output << str.data;
    return output;
}

std::istream& operator>>(std::istream& input, String& str){
    unsigned bufferSize = 1024;
    char buffer[bufferSize];
    input.getline(buffer, bufferSize, '\n');
    str.size = strlen(buffer);

    str.data = new char[str.size + 1];
    strcpy(str.data, buffer);

    return input;
}

bool String::operator==(const String& other){
    return strcmp(this->data, other.data) == 0;
}

bool String::operator!=(const String& other){
    return !(*this == other);
}

bool operator==(const String& lhs, const String& rhs){
    return strcmp(lhs.data, rhs.data) == 0;
}

bool operator!=(const String& lhs, const String& rhs){
    return !(lhs == rhs);
}

String& String::operator+=(const String& rhs){
    char* temp = new char[this->size + 1];
    strcpy(temp, this->data);

    this->erase();
    this->data = new char[this->size + rhs.size + 1];

    for(int i = 0; i < this->size; i++)
        this->data[i] = temp[i];
    for(int i = 0; i < rhs.size; i++)
        this->data[i + this->size] = rhs.data[i];
    
    this->size += rhs.size;
    this->data[size] = '\0';

    delete[] temp;

    return *this;
}

String& String::operator+=(char symbol){
    char* temp = new char[this->size + 2];
    strcpy(temp, this->data);
    temp[this->size] = symbol; 
    temp[this->size + 1] = '\0';

    this->data = new char[this->size + 2];
    strcpy(this->data, temp);

    this->size++;
    delete[] temp;

    return *this;
}

int String::convertToNumber(const String& str){
    for(int i = 0; i < str.getSize(); ++i){
        if(str[i] < '0' || str[i] > '9'){
            std::cout << "\nInvalid number, negative or contains invalid symbols\n\n";
            return -1;
        }
    }
    int number = 0;
    for(int i = 0; i < str.size; ++i){
        number = number * 10 + str[i] - '0';
    }
    return number;
}

String String::getSurname(const String& name){
    int spacesCount = 0;

    for(int i = 0; name[i] != '\0'; ++i){
        if(name[i] == ' ') 
            spacesCount++;
    }

    unsigned numOfWords = spacesCount + 1;
    String* words = new String[numOfWords];

    int k = 0;
    for(int i = 0; i < numOfWords; ++i){
        for(; name[k] != ' '; ++k){
            words[i] += name[k];
        }
        ++k;
    }
    return words[numOfWords - 1];
}
