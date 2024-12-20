#ifndef CROP_H
#define CROP_H

#include "cocos2d.h"

USING_NS_CC;

class FarmManager;

class Crop : public Sprite {
public:
    // ��������ö��
    enum CropType {
        ONION,
        POTATO,
        RADISH
    };

    Crop(const std::string& cropName, const std::string& imagePath, int maxGrowthTime, int maxWaterDays, int maxFertilizerDays, int maxPestDays, CropType cropType);
    ~Crop();


    // ��������״̬
    void update(float dt);

    // ��ˮ
    void water();

    // ʩ��
    void fertilize();

    void controlPest();

    // �ջ�
    bool harvest();

    // ��ȡ��ǰ�����׶�
    int getGrowthStage() const;

    // ��ȡ��ǰ����
    int getYield() const;

    // ��ȡ��������
    std::string get_Name() const;

    // ��������λ��
    void setPosition(const Vec2& position);

    int getWaterDays() const;

    int getFertilizerDays() const;

    int getPestDays() const;

    // ��ȡ����λ��
    Vec2 get_Position() const;

    // ������������
    CropType getCropType() const {
        return _cropType;
    }

    void setFarmManager(FarmManager* farmManager);

    std::string _cropName; // ��������
    int _growthStage; // �����׶Σ�0:����, 1:����, 2:����, 3:���ջ�
    int _growthTime; // ��ǰ����ʱ��
    int _maxGrowthTime; // �������ʱ��
    int _waterDays; // ��ǰȱˮ����
    int _maxWaterDays; // ���ȱˮ����
    int _fertilizerDays; // ��ǰȱ������
    int _maxFertilizerDays; // ���ȱ������
    int _pestDays; // ��ǰ�溦����
    int _maxPestDays; // ���溦����
    float _lastPestControlTime; // ���һ�η��γ溦��ʱ��
    float _lastWaterTime;
    float _lastFertilizerTime;
    int _yield; // ��ǰ����
    Label* _statusLabel; // ״̬��ǩ����ʾȱˮ��ȱ�ʣ�
    FarmManager* _farmManager;
    CropType _cropType; // ��������
private:
    
};

#endif // CROP_H