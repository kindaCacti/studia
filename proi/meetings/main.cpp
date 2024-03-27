#include <iostream>
#include <string>
#include "meeting.h"

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
    int meetingType = std::stoi(argv[6]);
    
    m.setTime(year, month, day, hour, minute);
    m.setMeetingType(meetingType);

    for(int i = 7; i<argc; i+=2){
        if(i + 1 == argc){
            m.addParticipant(argv[i]);
            continue;
        }
        else{
            m.addParticipant(argv[i], argv[i+1]);
        }
    }

    std::cout<<m.parseToString();
}