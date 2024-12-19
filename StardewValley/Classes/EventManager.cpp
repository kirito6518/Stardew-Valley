#include "EventManager.h"
#include "SeasonManager.h"

EventManager::EventManager() {
    // ��ʼ������
    addEvent(1, "- the Spring Festival -", "��ף����", 0 /* Winter 15 */, 6 /* Spring 7 */);
    addEvent(2, "- the Labor Day -", "��ף�Ͷ�", 15 /* Summer 1 */, 20 /* Summer 5 */);
    addEvent(3, "- the Mid-autumn Festival -", "��ף����", 34 /* Autumn 5 */, 41 /* Autumn 12 */);
}

EventManager::~EventManager() {}

void EventManager::addEvent(int id, const std::string& name, const std::string& description, int startTime, int endTime) {
    Event event;
    event.id = id;
    event.name = name;
    event.description = description;
    event.startTime = startTime;
    event.endTime = endTime;
    events.push_back(event);
}

std::string EventManager::getCurrentEvent(int currentSeason, int daysInCurrentSeason) const {
    for (const auto& event : events) {
        // ���輾�ڵ�˳���� Spring(0), Summer(1), Autumn(2), Winter(3)
        int seasonOffset = currentSeason * SeasonManager::DAYS_PER_SEASON;
        int totalDays = seasonOffset + daysInCurrentSeason;

        if (totalDays >= event.startTime && totalDays <= event.endTime) {
            return event.name;
        }
    }
    return "";
}