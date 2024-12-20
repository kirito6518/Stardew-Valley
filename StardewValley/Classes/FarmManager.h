#ifndef FARMMANAGER_H
#define FARMMANAGER_H

#include "Crop.h"
#include <vector>

class MainMap; // ��ǰ���� MainMap ��

class FarmManager {
public:
    FarmManager();
    ~FarmManager();

    // ��ʼ��ũ��
    void initFarm();

    // ����ũ��״̬
    void update(float dt);

    // ��ֲ����
    void FarmManager::plantCrop(const std::string& cropName, const std::string& imagePath, int maxGrowthTime, int maxWaterDays, int maxFertilizerDays, int maxPestDays, const Vec2& position, Crop::CropType cropType);

    // ��ˮ
    void waterCrop(const Vec2& position);

    // ʩ��
    void fertilizeCrop(const Vec2& position);

    void controlPest(const Vec2& position);

    // �ջ�����
    bool FarmManager::harvestCrop(const Vec2& position, int& yield);

    void FarmManager::removeCrop(Crop* crop);

    bool isPositionOccupied(const Vec2& position);

    // ������������
    void setMainMap(MainMap* mainMap);

    // ��ȡ�����б�
    const std::vector<Crop*>& getCrops() const;
    std::vector<Crop*> _crops; // �����б�
    
private:
    MainMap* mainMap;
};

#endif // FARMMANAGER_H