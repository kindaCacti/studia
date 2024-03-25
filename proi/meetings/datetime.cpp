#pragma once
#include "datetime.h"
#include <string>

Datetime::Datetime(){
    setTime(0, 0, 0, 0, 0);
}

Datetime::Datetime(int _year, int _month, int _day, int _hour, int _minute){
    setTime(_year, _month, _day, _hour, _minute);
}

void Datetime::setTime(int _year, int _month, int _day, int _hour, int _minute){
    year = _year;
    month = _month;
    day = _day;
    hour = _hour;
    minute = _minute;   
}

int Datetime::getYear(){
    return year;
}

int Datetime::getMonth(){
    return month;
}

int Datetime::getDay(){
    return day;
}

int Datetime::getHour(){
    return hour;
}

int Datetime::getMinute(){
    return minute;
}

std::string Datetime::parseToString(){
    std::string out = std::to_string(year);
    out += ".";
    if(month<10) out += "0";
    out += std::to_string(month);
    out += ".";
    if(day<10) out += "0";
    out += std::to_string(day);
    out += " ";
    out += std::to_string(hour);
    out += ":";
    if(minute<10) out += "0";
    out += std::to_string(minute);
    return out;
}