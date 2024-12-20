#ifndef FARMMANAGER_H
#define FARMMANAGER_H

#include "Crop.h"
#include <vector>

class MainMap; // 向前声明 MainMap 类

class FarmManager {
public:
    FarmManager();
    ~FarmManager();

    // 初始化农田
    void initFarm();

    // 更新农田状态
    void update(float dt);

    // 种植作物
    void FarmManager::plantCrop(const std::string& cropName, const std::string& imagePath, int maxGrowthTime, int maxWaterDays, int maxFertilizerDays, int maxPestDays, const Vec2& position, Crop::CropType cropType);

    // 浇水
    void waterCrop(const Vec2& position);

    // 施肥
    void fertilizeCrop(const Vec2& position);

    void controlPest(const Vec2& position);

    // 收获作物
    bool FarmManager::harvestCrop(const Vec2& position, int& yield);

    void FarmManager::removeCrop(Crop* crop);

    bool isPositionOccupied(const Vec2& position);

    // 其他函数声明
    void setMainMap(MainMap* mainMap);

    // 获取作物列表
    const std::vector<Crop*>& getCrops() const;
    std::vector<Crop*> _crops; // 作物列表
    
private:
    MainMap* mainMap;
};

#endif // FARMMANAGER_H