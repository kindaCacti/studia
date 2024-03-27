#include <gtest/gtest.h>
#include <string>
#include "meeting.h"
#include "person.h"
#include "datetime.h"
#include "exceptions.h"

TEST( person_init, person_init )
{
    Person p("Adam", "Sandler");
    ASSERT_EQ(p.getName(), "Adam");
    ASSERT_EQ(p.getSurname(), "Sandler");
}

TEST( person_init_multiple, person_init_multiple )
{
    Person p1("Adam", "Sandler");
    Person p2("Adam", "Sandler2");
    ASSERT_EQ(p1.getName(), "Adam");
    ASSERT_EQ(p1.getSurname(), "Sandler");
    ASSERT_EQ(p2.getName(), "Adam");
    ASSERT_EQ(p2.getSurname(), "Sandler2");
}

TEST( compare_persons, compare_persons){
    Person p1("Adam", "Sandler");
    Person p2("Adam", "Sandler2");
    ASSERT_EQ(p1.isEqualTo(p2), false);
    ASSERT_EQ(p2.isEqualTo(p1), false);
    ASSERT_EQ(p1.isEqualTo(p1), true);
    ASSERT_EQ(p2.isEqualTo(p2), true);
}

TEST( person_stringification, person_stringification){
    Person p1("Adam", "Sandler");
    ASSERT_EQ(p1.parseToString(), std::string("Adam Sandler"));
}

TEST( datetime_empty_init, datetime_empty_init){
    Datetime dt;
    ASSERT_EQ(dt.getYear(), 1);
    ASSERT_EQ(dt.getMonth(), 1);
    ASSERT_EQ(dt.getDay(), 1);
    ASSERT_EQ(dt.getHour(), 1);
    ASSERT_EQ(dt.getMinute(), 1);
}

TEST( datetime_init, datetime_init){
    Datetime dt(2004, 9, 16, 12, 0);
    ASSERT_EQ(dt.getYear(), 2004);
    ASSERT_EQ(dt.getMonth(), 9);
    ASSERT_EQ(dt.getDay(), 16);
    ASSERT_EQ(dt.getHour(), 12);
    ASSERT_EQ(dt.getMinute(), 0);
}

TEST (datetime_set_time, datetime_set_time){
    Datetime dt;
    dt.setTime(2003, 10, 10, 10, 10);
    ASSERT_EQ(dt.getYear(), 2003);
    ASSERT_EQ(dt.getMonth(), 10);
    ASSERT_EQ(dt.getDay(), 10);
    ASSERT_EQ(dt.getHour(), 10);
    ASSERT_EQ(dt.getMinute(), 10);
}

TEST( datetime_stringification, datetime_stringification){
    Datetime dt;
    dt.setTime(2003, 9, 10, 10, 10);
    ASSERT_EQ(dt.parseToString(), "10.09.2003 10:10");
}

TEST( datetime_stringification_no_fill, datetime_stringification_no_fill){
    Datetime dt;
    dt.setTime(2003, 10, 10, 10, 10);
    ASSERT_EQ(dt.parseToString(), "10.10.2003 10:10");
}

TEST( meeting_init, meeting_init ){
    Meeting mt;
    ASSERT_EQ(mt.getMeetingType(), "unset");
    ASSERT_EQ(mt.getParticipants().size(), 0);
    ASSERT_EQ(mt.getPlace().size(), 0);
}

TEST( meeting_add_participant, meeting_add_participant){
    Meeting mt;
    mt.addParticipant("Adam", "Sandler");
    ASSERT_EQ(mt.getParticipants().size(), 1);
    ASSERT_EQ(mt.getParticipants().back().getName(), "Adam");
    ASSERT_EQ(mt.getParticipants().back().getSurname(), "Sandler");
}

TEST( meeting_get_participants, meeting_get_participants ){
    Meeting mt;
    mt.addParticipant("Adam", "Sandler");
    mt.addParticipant("Adam", "Sandler2");
    ASSERT_EQ(mt.getParticipants()[0].getSurname(), "Sandler");
    ASSERT_EQ(mt.getParticipants()[1].getSurname(), "Sandler2");
}

