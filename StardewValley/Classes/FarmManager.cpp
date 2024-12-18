#include "FarmManager.h"
#include "MainMap.h"

FarmManager::FarmManager() {}

FarmManager::~FarmManager() {
    for (auto crop : _crops) {
        delete crop;
    }
}

void FarmManager::initFarm() {
    // 初始化农田，可以在这里添加默认的作物
}

void FarmManager::update(float dt) {
    for (auto crop : _crops) {
        crop->update(dt);
    }
}

void FarmManager::setMainMap(MainMap* mainMap) {
    this->mainMap = mainMap;
}

void FarmManager::plantCrop(const std::string& cropName, const std::string& imagePath, int maxGrowthTime, int maxWaterDays, int maxFertilizerDays, const Vec2& position) {
    Crop* crop = new Crop(cropName, imagePath, maxGrowthTime, maxWaterDays, maxFertilizerDays);
    crop->setPosition(position);
    _crops.push_back(crop);
    if (mainMap) {
        mainMap->addChild(crop, 1);
    }
    else {
        CCLOG("mainMap is nullptr when adding crop.");
    }
}

void FarmManager::waterCrop(const Vec2& position) {
    for (auto crop : _crops) {
        if (crop->getPosition() == position) {
            crop->water();
            break;
        }
    }
}

void FarmManager::fertilizeCrop(const Vec2& position) {
    for (auto crop : _crops) {
        if (crop->getPosition() == position) {
            crop->fertilize();
            break;
        }
    }
}

void FarmManager::harvestCrop(const Vec2& position) {
    for (auto it = _crops.begin(); it != _crops.end(); ++it) {
        if ((*it)->getPosition() == position) {
            if ((*it)->harvest()) {
                // 获取收获的物品并添加到背包
                int yield = (*it)->getYield();
                // BackpackManager::addItem("Onion", yield);
                delete* it;
                _crops.erase(it);
            }
            break;
        }
    }
}

const std::vector<Crop*>& FarmManager::getCrops() const {
    return _crops;
}

bool FarmManager::isPositionOccupied(const Vec2& position) {
    for (auto crop : _crops) {
        if (crop->getPosition() == position) {
            return true;
        }
    }
    return false;
}