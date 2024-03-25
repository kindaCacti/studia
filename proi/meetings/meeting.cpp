#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "datetime.h"
#include "person.h"
#include "meeting.h"


int Meeting::ids = 0;

Meeting::Meeting(){
    id = ++ids;
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

void Meeting::addParticipant(const Person newParticipant){
    participants.push_back(newParticipant);
}

void Meeting::removeParticipant(Person personToRemove, std::ostream& os){
    moveToEndOfParticipants(personToRemove);

    if(participants.back().isEqualTo(personToRemove)){
        participants.pop_back();
        print(os, "Successfully removed: " + personToRemove.parseToString());
        return;
    }

    print(os, "Person: " + personToRemove.parseToString() + " does not exist");
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

void Meeting::setMeetingType(std::string newMeetingType){
    meetingType = newMeetingType;
}

std::string Meeting::getMeetingType(){
    return meetingType;
}

std::string Meeting::parseToString(){
    std::string out = "\n----------\n\nMEETING ID: ";
    out += std::to_string(id);
    out += "\n\nTime:\n";
    out += date.parseToString();
    out += "\n\nMeeting type:\n";
    out += meetingType;
    out += "\n\nParticipants:\n";

    int n = participants.size();
    for(int i = 0; i<n; i++){
        out+=participants[i].parseToString();
        out+="\n";
    }

    out += "\n\n----------\n";
    return out;
}
