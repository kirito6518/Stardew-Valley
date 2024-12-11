#ifndef CROP_H
#define CROP_H

#include "cocos2d.h"
#include <string>
#include <unordered_map>

class Crop : public cocos2d::Node {
public:
    enum GrowthStage {
        Stage1,
        Stage2,
        Stage3,
        Harvestable
    };

    Crop(const std::string& name, const std::string& season);

    void update(int days);
    void water();
    void fertilize();
    void checkDisease();
    bool isSeasonValid(const std::string& currentSeason) const;
    GrowthStage getGrowthStage() const;
    bool isDiseased() const { return isDiseasedFlag; }
    std::string get_Name() const { return name; }
    std::string getSeason() const { return season; }

    // ��������������Ƿ�����ջ�
    bool isReadyToHarvest() const;

    // ��ʾȱˮ��ȱ�ʵĶ���
    void showWaterAnimation();
    void showFertilizeAnimation();

    // ��̬��Ա���������ڳ�ʼ���������
    static void initializeCropParameters();

private:
    std::string name;          // ��������
    std::string season;        // ��ֲ����
    bool isWatered;            // �Ƿ�ˮ
    bool isFertilized;         // �Ƿ�ʩ��
    bool isDiseasedFlag;       // �Ƿ�����
    int daysSincePlanted;      // ��ֲ�������
    GrowthStage growthStage;   // ��ǰ�����׶�
    cocos2d::Sprite* sprite;   // ������ʾ����ľ���

    // ��̬��Ա�������洢����Ĳ���
    static std::unordered_map<std::string, int> growthTimes;
    static std::unordered_map<std::string, int> waterThresholds;
    static std::unordered_map<std::string, int> fertilizerThresholds;

    // ������ʾ��ͼƬ
    void setGrowthStageImage();
};

#endif // CROP_H