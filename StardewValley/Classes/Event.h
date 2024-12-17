#pragma once
#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event {
public:
    Event(int id, const std::string& name, const std::string& description, int startTime, int endTime);
    ~Event();

    int getId() const;
    std::string getName() const;
    std::string getDescription() const;
    int getStartTime() const;
    int getEndTime() const;

private:
    int _id;
    std::string _name;
    std::string _description;
    int _startTime;
    int _endTime;
};

#endif // EVENT_H