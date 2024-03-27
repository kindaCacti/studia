#include "datetime.h"
#include "exceptions.h"
#include <string>

Datetime::Datetime(){
    setTime(1, 1, 1, 1, 1);
}

Datetime::Datetime(int _year, int _month, int _day, int _hour, int _minute){
    setTime(_year, _month, _day, _hour, _minute);
}

void Datetime::setTime(int _year, int _month, int _day, int _hour, int _minute){
    try{
        if(_month < 1) throw IncorrectDate("Incorrect month value, month should be between 1 and 12");
        if(_month > 12) throw IncorrectDate("Incorrect month value, month should be between 1 and 12");
        switch(_month){
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if(_day < 1) throw IncorrectDate("Incorrect day value, day should be between 1 and 31");
                if(_day > 31) throw IncorrectDate("Incorrect day value, day should be between 1 and 31"); 
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                if(_day < 1) throw IncorrectDate("Incorrect day value, day should be between 1 and 30");
                if(_day > 30) throw IncorrectDate("Incorrect day value, day should be between 1 and 30");
                break;
            case 2:
                if(_day < 1) throw IncorrectDate("Incorrect day value, day should be between 1 and 28");
                if(_day > 30) throw IncorrectDate("Incorrect day value, day should be between 1 and 28");
                break;
        }
        if(_hour < 0 and _hour > 23) throw IncorrectDate("Incorrect hour value, hour should be between 0 and 23");
        if(_minute < 0 and _minute > 59) throw IncorrectDate("Incorrect minute value, minute should be between 0 and 59");
    }catch (IncorrectDate ind){
        ind.write();
        return;
    }
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
    std::string out = "";
    if(day<10) out += "0";
    out += std::to_string(day);
    out += ".";
    if(month<10) out += "0";
    out += std::to_string(month);
    out += ".";
    out += std::to_string(year);
    out += " ";
    out += std::to_string(hour);
    out += ":";
    if(minute<10) out += "0";
    out += std::to_string(minute);
    return out;
}

inline bool Datetime::operator== (Datetime& dt){
    if(dt.getYear() != year) return false;
    if(dt.getMonth() != month) return false;
    if(dt.getDay() != day) return false;
    if(dt.getHour() != hour) return false;
    if(dt.getMinute() != minute) return false;
    return true;
}