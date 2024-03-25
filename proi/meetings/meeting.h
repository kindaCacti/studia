#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "datetime.h"
#include "person.h"

class Meeting{
    static int ids;
    int id;
    Datetime date;
    std::vector<Person> participants;
    std::string place;
    std::string meetingType;

    void print(std::ostream&, std::string);

    void moveToEndOfParticipants(Person);

    public:
        Meeting();
        void setTime(const int, const int, const int, const int, const int);
        Datetime getTime();

        void addParticipant(Person);
        void removeParticipant(Person, std::ostream&);
        std::vector<Person> getParticipants();

        void setPlace(std::string);
        std::string getPlace();

        void setMeetingType(std::string);
        std::string getMeetingType();

        std::string parseToString();
};
