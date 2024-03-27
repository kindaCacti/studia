#include <vector>
#include <string>
#include <iostream>
#include "datetime.h"
#include "person.h"
#include "meeting.h"


int Meeting::ids = 0;

Meeting::Meeting(){
    id = ++ids;
    meetingType = NO_MEETING_TYPE_SET;
    date = Datetime();
    place = "";
}

void Meeting::print(std::ostream& os, std::string data){
    os << data << std::endl;
}

void Meeting::moveToEndOfParticipants(Person personToMove){
    int it = 0;
    int n = participants.size();
    for(; it < n-1; it++){
        if(participants[it].isEqualTo(personToMove)){
            std::swap(participants[it], participants[it + 1]);
        }
    }
}

void Meeting::setTime(int year, int month, int day, int hour, int minute){
    date = Datetime(year, month, day, hour, minute);
}

Datetime Meeting::getTime(){
    return date;
}

void Meeting::addParticipant(std::string name, std::string surname){
    participants.push_back(Person(name, surname));
}

void Meeting::removeParticipant(Person personToRemove){
    moveToEndOfParticipants(personToRemove);

    if(participants.back().isEqualTo(personToRemove)){
        participants.pop_back();
    }
}

std::vector<Person> Meeting::getParticipants(){
    return participants;
}

void Meeting::setPlace(std::string newPlace){
    place = newPlace;
}

std::string Meeting::getPlace(){
    return place;
}

void Meeting::setMeetingType(int newMeetingType){
    switch(newMeetingType){
        case 1:
            meetingType = Board_Meeting;
            break;
        case 2:
            meetingType = Client_Meeting;
            break;
        case 3:
            meetingType = Team_Meeting;
            break;
        case 4:
            meetingType = Information_Meeting;
            break;
        default:
            meetingType = NO_MEETING_TYPE_SET;
            break;
    }
}

std::string Meeting::getMeetingType(){
    switch(meetingType){
        case(NO_MEETING_TYPE_SET):
            return "unset";
        case(Board_Meeting):
            return "Board Meeting";
        case(Client_Meeting):
            return "Client Meeting";
        case(Team_Meeting):
            return "Team Meeting";
        case(Information_Meeting):
            return "Information Meeting";
    }
    return "error";
}

std::string Meeting::parseToString(){
    std::string out = "\n----------\n\nMEETING ID: ";
    out += std::to_string(id);
    out += "\n\nTime:\n";
    out += date.parseToString();
    out += "\n\nMeeting type:\n";
    out += getMeetingType();
    out += "\n\nParticipants:\n";

    int n = participants.size();
    for(int i = 0; i<n; i++){
        out+=participants[i].parseToString();
        out+="\n";
    }

    out += "\n\n----------\n";
    return out;
}
