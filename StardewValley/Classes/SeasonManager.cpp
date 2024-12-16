#include "SeasonManager.h"

// 构造函数，初始化季节管理器
SeasonManager::SeasonManager() : currentSeason(Spring), daysInCurrentSeason(0) {}

// 更新季节
void SeasonManager::updateSeason(int days) {
    daysInCurrentSeason += days;
    if (daysInCurrentSeason >= DAYS_PER_SEASON) {
        daysInCurrentSeason = 0;
        currentSeason = static_cast<Season>((currentSeason + 1) % 4);
    }
}

// 获取当前季节
SeasonManager::Season SeasonManager::getCurrentSeason() const {
    return currentSeason;
}

// 获取当前季节的名称
std::string SeasonManager::getCurrentSeasonName() const {
    switch (currentSeason) {
    case Spring: return "Spring";
    case Summer: return "Summer";
    case Autumn: return "Autumn";
    case Winter: return "Winter";
    default: return "Unknown";
    }
}