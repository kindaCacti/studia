#include "entry.h"
#include <stdexcept>

Entry::Entry(std::string _word, int _occurrences = 1){
    word = _word;
    occurrences = _occurrences;
}

bool Entry::isWordEqual(std::string& lWord){
    return word == lWord;
}

bool Entry::isWordBigger(std::string& lWord){
    return word > lWord;
}

bool Entry::isWordBigger(Entry& lWord){
    return word > lWord.getWord();
}

void Entry::addOccurrence(int ammount = 1){
    occurrences += ammount;
}

void Entry::removeOccurrence(int ammount = 1){
    if(ammount > occurrences) 
        throw std::invalid_argument("tried to remove more occurrences than possible");
    occurrences -= ammount;
}

int Entry::getOccurrences() const{
    return occurrences;
}

std::string Entry::getWord() const{
    return std::string(word);
}

std::string Entry::stringify() const{
    std::string out = "";
    out +="{ word: " + word + ", occurrences: " + std::to_string(occurrences) + " }";
    return out;
}

void Entry::operator+=(int add){
    addOccurrence(add);
}

void Entry::operator-=(int rem){
    removeOccurrence(rem);
}

Entry& Entry::operator++(){
    (*this)+=1;
    return *this;
}

Entry& Entry::operator--(){
    (*this)-=1;
    return *this;
}

std::ostream& operator<<(std::ostream& os, Entry en){
    os << en.stringify();
    return os;
}