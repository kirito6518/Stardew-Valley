#pragma once
#ifndef EventManager_H
#define EventManager_H

#include <string>
#include <vector>

class EventManager {
public:
    EventManager();
    ~EventManager();

    // ��ӽ���
    void addEvent(int id, const std::string& name, const std::string& description, int startTime, int endTime);

    // ��鵱ǰ�Ƿ��н��գ������ؽ�����Ϣ
    std::string getCurrentEvent(int currentSeason, int daysInCurrentSeason) const;

    // �麯������������������ӽ����¼�
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