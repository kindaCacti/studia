#pragma once
#include <iostream>
#include <string>
#include "meeting.h"
#include "person.h"
#include "datetime.h"

int main(int argc, char* argv[]){
    if(argc == 1){
        std::cout<<"The usage of this app is ./meetings.exe [year] [month] [day] [hour] [minute] [meeting_type] [participants...]\n";
        return 0;
    }

    if(argc < 7){
        std::cout<<"Too few arguments\n";
        return 0;
    }

    Meeting m;

    int year = std::stoi(argv[1]);
    int month = std::stoi(argv[2]);
    int day = std::stoi(argv[3]);
    int hour = std::stoi(argv[4]);
    int minute = std::stoi(argv[5]);
    std::string meetingType = argv[6];
    
    m.setTime(year, month, day, hour, minute);
    std::cout<<"hi\n";
    m.setMeetingType(meetingType);
    std::cout<<"hi\n";
    for(int i = 7; i<argc; i+=2){
        if(i + 1 == argc){
            Person p(argv[i]);
            m.addParticipant(p);
            continue;
        }
        else{
            Person p(argv[i], argv[i+1]);
            m.addParticipant(p);
        }
    }

    std::cout<<"hi\n";
    std::cout<<m.parseToString();
}