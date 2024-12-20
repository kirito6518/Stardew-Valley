#pragma once
#include <string>

class SeasonManager {
public:
    // 季节枚举
    enum Season {
        Spring,
        Summer,
        Autumn,
        Winter
    };

    // 获取单例实例
    static SeasonManager* getInstance();

    // 更新季节
    void updateSeason(int days);

    // 获取当前季节
    Season getCurrentSeason() const;

    // 获取当前季节名称
    std::string getCurrentSeasonName() const;

    // 获取当前季节的天数
    int getDaysInCurrentSeason() const { return daysInCurrentSeason; }

    // 构造函数私有化
    SeasonManager();

    // 禁止拷贝构造和赋值操作
    SeasonManager(const SeasonManager&) = delete;
    SeasonManager& operator=(const SeasonManager&) = delete;

    Season currentSeason; // 当前季节
    int daysInCurrentSeason; // 当前季节的天数
    static const int DAYS_PER_SEASON = 15; // 每个季节的天数

    static SeasonManager* instance; // 单例实例
private:
    
};