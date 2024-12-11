#include "SeasonManager.h"

SeasonManager::SeasonManager() : currentSeason(Spring), daysInCurrentSeason(0) {}

void SeasonManager::updateSeason(int days) {
    daysInCurrentSeason += days;
    if (daysInCurrentSeason >= DAYS_PER_SEASON) {
        daysInCurrentSeason = 0;
        currentSeason = static_cast<Season>((currentSeason + 1) % 4);
    }
}

SeasonManager::Season SeasonManager::getCurrentSeason() const {
    return currentSeason;
}

std::string SeasonManager::getCurrentSeasonName() const {
    switch (currentSeason) {
    case Spring: return "Spring";
    case Summer: return "Summer";
    case Autumn: return "Autumn";
    case Winter: return "Winter";
    default: return "Unknown";
    }
}