#pragma once
#ifndef EventManager_H
#define EventManager_H

#include <string>
#include <vector>

class EventManager {
public:
    EventManager();
    ~EventManager();

    // 添加节日
    void addEvent(int id, const std::string& name, const std::string& description, int startTime, int endTime);

    // 检查当前是否有节日，并返回节日信息
    std::string getCurrentEvent(int currentSeason, int daysInCurrentSeason) const;

    // 虚函数，供子类重载以添加节日事件
    virtual void onEventTrigger(int eventId) {}

private:
    struct Event {
        int id;
        std::string name;
        std::string description;
        int startTime;
        int endTime;
    };

    std::vector<Event> events;
};

#endif // EventManager_H