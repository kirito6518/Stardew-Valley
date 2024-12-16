#include "FarmManager.h"
#include <algorithm>

// 构造函数，初始化农场管理器
FarmManager::FarmManager() {
    // 初始化作物和动物的参数
    Crop::initializeCropParameters();
    Animal::initializeAnimalParameters();
}

// 析构函数，释放动态分配的作物和动物对象
FarmManager::~FarmManager() {
    for (auto crop : crops) {
        delete crop;
    }
    for (auto animal : animals) {
        delete animal;
    }
}

// 种植作物
void FarmManager::plantCrop(const std::string& cropName, const std::string& season) {
    if (resourceManager.hasEnoughResource("Seeds", 1) && seasonManager.getCurrentSeasonName() == season) {
        resourceManager.useResource("Seeds", 1);
        crops.push_back(new Crop(cropName, season));
    }
}

// 给作物浇水
void FarmManager::waterCrop(Crop* crop) {
    if (resourceManager.hasEnoughResource("Water", 1)) {
        resourceManager.useResource("Water", 1);
        crop->water();
    }
}

// 给作物施肥
void FarmManager::fertilizeCrop(Crop* crop) {
    if (resourceManager.hasEnoughResource("Fertilizer", 1)) {
        resourceManager.useResource("Fertilizer", 1);
        crop->fertilize();
    }
}

// 更新作物状态
void FarmManager::updateCrops(int days) {
    for (auto crop : crops) {
        crop->update(days);
        crop->checkDisease();
        if (crop->isDiseased()) {
            crops.erase(std::remove(crops.begin(), crops.end(), crop), crops.end());
            delete crop;
        }
    }
}

// 收获作物
void FarmManager::harvestCrop(Crop* crop) {
    if (crop->isReadyToHarvest() && crop->isSeasonValid(seasonManager.getCurrentSeasonName())) {
        resourceManager.addResource("Seeds", 1);
        crops.erase(std::remove(crops.begin(), crops.end(), crop), crops.end());
        delete crop;
    }
}

// 添加动物
void FarmManager::addAnimal(const std::string& animalName, const std::string& breedSeason) {
    animals.push_back(new Animal(animalName, breedSeason));
}

// 收集动物产品
void FarmManager::collectAnimalProduct(Animal* animal) {
    if (animal->canProduce()) {
        if (animal->getProductType() == "Milk") {
            resourceManager.addResource("Water", 1);
        }
        else if (animal->getProductType() == "Egg") {
            resourceManager.addResource("Seeds", 1);
        }
        animal->collectProduct();
    }
}

// 更新动物状态
void FarmManager::updateAnimals(int days) {
    for (auto animal : animals) {
        animal->update(days);
    }
}

// 更新季节
void FarmManager::updateSeason(int days) {
    seasonManager.updateSeason(days);
}

// 繁殖动物
void FarmManager::breedAnimals() {
    std::vector<Animal*> newAnimals;
    for (auto animal : animals) {
        if (animal->canBreed(seasonManager.getCurrentSeasonName())) {
            Animal* newAnimal = animal->breed();
            newAnimals.push_back(newAnimal);
        }
    }
    animals.insert(animals.end(), newAnimals.begin(), newAnimals.end());
}

// 收集肥料
void FarmManager::collectFertilizer() {
    int totalFertilizer = 0;
    for (auto animal : animals) {
        totalFertilizer += animal->getFertilizerCount();
        animal->collectProduct();
    }
    resourceManager.addResource("Fertilizer", totalFertilizer);
}

// 喂食动物
void FarmManager::feedAnimals() {
    for (auto animal : animals) {
        if (animal->isHungry()) {
            if (resourceManager.hasEnoughResource("Feed", animal->getFeedAmount())) {
                resourceManager.useResource("Feed", animal->getFeedAmount());
                animal->feed();
            }
        }
    }
}