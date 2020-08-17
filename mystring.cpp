#include <iostream>
#include "mystring.h"

//********************************************
//Constructor
//********************************************
MyString::MyString(const char *rhs) {

    if (rhs) {
        string = new char[strlen(rhs) + 1];
        strcpy(string, rhs);
        refcount_ = new int{1};
    } else {
        string = nullptr;
        refcount_ = nullptr;
    }


}

//********************************************
//operator overload =
//********************************************
MyString &MyString::operator=(const MyString &rhs) {
    if (&rhs == this)
        return *this;
    decrement();
    string = rhs.string;
    refcount_ = rhs.refcount_;
    if (rhs.string)
        increment();
    return *this;
}

MyString &MyString::operator=(const char *rhs) {
    if (string && rhs) {
        if (strcmp(string, rhs) == 0)
            return *this;
    }
    decrement();
    string = new char[strlen(rhs) + 1];
    strcpy(string, rhs);
    refcount_ = new int{1};
    return *this;
}

MyString &MyString::operator=(MyString &&rhs) noexcept {

    if (rhs.string) {
        decrement();
        string = rhs.string;
        refcount_ = rhs.refcount_;
        rhs.string = nullptr;
        rhs.refcount_ = nullptr;
    } else {
        decrement();
        string = nullptr;
        refcount_ = nullptr;
    }
    return *this;
}

//********************************************
//index operator overload
//********************************************
const char &MyString::operator[](int i) const {
    if (i < 0 || static_cast<size_t >(i) > strlen(string)) {
        throw std::out_of_range("out of bounds");
    }

    return string[i];
}

char &MyString::operator[](int i) {
    if (i < 0 || static_cast<size_t >(i) > strlen(string)) {
        throw std::out_of_range("out of bounds");
    }

    auto temp = new char[strlen(string) + 1];
    strcpy(temp, string);
    decrement();
    string = temp;
    refcount_ = new int(1);

    return (char &) string[i];
}

//********************************************
// + and += operator overloads
//********************************************

MyString operator+(MyString const &lhs, MyString const &rhs) {
    size_t len = strlen(lhs.string) + strlen(rhs.string);
    char* temp_string=new char[len + 1];
    strcpy(temp_string, lhs.string);
    strcat(temp_string, rhs.string);
    temp_string[len] = '\0';
    MyString temp=MyString(temp_string);
    delete [] temp_string;
    return temp;
}

MyString operator+(MyString const &lhs, char const &rhs) {
    size_t len = strlen(lhs.string) + 1;
    char* temp_string=new char[len + 1];
    strcpy(temp_string, lhs.string);
    temp_string[len - 1] = rhs;
    temp_string[len] = '\0';

    MyString temp=MyString(temp_string);
    delete [] temp_string;

    return temp;
}

MyString &MyString::operator+=(MyString const &rhs) {

    MyString temp = MyString(string) + rhs;
    decrement();
    *this = temp;
    return *this;
}

MyString &MyString::operator+=(char const &rhs) {


    MyString temp = MyString(string) + rhs;
    decrement();
    *this = temp;
    return *this;
}

//********************************************
// cout and cin overloads
//********************************************
std::ostream &operator<<(std::ostream &os, const MyString &string) {
    os << string.string;
    return os;
}

std::istream &operator>>(std::istream &is, MyString &myString) {
    char c;
    if (myString.string)
        myString.decrement();
    myString = MyString("");
    while (std::cin.get(c) && c != '\n') {
        myString += c;
    }
    return is;

}

//********************************************
// member functions
//********************************************
void MyString::decrement() {
    if (string && --*refcount_ == 0) {
        delete refcount_;
        delete[] string;
        string = nullptr;
        refcount_ = nullptr;
    }
}


void
MyString::increment() {  //igazából felesleges külön függvénybe szervezni, de ha van decrement akkor hogy konzisztens legyen létrehoztam egy incrementet is
    (*refcount_)++;
}

size_t MyString::len() {
    return strlen(string);
}

//********************************************
// destructor
//********************************************
MyString::~MyString() {
    if (string && refcount_)
        decrement();
}

