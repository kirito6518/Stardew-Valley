#ifndef FARMMANAGER_H
#define FARMMANAGER_H

#include "Crop.h"
#include <vector>

class FarmManager {
public:
    FarmManager();
    ~FarmManager();

    // ��ʼ��ũ��
    void initFarm();

    // ����ũ��״̬
    void update(float dt);

    // ��ֲ����
    void plantCrop(const std::string& cropName, const std::string& imagePath, int maxGrowthTime, int maxWaterDays, int maxFertilizerDays, const Vec2& position);

    // ��ˮ
    void waterCrop(const Vec2& position);

    // ʩ��
    void fertilizeCrop(const Vec2& position);

    // �ջ�����
    void harvestCrop(const Vec2& position);

    bool isPositionOccupied(const Vec2& position);

    // ��ȡ�����б�
    const std::vector<Crop*>& getCrops() const;
    std::vector<Crop*> _crops; // �����б�

private:
    
};

#endif // FARMMANAGER_H