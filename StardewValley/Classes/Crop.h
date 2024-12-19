#ifndef CROP_H
#define CROP_H

#include "cocos2d.h"

USING_NS_CC;

class FarmManager;

class Crop : public Sprite {
public:
    Crop(const std::string& cropName, const std::string& imagePath, int maxGrowthTime, int maxWaterDays, int maxFertilizerDays, int maxPestDays);
    ~Crop();

    // 更新作物状态
    void update(float dt);

    // 浇水
    void water();

    // 施肥
    void fertilize();

    void controlPest();

    // 收获
    bool harvest();

    // 获取当前生长阶段
    int getGrowthStage() const;

    // 获取当前产量
    int getYield() const;

    // 获取作物名称
    std::string get_Name() const;

    // 设置作物位置
    void setPosition(const Vec2& position);

    int getWaterDays() const;

    int getFertilizerDays() const;

    int getPestDays() const;

    // 获取作物位置
    Vec2 get_Position() const;

    void setFarmManager(FarmManager* farmManager);

    std::string _cropName; // 作物名称
    int _growthStage; // 生长阶段（0:种子, 1:幼苗, 2:成熟, 3:可收获）
    int _growthTime; // 当前生长时间
    int _maxGrowthTime; // 最大生长时间
    int _waterDays; // 当前缺水天数
    int _maxWaterDays; // 最大缺水天数
    int _fertilizerDays; // 当前缺肥天数
    int _maxFertilizerDays; // 最大缺肥天数
    int _pestDays; // 当前虫害天数
    int _maxPestDays; // 最大虫害天数
    float _lastPestControlTime; // 最近一次防治虫害的时间
    float _lastWaterTime;
    float _lastFertilizerTime;
    int _yield; // 当前产量
    Label* _statusLabel; // 状态标签（显示缺水或缺肥）
    FarmManager* _farmManager;
private:
    
};

#endif // CROP_H