#ifndef FARMMANAGER_H
#define FARMMANAGER_H

#include "Crop.h"
#include <vector>

class FarmManager {
public:
    FarmManager();
    ~FarmManager();

    // 初始化农田
    void initFarm();

    // 更新农田状态
    void update(float dt);

    // 种植作物
    void plantCrop(const std::string& cropName, const std::string& imagePath, int maxGrowthTime, int maxWaterDays, int maxFertilizerDays, const Vec2& position);

    // 浇水
    void waterCrop(const Vec2& position);

    // 施肥
    void fertilizeCrop(const Vec2& position);

    // 收获作物
    void harvestCrop(const Vec2& position);

    bool isPositionOccupied(const Vec2& position);

    // 获取作物列表
    const std::vector<Crop*>& getCrops() const;
    std::vector<Crop*> _crops; // 作物列表

private:
    
};

#endif // FARMMANAGER_H