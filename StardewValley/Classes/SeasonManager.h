#pragma once
#include <string>

// 季节管理器类
class SeasonManager {
public:
    // 季节枚举
    enum Season {
        Spring,
        Summer,
        Autumn,
        Winter
    };

    // 构造函数
    SeasonManager();

    // 更新季节
    void updateSeason(int days);

    // 获取当前季节
    Season getCurrentSeason() const;

    // 获取当前季节的名称
    std::string getCurrentSeasonName() const;

    // 获取当前季节已过去的天数
    int getDaysInCurrentSeason() const { return daysInCurrentSeason; }

    Season currentSeason; // 当前季节
    int daysInCurrentSeason; // 当前季节的天数
    static const int DAYS_PER_SEASON = 15; // 每个季节持续10天
private:
    
};