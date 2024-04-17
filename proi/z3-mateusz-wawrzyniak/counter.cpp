#include "counter.h"
#include <iostream>

int Counter::idInEntries(std::string& word){
    if(entries.size() == 0) return -1;

    int lowerBound = 0;
    int upperBound = entries.size() - 1;
    int middle;

    while(lowerBound < upperBound){
        middle = (lowerBound + upperBound) / 2 + 1;
        if(entries[middle].isWordBigger(word)){
            upperBound = middle - 1;
        }else{
            lowerBound = middle;
        }
    }

    if(entries[lowerBound].isWordEqual(word)){
        return lowerBound;
    }
    return -1;
}

void Counter::insertIntoPlace(std::string word){
    entries.push_back(Entry(word, 1));
    for(int i = entries.size()-2; i>=0; i--){
        if(entries[i+1].isWordBigger(entries[i])) break;
        std::swap(entries[i], entries[i+1]);
    }
}

void Counter::moveEntryBack(int tmp){
    for(int i = tmp+1; i <= entries.size(); i++){
        std::swap(entries[tmp], entries[tmp+1]);
    }
}

void Counter::addWord(std::string word, int ammount){
    int tmp = idInEntries(word);

    if(tmp == -1){
        words++;
        insertIntoPlace(word);
        return;
    }

    entries[tmp]+=ammount;
}

void Counter::operator+=(std::string& str){
    addWord(str, 1);
}

void Counter::operator-=(std::string& str){
    removeWord(str);
}

std::istream& operator>>(std::istream& st, Counter& cnt){
    std::string tmp;
    st >> tmp;
    cnt += tmp;
    return st;
}

std::ostream& operator<<(std::ostream& st, Counter& cnt){
    st << cnt.stringify();
    return st;
}

void Counter::removeWord(std::string& word){
    int tmp = idInEntries(word);

    if(tmp==-1) return;

    --entries[tmp];
    if(entries[tmp].getOccurrences() > 0) return;

    words--;
    moveEntryBack(tmp);
    entries.pop_back();
}

void Counter::addFromCounter(Counter& second){
    std::vector<Entry> tmp = second.getEntries();
    for(int i = 0; i<tmp.size(); i++){
        addWord(tmp[i].getWord(), tmp[i].getOccurrences());
    }
}

std::vector<Entry> Counter::getEntries(){
    return entries;
}

std::string Counter::stringify(){
    std::string out = "{ ";
    for(int i = 0; i<entries.size(); i++){
        out += entries[i].stringify();
        out += " ";
    }
    out += "}\n";
    return out;
}

int Counter::bestId(int a, int b, int bt, int mul){
    if(b == -1) return -1;
    if(b == a) return a;
    if(b == bt) return a;

    if(entries[b].getOccurrences() * mul < entries[bt].getOccurrences() * mul) return a;

    if(a == -1){
        if(b < bt){
            if(entries[b].getOccurrences() * mul > entries[bt].getOccurrences() * mul){
                return b;
            }
        }else{
            if(entries[b].getOccurrences() * mul >= entries[bt].getOccurrences() * mul){
                return b;
            }
        }
        return a;
    }

    // here a and b is not equal to -1

    if(entries[b].getOccurrences() * mul < entries[a].getOccurrences() * mul) return b;

    return a;
}

int Counter::getOnEdge(int mul){
    int out = -1;
    int n = entries.size();
    for(int i = 0; i<n; i++){
        if(out == -1){
            out = i;
            continue;
        }
        if(entries[out].getOccurrences() * mul> entries[i].getOccurrences() * mul) out = i;
    }

    return out;
}

std::vector<Entry>::const_iterator Counter::fiterator::nextSmallest(){
    iterator tmp = iterator(st);
    iterator end = iterator(cnt_end);
    iterator st = iterator(it);

    bool before = true;
    iterator out = iterator(it);
    while(tmp != end){
        if((*tmp).getWord() == (*it).getWord()){
            before = false;
            tmp++;
            continue;
        }

        int cval = (*tmp).getOccurrences() * mul;
        int bval = (*out).getOccurrences() * mul;
        int sval = (*st).getOccurrences() * mul;
        if(cval < sval or (before and cval == sval)){
            tmp++;
            continue;
        }
        if(!(out != st)){
            out.setIt(tmp.getIt());
        }
        else if(before){
            if(cval < bval){
                out.setIt(tmp.getIt());
            }
        }else{
            if(out != st){
                if(cval < bval){
                    out.setIt(tmp.getIt());
                }
            }else{
                if(cval <= bval){
                    out.setIt(tmp.getIt());
                }
            }
        }
        tmp++;
    }
    if(out.getIt() == st.getIt()){
        return cnt_end;
    }
    return out.getIt();
}

Counter::iterator Counter::begin(){
    return iterator(entries.begin());
}

Counter::iterator Counter::end(){
    return iterator(entries.end());
}

Counter::iterator Counter::iterator::operator++(int a){
    auto tmp = iterator(it);
    it++;
    return tmp;
}

Counter::iterator& Counter::iterator::operator++(){
    ++it;
    return (*this);
}

bool Counter::iterator::operator!=(iterator wcit){
    return it != wcit.getIt();
}

Counter::fiterator Counter::fbegin(){
    return fiterator(entries.begin() + getOnEdge(1), entries.end(), entries.begin());
}

Counter::fiterator Counter::frend(){
    return fiterator(entries.end(), entries.end(), entries.begin(), -1);
}
Counter::fiterator Counter::frbegin(){
    return fiterator(entries.begin() + getOnEdge(-1), entries.end(), entries.begin(), -1);
}

Counter::fiterator Counter::fend(){
    return fiterator(entries.end(), entries.end(), entries.begin());
}

Counter::fiterator Counter::fiterator::operator++(int a){
    auto tmp = fiterator(it, cnt_end, st);
    it = nextSmallest();
    return tmp;
}

Counter::fiterator& Counter::fiterator::operator++(){
    auto tmp = fiterator(it, cnt_end, st);
    it = nextSmallest();
    return (*this);
}