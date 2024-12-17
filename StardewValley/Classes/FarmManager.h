#pragma once
#ifndef FARMMANAGER_H
#define FARMMANAGER_H

#include <vector>
#include "Crop.h"
#include "Animal.h"
#include "ResourceManager.h"
#include "SeasonManager.h"

// ũ����������
class FarmManager {
public:
    // ���캯��
    FarmManager();

    // ��������
    ~FarmManager();

    // ��ֲ����
    void plantCrop(const std::string& cropName, const std::string& season);

    // �����ｽˮ
    void waterCrop(Crop* crop);

    // ������ʩ��
    void fertilizeCrop(Crop* crop);

    // ��������״̬
    void updateCrops(int days);

    // �ջ�����
    void harvestCrop(Crop* crop);

    // ��Ӷ���
    void addAnimal(const std::string& animalName, const std::string& breedSeason);

    // �ռ������Ʒ
    void collectAnimalProduct(Animal* animal);

    // ���¶���״̬
    void updateAnimals(int days);

    // ���¼���
    void updateSeason(int days);

    // ��ֳ����
    void breedAnimals();

    // �ռ�����
    void collectFertilizer();

    // ιʳ����
    void feedAnimals();

private:
    std::vector<Crop*> crops;       // �����б�
    std::vector<Animal*> animals;   // �����б�
    ResourceManager resourceManager; // ��Դ������
    SeasonManager seasonManager;    // ���ڹ�����
};

#endif // FARMMANAGER_H