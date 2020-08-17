#include <iostream>
#include "mystring.h"

int main() {
    MyString a, b;
    a = MyString();
    a = b = "hello vilag";
    std::cout << " a = b = \"hello vilag\";   a=" << a << " b= " << b << std::endl;
    MyString c{a};
    std::cout << "MyString c{a}  a=" << a << " c= " << c << std::endl;
    MyString d;
    d = a;
    d = MyString{"move constructor"};
    std::cout << "d = MyString{\"move constructor\"}  d=" << d << std::endl;
    std::cout << "a[4] = 'a'  előtte=\"" << a<<"\"";
    a[4] = 'a';
    std::cout << " utána= " << a << std::endl;
    std::cout<<" \"a\" megváltozott az előző sorban de \"b\" még mindig változatlan   a=\"" << a <<"\"  "<<"b="<< b<<std::endl;
    MyString x = "hello";
    x[2] = 'c';
    const MyString testconst = MyString("const");
    char test1 = testconst[2];

    MyString y = x+test1;
    y[0] = 'c';
    std::cout<<"x=\"" << x <<"\"  "<<"y="<< y<<std::endl;
    MyString z = x + y + "something";
    std::cout<<"MyString z = x + y + \"something\"   "<<"z="<< z<<std::endl;

    MyString test;
    test = d + "param";
    z += '!';
    x += d;
    d="param";
    std::cout<<"d=\""<<d <<"\"  d.len=" << d.len() << std::endl;
    std::cout<<"cin test, adj meg egy stringet:";
    std::cin >> a;

    std::cout << "a="<< a << std::endl;

}