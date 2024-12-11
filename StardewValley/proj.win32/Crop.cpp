#include "Crop.h"

Crop::Crop(std::string name, int growthTime, std::string season)
    : name(name), growthTime(growthTime), season(season),
    isWatered(false), isFertilized(false), isDiseased(false), daysSincePlanted(0) {
}

bool Crop::isReadyToHarvest() const {
    return daysSincePlanted >= growthTime;
}

void Crop::update(int days) {
    daysSincePlanted += days;
}

void Crop::water() {
    isWatered = true;
}

void Crop::fertilize() {
    isFertilized = true;
}

void Crop::checkDisease() {
    // ¼òµ¥µÄ¼²²¡¼ì²âÂß¼­
    if (!isWatered || !isFertilized) {
        isDiseased = true;
    }
}

bool Crop::isSeasonValid(const std::string& currentSeason) const {
    return season == currentSeason;
}