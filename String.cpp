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
    // std::cout << "Default ctor called for string" << std::endl;
    this->size = 1;
    this->data = new char[2];
    strcpy(this->data, " ");
}

String::String(const char* data){
    this->size = strlen(data);  
    this->data = new char[size + 1];
    strcpy(this->data, data);
}

String::String(const String& other){
    // std::cout << "Copy ctor called for string" << std::endl;
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
    // std::cout << "Destructor called for string" << std::endl;
    this->erase();
}

int String::getSize() const {return this->size; }
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
    int bufferSize = 1024;
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

unsigned String::convertToNumber(const String& str){
    for(int i = 0; i < str.size; ++i){
        if(str[i] < '0' || str[i] > '9')
            throw "Invalid number, negative or contains invalid symbols";
    }
    int number = 0;
    for(int i = 0; i < str.size; ++i){
        number = number * 10 + str[i] - '0';
    }
    return number;
}


void String::writeInBin(std::ofstream& output){
    size_t dataLen = this->size + 1;
    output.write(reinterpret_cast<const char*>(&dataLen), sizeof(dataLen));
    output.write(this->data, dataLen);
}

void String::readFromBin(std::ifstream& input, String& str){
    size_t dataLen;
    input.read(reinterpret_cast<char*>(&dataLen), sizeof(dataLen));

    delete[] str.data;
    str.data = new char[dataLen];
    input.read(str.data, dataLen);

    int capacity;
    input.read(reinterpret_cast<char*>(&capacity), sizeof(capacity));

    str.size = dataLen - 1;
}

// int main(){
    // String myStr("Hello world");
    // String otherStr("Fuck you");

    // std::ofstream output("String.bin", std::ios::binary);

    // myStr.writeInBin(output);
    // otherStr.writeInBin(output);

    // output.close();

    // String test1;
    // String test2;

    // std::ifstream input("String.bin", std::ios::binary);

    // String::readFromBin(input, test2);
    // String::readFromBin(input, test1);

    // input.close();

    // std::cout << test1 << std::endl;
    // std::cout << test2 << std::endl;

    // std::cout << (myStr != test1) << std::endl;
    // std::cout << myStr << " " << test1 << std::endl;
// }