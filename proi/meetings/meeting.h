#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "datetime.h"
#include "person.h"

enum MeetingType{
    NO_MEETING_TYPE_SET,
    Board_Meeting,
    Client_Meeting,
    Team_Meeting,
    Information_Meeting
};

class Meeting{
    static int ids;
    int id;
    Datetime date;
    std::vector<Person> participants;
    std::string place;
    MeetingType meetingType;

    void print(std::ostream&, std::string);

    void moveToEndOfParticipants(Person);

    public:
        Meeting();
        void setTime(const int, const int, const int, const int, const int);
        Datetime getTime();

        void addParticipant(std::string, std::string="");
        void addParticipant(Person& p);
        void removeParticipant(Person);
        std::vector<Person> getParticipants();

        void setPlace(std::string);
        std::string getPlace();

        void setMeetingType(int);
        std::string getMeetingType();

        std::string parseToString();

        int participantCount();
        int findParticipant(Person p);
};