TEST( meeting_remove_participant, meeting_remove_participant){
    Meeting mt;
    mt.addParticipant("Adam", "Sandler");
    mt.addParticipant("Adam", "Sandler2");
    mt.addParticipant("Adam", "Sandler3");
    mt.addParticipant("Adam", "Sandler4");
    mt.removeParticipant(mt.getParticipants()[1]);
    ASSERT_EQ(mt.getParticipants().size(), 3);
    ASSERT_EQ(mt.getParticipants()[0].getSurname(), "Sandler");
    ASSERT_EQ(mt.getParticipants()[1].getSurname(), "Sandler3");
    ASSERT_EQ(mt.getParticipants()[2].getSurname(), "Sandler4");
}

TEST( meeting_remove_non_existant_participant, meeting_remove_non_existant_participant){
    Meeting mt;
    mt.addParticipant("Adam", "Sandler");
    mt.addParticipant("Adam", "Sandler2");
    mt.addParticipant("Adam", "Sandler3");
    mt.addParticipant("Adam", "Sandler4");
    Person pr("Adam", "Sandler5");
    mt.removeParticipant(pr);
    ASSERT_EQ(mt.getParticipants().size(), 4);
    ASSERT_EQ(mt.getParticipants()[0].getSurname(), "Sandler");
    ASSERT_EQ(mt.getParticipants()[1].getSurname(), "Sandler2");
    ASSERT_EQ(mt.getParticipants()[2].getSurname(), "Sandler3");
    ASSERT_EQ(mt.getParticipants()[3].getSurname(), "Sandler4");
}

TEST( meeting_set_time, meeting_set_time ){
    Meeting mt;
    mt.setTime(100, 2, 2, 2, 2);
    ASSERT_EQ(mt.getTime().getYear(), 100);
    ASSERT_EQ(mt.getTime().getMonth(), 2);
    ASSERT_EQ(mt.getTime().getDay(), 2);
    ASSERT_EQ(mt.getTime().getHour(), 2);
    ASSERT_EQ(mt.getTime().getMinute(), 2);
}

TEST( meeting_set_place, meeting_set_place ){
    Meeting mt;
    mt.setPlace("PW");
    ASSERT_EQ(mt.getPlace(), "PW");
}

TEST( meeting_find_person, meeting_find_person ){
    Meeting mt;
    Person pt1("Adam Sandler1");
    Person pt2("Adam Sandler2");
    Person pt3("Adam Sandler3");
    mt.addParticipant(pt1);
    mt.addParticipant(pt2);
    ASSERT_EQ(mt.findParticipant(pt1), 0);
    ASSERT_EQ(mt.findParticipant(pt2), 1);
    ASSERT_EQ(mt.findParticipant(pt3), -1);

}

TEST( set_meeting_type, set_meeting_type ){
    Meeting mt;
    mt.setMeetingType(2);
    ASSERT_EQ(mt.getMeetingType(), "Client Meeting");
}

TEST( datetime_exception_test, datetime_exception_test )
{
    // this tests _that_ the expected exception is thrown
    EXPECT_THROW({
        try
        {
            Datetime dt(0,0,0,0,0);
        }
        catch( const IncorrectDate& e )
        {
            throw;
        }
    }, IncorrectDate );
}

TEST( datetime_exception_test_month, datetime_exception_test_month )
{
    // this tests _that_ the expected exception is thrown
    EXPECT_THROW({
        try
        {
            Datetime dt(0,13,1,0,0);
        }
        catch( const IncorrectDate& e )
        {
            throw;
        }
    }, IncorrectDate );
}

TEST( datetime_exception_test_day, datetime_exception_test_day )
{
    // this tests _that_ the expected exception is thrown
    EXPECT_THROW({
        try
        {
            Datetime dt(0,10,32,0,0);
        }
        catch( const IncorrectDate& e )
        {
            throw;
        }
    }, IncorrectDate );
}