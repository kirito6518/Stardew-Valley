#pragma once
#include <string>

class SeasonManager {
public:
    enum Season {
        Spring,
        Summer,
        Autumn,
        Winter
    };

    SeasonManager();

    void updateSeason(int days);
    Season getCurrentSeason() const;
    std::string getCurrentSeasonName() const;

private:
    Season currentSeason;
    int daysInCurrentSeason;
    static const int DAYS_PER_SEASON = 10; // 每个季节持续10天
};