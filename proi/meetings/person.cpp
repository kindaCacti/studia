#pragma once
#include <string>
#include "person.h"

int Person::ids = 0;

Person::Person(std::string _name, std::string _surname){
    name = _name;
    surname = _surname;
    id = ++ids;
}

Person::Person(std::string _fullName){
    name = _fullName;
    surname = "";
    id = ++ids;
}

int Person::getId(){
    return id;
}

bool Person::isEqualTo(Person toCompare){
    if(getId() == toCompare.getId()) return true;
    return false;
}

std::string Person::parseToString(){
    std::string out = name;
    out += " ";
    out += surname;
    return out;
}