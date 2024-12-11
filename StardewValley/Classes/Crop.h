#ifndef CROP_H
#define CROP_H

#include "cocos2d.h"
#include <string>
#include <unordered_map>

class Crop : public cocos2d::Node {
public:
    enum GrowthStage {
        Stage1,
        Stage2,
        Stage3,
        Harvestable
    };

    Crop(const std::string& name, const std::string& season);

    void update(int days);
    void water();
    void fertilize();
    void checkDisease();
    bool isSeasonValid(const std::string& currentSeason) const;
    GrowthStage getGrowthStage() const;
    bool isDiseased() const { return isDiseasedFlag; }
    std::string get_Name() const { return name; }
    std::string getSeason() const { return season; }

    // 新增：检查作物是否可以收获
    bool isReadyToHarvest() const;

    // 显示缺水或缺肥的动画
    void showWaterAnimation();
    void showFertilizeAnimation();

    // 静态成员函数，用于初始化作物参数
    static void initializeCropParameters();

private:
    std::string name;          // 作物名称
    std::string season;        // 种植季节
    bool isWatered;            // 是否浇水
    bool isFertilized;         // 是否施肥
    bool isDiseasedFlag;       // 是否生病
    int daysSincePlanted;      // 种植后的天数
    GrowthStage growthStage;   // 当前生长阶段
    cocos2d::Sprite* sprite;   // 用于显示作物的精灵

    // 静态成员变量，存储作物的参数
    static std::unordered_map<std::string, int> growthTimes;
    static std::unordered_map<std::string, int> waterThresholds;
    static std::unordered_map<std::string, int> fertilizerThresholds;

    // 更新显示的图片
    void setGrowthStageImage();
};

#endif // CROP_H