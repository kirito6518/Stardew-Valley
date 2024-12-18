#ifndef CROP_H
#define CROP_H

#include "cocos2d.h"

USING_NS_CC;

class Crop : public Sprite {
public:
    Crop(const std::string& cropName, const std::string& imagePath, int maxGrowthTime, int maxWaterDays, int maxFertilizerDays);
    ~Crop();

    // ��������״̬
    void update(float dt);

    // ��ˮ
    void water();

    // ʩ��
    void fertilize();

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

    // ��ȡ����λ��
    Vec2 get_Position() const;

private:
    std::string _cropName; // ��������
    int _growthStage; // �����׶Σ�0:����, 1:����, 2:����, 3:���ջ�
    int _growthTime; // ��ǰ����ʱ��
    int _maxGrowthTime; // �������ʱ��
    int _waterDays; // ��ǰȱˮ����
    int _maxWaterDays; // ���ȱˮ����
    int _fertilizerDays; // ��ǰȱ������
    int _maxFertilizerDays; // ���ȱ������
    float _lastWaterTime;
    float _lastFertilizerTime;
    int _yield; // ��ǰ����
    Label* _statusLabel; // ״̬��ǩ����ʾȱˮ��ȱ�ʣ�
};

#endif // CROP_H