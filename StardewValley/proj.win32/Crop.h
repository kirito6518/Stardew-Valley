#pragma once
#include <string>

class Crop {
public:
    Crop(std::string name, int growthTime, std::string season);

    bool isReadyToHarvest() const;
    void update(int days);
    void water();
    void fertilize();
    void checkDisease();
    bool isSeasonValid(const std::string& currentSeason) const;

    std::string getName() const { return name; }
    std::string getSeason() const { return season; }
    bool isDiseased() const { return isDiseased; }

private:
    std::string name;          // 作物名称
    int growthTime;            // 成熟时间（以游戏天数为单位）
    std::string season;        // 适合种植的季节
    bool isWatered;            // 是否已浇水
    bool isFertilized;         // 是否已施肥
    bool isDiseased;           // 是否患病
    int daysSincePlanted;      // 种植后的天数
};
