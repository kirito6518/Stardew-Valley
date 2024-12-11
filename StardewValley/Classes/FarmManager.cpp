#include "FarmManager.h"
#include <algorithm>

FarmManager::FarmManager() {
    // 初始化作物和动物的参数
    Crop::initializeCropParameters();
    Animal::initializeAnimalParameters();
}

FarmManager::~FarmManager() {
    for (auto crop : crops) {
        delete crop;
    }
    for (auto animal : animals) {
        delete animal;
    }
}

void FarmManager::plantCrop(const std::string& cropName, const std::string& season) {
    if (resourceManager.hasEnoughResource("Seeds", 1) && seasonManager.getCurrentSeasonName() == season) {
        resourceManager.useResource("Seeds", 1);
        crops.push_back(new Crop(cropName, season));
    }
}

void FarmManager::waterCrop(Crop* crop) {
    if (resourceManager.hasEnoughResource("Water", 1)) {
        resourceManager.useResource("Water", 1);
        crop->water();
    }
}

void FarmManager::fertilizeCrop(Crop* crop) {
    if (resourceManager.hasEnoughResource("Fertilizer", 1)) {
        resourceManager.useResource("Fertilizer", 1);
        crop->fertilize();
    }
}

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

void FarmManager::harvestCrop(Crop* crop) {
    if (crop->isReadyToHarvest() && crop->isSeasonValid(seasonManager.getCurrentSeasonName())) {
        resourceManager.addResource("Seeds", 1);
        crops.erase(std::remove(crops.begin(), crops.end(), crop), crops.end());
        delete crop;
    }
}

void FarmManager::addAnimal(const std::string& animalName, const std::string& breedSeason) {
    animals.push_back(new Animal(animalName, breedSeason));
}

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

void FarmManager::updateAnimals(int days) {
    for (auto animal : animals) {
        animal->update(days);
    }
}

void FarmManager::updateSeason(int days) {
    seasonManager.updateSeason(days);
}

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

void FarmManager::collectFertilizer() {
    int totalFertilizer = 0;
    for (auto animal : animals) {
        totalFertilizer += animal->getFertilizerCount();
        animal->collectProduct();
    }
    resourceManager.addResource("Fertilizer", totalFertilizer);
}

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