#pragma once
#include <string>

class Entry{
private:
    std::string word;
    int occurrences;

public:
    Entry(std::string, int);
    bool isWordEqual(std::string&);
    bool isWordBigger(std::string&);
    bool isWordBigger(Entry&);
    void addOccurrence(int);
    void setOccurrences(int occ){occurrences = occ;};
    void removeOccurrence(int);
    int getOccurrences() const;
    std::string getWord() const;
    void setWord(std::string wrd){word = wrd;};
    std::string stringify() const;
    void operator+=(int);
    void operator-=(int);
    Entry& operator++();
    Entry& operator--();
    friend std::ostream& operator<<(std::ostream&, Entry);
};