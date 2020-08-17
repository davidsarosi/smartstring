#ifndef CPP_HF_MYSTRING_H
#define CPP_HF_MYSTRING_H


#include <cstring>
#include <ostream>

class MyString {
    char *string;
    int *refcount_;

    void decrement();
    void increment();

public:
    MyString(const char *rhs = nullptr);
    MyString(MyString const &other_ptr) : string{other_ptr.string}, refcount_{other_ptr.refcount_} {
        ++*refcount_;
    }
    MyString(MyString &&other) noexcept : string{other.string}, refcount_{other.refcount_} {
        ++*refcount_;
    }

    MyString &operator=(const char *rhs);
    MyString &operator=(MyString const &);
    MyString &operator=(MyString &&) noexcept;

    const char &operator*(MyString const &s) { return *string; }
    const char *operator->() const { return string; };
    const char &operator[](int) const;
    char &operator[](int);


    MyString &operator+=(char const &);
    MyString &operator+=(MyString const &);
    friend MyString operator+(MyString const &lhs, char const &rhs);
    friend MyString operator+(MyString const &lhs, MyString const &rhs);

    friend std::ostream &operator<<(std::ostream &os, const MyString &string);
    friend std::istream &operator>>(std::istream &, MyString &);

    size_t len();

    ~MyString();
};

#endif