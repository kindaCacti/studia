#pragma once
#include <string>

class Datetime{
    int year;
    int month;
    int day;
    int hour;
    int minute;

    bool isCorrectType(int, int, int, int, int);

    public:
        Datetime();
        Datetime(int, int, int, int, int);
        void setTime(int, int, int, int, int);
        int getYear();
        int getMonth();
        int getDay();
        int getHour();
        int getMinute();
        std::string parseToString();
};