#ifndef CROP_H
#define CROP_H

#include "cocos2d.h"
#include <string>
#include <unordered_map>

// 定义作物类，继承自cocos2d::Node
class Crop : public cocos2d::Node {
public:
    // 定义作物的生长阶段枚举
    enum GrowthStage {
        Stage1,       // 阶段1
        Stage2,       // 阶段2
        Stage3,       // 阶段3
        Harvestable   // 可收获阶段
    };

    // 构造函数，初始化作物的名称和种植季节
    Crop(const std::string& name, const std::string& season);

    // 更新作物状态，参数为经过的天数
    void update(int days);

    // 浇水操作
    void water();

    // 施肥操作
    void fertilize();

    // 检查作物是否生病
    void checkDisease();

    // 检查当前季节是否适合种植该作物
    bool isSeasonValid(const std::string& currentSeason) const;

    // 获取当前作物的生长阶段
    GrowthStage getGrowthStage() const;

    // 检查作物是否生病
    bool isDiseased() const { return isDiseasedFlag; }

    // 获取作物的名称
    std::string get_Name() const { return name; }

    // 获取作物的种植季节
    std::string getSeason() const { return season; }

    // 检查作物是否可以收获
    bool isReadyToHarvest() const;

    // 显示缺水动画
    void showWaterAnimation();

    // 显示缺肥动画
    void showFertilizeAnimation();

    // 静态成员函数，用于初始化作物的参数
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
    static std::unordered_map<std::string, int> growthTimes;       // 作物生长所需的总天数
    static std::unordered_map<std::string, int> waterThresholds;   // 作物缺水阈值
    static std::unordered_map<std::string, int> fertilizerThresholds; // 作物缺肥阈值

    // 更新显示的图片
    void setGrowthStageImage();
};

#endif // CROP_H