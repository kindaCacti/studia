#include <gtest/gtest.h>
#include "entry.h"
#include "counter.h"

TEST(ENTRY, CREATE_ENTRY){
    Entry e = Entry("hello", 10);
    ASSERT_EQ(e.getWord(), std::string("hello"));
    ASSERT_EQ(e.getOccurrences(), 10);
}

TEST(ENTRY, ADD_OCCURRENCE){
    Entry e = Entry("hello", 10);
    ASSERT_EQ(e.getOccurrences(), 10);
    e.addOccurrence(1);
    ASSERT_EQ(e.getOccurrences(), 11);
    e.addOccurrence(5);
    ASSERT_EQ(e.getOccurrences(), 16);
    e.addOccurrence(100);
    ASSERT_EQ(e.getOccurrences(), 116);
}

TEST(ENTRY, REMOVE_OCCURRENCE){
    Entry e = Entry("hello", 10);
    ASSERT_EQ(e.getOccurrences(), 10);
    e.removeOccurrence(1);
    ASSERT_EQ(e.getOccurrences(), 9);
    e.removeOccurrence(5);
    ASSERT_EQ(e.getOccurrences(), 4);
}

TEST(ENTRY, COMPARE_WORDS){
    Entry e = Entry("hello", 10);
    std::string w1 = "aaa";
    std::string w2 = "hello";
    std::string w3 = "zzzz";
    ASSERT_EQ(e.isWordEqual(w2), true);
    ASSERT_EQ(e.isWordEqual(w1), false);
    ASSERT_EQ(e.isWordBigger(w1), true);
    ASSERT_EQ(e.isWordBigger(w2), false);
    ASSERT_EQ(e.isWordBigger(w3), false);
}

TEST(ENTRY, COMPARE_ENTRIES){
    Entry e1 = Entry("hello", 10);
    Entry e2 = Entry("aaa", 10);
    Entry e3 = Entry("zzz", 10);
    ASSERT_EQ(e1.isWordBigger(e2), true);
    ASSERT_EQ(e1.isWordBigger(e1), false);
    ASSERT_EQ(e1.isWordBigger(e3), false);
}

TEST(ENTRY, STRINGIFY){
    Entry e = Entry("hello", 10);
    ASSERT_EQ(e.stringify(), std::string("{ word: hello, occurrences: 10 }"));
}

TEST(ENTRY, OPERATORS){
    Entry e = Entry("hello", 10);
    ASSERT_EQ(e.getOccurrences(), 10);
    ++e;
    ASSERT_EQ(e.getOccurrences(), 11);
    --e;
    ASSERT_EQ(e.getOccurrences(), 10);
    e+=10;
    ASSERT_EQ(e.getOccurrences(), 20);
    e-=10;
    ASSERT_EQ(e.getOccurrences(), 10);
}

TEST(COUNTER, ADDING_WORDS){
    Counter c;
    c.addWord("ala", 1);
    c.addWord("ma", 1);
    c.addWord("kota", 1);
    c.addWord("kota", 1);
    ASSERT_EQ(c.numberOfWords(), 3);
}

TEST(COUNTER, REMOVE_WORD){
    Counter c;
    c.addWord("ala", 1);
    c.addWord("ma", 1);
    c.addWord("kota", 1);
    c.addWord("kota", 1);
    std::string wtr = "kota";
    c.removeWord(wtr);
    ASSERT_EQ(c.numberOfWords(), 3);
    c.removeWord(wtr);
    ASSERT_EQ(c.numberOfWords(), 2);
}

TEST(COUNTER, ADD_FROM_COUNTER){
    Counter c, d;
    c.addWord("ala", 1);
    c.addWord("ma", 1);
    c.addWord("kota", 1);
    c.addWord("kota", 1);
    d.addWord("kot", 1);
    d.addWord("ma", 1);
    d.addWord("ale", 1);
    c.addFromCounter(d);
    ASSERT_EQ(c.numberOfWords(), 5);
}

TEST(COUNTER, OPEARTORS){
    Counter c;
    std::string w1 = "ala";
    std::string w2 = "ma";
    std::string w3 = "kota";
    c += w1;
    c += w1;
    c += w2;
    c += w3;

    ASSERT_EQ(c.numberOfWords(), 3);
    c-=w1;
    ASSERT_EQ(c.numberOfWords(), 3);
    c-=w1;
    ASSERT_EQ(c.numberOfWords(), 2);
}

TEST(COUNTER, TEST_ITERATOR){
    Counter c;
    std::string w1 = "ala";
    std::string w2 = "ma";
    std::string w3 = "kota";
    c += w1;
    c += w1;
    c += w2;
    c += w3;

    auto it = c.begin();
    std::string tmp = "";
    while(it != c.end()){
        tmp += (*it).stringify();
        it++;
    }

    ASSERT_EQ(tmp, std::string("{ word: ala, occurrences: 2 }{ word: kota, occurrences: 1 }{ word: ma, occurrences: 1 }"));
}

TEST(COUNTER, TEST_FITERATOR){
    Counter c;
    std::string w1 = "ala";
    std::string w2 = "ma";
    std::string w3 = "kota";
    c += w1;
    c += w1;
    c += w2;
    c += w3;

    auto it = c.fbegin();
    std::string tmp = "";
    while(it != c.fend()){
        tmp += (*it).stringify();
        it++;
    }

    ASSERT_EQ(tmp, std::string("{ word: kota, occurrences: 1 }{ word: ma, occurrences: 1 }{ word: ala, occurrences: 2 }"));
}