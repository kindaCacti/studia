#pragma once
#include <string>

class Person{
    static int ids; //automatically initialized with 0, because it's a static variable
    int id;
    std::string name;
    std::string surname;

    public:
        Person(std::string, std::string);
        Person(std::string);
        int getId();
        bool isEqualTo(Person);
        std::string parseToString();
};