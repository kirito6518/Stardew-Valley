#pragma once
#ifndef FARMMANAGER_H
#define FARMMANAGER_H

#include <vector>
#include "Crop.h"
#include "Animal.h"
#include "ResourceManager.h"
#include "SeasonManager.h"

class FarmManager {
public:
    FarmManager();
    ~FarmManager();

    void plantCrop(const std::string& cropName, const std::string& season);
    void waterCrop(Crop* crop);
    void fertilizeCrop(Crop* crop);
    void updateCrops(int days);
    void harvestCrop(Crop* crop);
    void addAnimal(const std::string& animalName, const std::string& breedSeason);
    void collectAnimalProduct(Animal* animal);
    void updateAnimals(int days);
    void updateSeason(int days);
    void breedAnimals();
    void collectFertilizer();
    void feedAnimals();

private:
    std::vector<Crop*> crops;
    std::vector<Animal*> animals;
    ResourceManager resourceManager;
    SeasonManager seasonManager;
};

#endif // FARMMANAGER_H