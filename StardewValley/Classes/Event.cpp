#include "Event.h"

Event::Event(int id, const std::string& name, const std::string& description, int startTime, int endTime)
    : _id(id), _name(name), _description(description), _startTime(startTime), _endTime(endTime) {
}

Event::~Event() {}

int Event::getId() const {
    return _id;
}

std::string Event::getName() const {
    return _name;
}

std::string Event::getDescription() const {
    return _description;
}

int Event::getStartTime() const {
    return _startTime;
}

int Event::getEndTime() const {
    return _endTime;
}