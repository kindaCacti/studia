#pragma once
#include <string>
#include <vector>
#include "entry.h"

class Counter{
private:
    std::vector<Entry> entries;
    int words;
    int idInEntries(std::string&);
    void moveEntryBack(int tmp);
    void insertIntoPlace(std::string);
    int bestId(int, int, int, int);
    int getOnEdge(int);
public:

     class iterator
    {
        std::vector<Entry>::const_iterator it;
    public:
        iterator(std::vector<Entry>::const_iterator vit) : it(vit)
        {
        }

        iterator operator++(int);
        iterator& operator++();
        std::vector<Entry>::const_iterator getIt(){return it;};
        void setIt(std::vector<Entry>::const_iterator _it){it = _it;};
        const Entry& operator*(){return *it;};
        bool operator!=(iterator wcit);
    };

    class fiterator
    {
        std::vector<Entry>::const_iterator it;
        std::vector<Entry>::const_iterator cnt_end;
        std::vector<Entry>::const_iterator st;
        int mul;
    public:
        fiterator(std::vector<Entry>::const_iterator vit,
                std::vector<Entry>::const_iterator vcnt_end, std::vector<Entry>::const_iterator vst, int vmul = 1) : it(vit), cnt_end(vcnt_end), st(vst), mul(vmul)
        {
        }

        fiterator operator++(int);
        fiterator& operator++();
        std::vector<Entry>::const_iterator getIt(){return it;};
        std::vector<Entry>::const_iterator getItEnd(){return cnt_end;};
        std::vector<Entry>::const_iterator getItSt(){return st;};
        const Entry operator*(){return *it;};
        bool operator!=(fiterator wcit){return wcit.getIt() != it;};
        std::vector<Entry>::const_iterator nextSmallest();
    };
    Counter(){words=0;}

    void addWord(std::string, int);
    void removeWord(std::string&);
    void addFromCounter(Counter&);
    int numberOfWords(){return words;};
    std::vector<Entry> getEntries();
    std::string stringify();
    void operator+=(std::string&);
    void operator-=(std::string&);
    friend std::istream& operator>>(std::istream&, Counter&);
    friend std::ostream& operator<<(std::ostream&, Counter&);
    iterator begin();
    iterator end();
    fiterator fbegin();
    fiterator fend();
    fiterator frbegin();
    fiterator frend();
};