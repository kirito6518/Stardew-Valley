#include "EventManager.h"
#include "SeasonManager.h"

EventManager::EventManager() {
    // 初始化节日
    addEvent(1, "- the Spring Festival -", "庆祝新年", 0 /* Winter 15 */, 6 /* Spring 7 */);
    addEvent(2, "- the Labor Day -", "庆祝劳动", 15 /* Summer 1 */, 20 /* Summer 5 */);
    addEvent(3, "- the Mid-autumn Festival -", "庆祝中秋", 34 /* Autumn 5 */, 41 /* Autumn 12 */);
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
        // 假设季节的顺序是 Spring(0), Summer(1), Autumn(2), Winter(3)
        int seasonOffset = currentSeason * SeasonManager::DAYS_PER_SEASON;
        int totalDays = seasonOffset + daysInCurrentSeason;

        if (totalDays >= event.startTime && totalDays <= event.endTime) {
            return event.name;
        }
    }
    return "";
}