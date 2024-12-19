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

void FarmManager::plantCrop(const std::string& cropName, const std::string& imagePath, int maxGrowthTime, int maxWaterDays, int maxFertilizerDays, int maxPestDays, const Vec2& position) {
    Crop* crop = new Crop(cropName, imagePath, maxGrowthTime, maxWaterDays, maxFertilizerDays, maxPestDays);
    crop->setFarmManager(this);
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

void FarmManager::controlPest(const Vec2& position) {
    for (auto crop : _crops) {
        if (crop->getPosition() == position) {
            crop->controlPest();
            break;
        }
    }
}

void FarmManager::removeCrop(Crop* crop) {
    for (auto it = _crops.begin(); it != _crops.end(); ) {
        if (*it == crop) {
            it = _crops.erase(it);
        }
        else {
            ++it;
        }
    }
}

bool FarmManager::harvestCrop(const Vec2& position, int& yield) {
    for (auto it = _crops.begin(); it != _crops.end();) {
        if ((*it)->getPosition() == position) {
            if ((*it)->harvest()) {
                yield = (*it)->getYield();
                (*it)->removeFromParent();
                delete* it;
                it = _crops.erase(it);
                return true;
            }
            else {
                ++it;
            }
        }
        else {
            ++it;
        }
    }
    return false;
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