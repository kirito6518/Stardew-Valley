#pragma once
#ifndef FARMMANAGER_H
#define FARMMANAGER_H

#include <vector>
#include "Crop.h"
#include "Animal.h"
#include "ResourceManager.h"
#include "SeasonManager.h"

// 农场管理器类
class FarmManager {
public:
    // 构造函数
    FarmManager();

    // 析构函数
    ~FarmManager();

    // 种植作物
    void plantCrop(const std::string& cropName, const std::string& season);

    // 给作物浇水
    void waterCrop(Crop* crop);

    // 给作物施肥
    void fertilizeCrop(Crop* crop);

    // 更新作物状态
    void updateCrops(int days);

    // 收获作物
    void harvestCrop(Crop* crop);

    // 添加动物
    void addAnimal(const std::string& animalName, const std::string& breedSeason);

    // 收集动物产品
    void collectAnimalProduct(Animal* animal);

    // 更新动物状态
    void updateAnimals(int days);

    // 更新季节
    void updateSeason(int days);

    // 繁殖动物
    void breedAnimals();

    // 收集肥料
    void collectFertilizer();

    // 喂食动物
    void feedAnimals();

private:
    std::vector<Crop*> crops;       // 作物列表
    std::vector<Animal*> animals;   // 动物列表
    ResourceManager resourceManager; // 资源管理器
    SeasonManager seasonManager;    // 季节管理器
};

#endif // FARMMANAGER_H