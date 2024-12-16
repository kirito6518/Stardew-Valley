#ifndef CROP_H
#define CROP_H

#include "cocos2d.h"
#include <string>
#include <unordered_map>

// ���������࣬�̳���cocos2d::Node
class Crop : public cocos2d::Node {
public:
    // ��������������׶�ö��
    enum GrowthStage {
        Stage1,       // �׶�1
        Stage2,       // �׶�2
        Stage3,       // �׶�3
        Harvestable   // ���ջ�׶�
    };

    // ���캯������ʼ����������ƺ���ֲ����
    Crop(const std::string& name, const std::string& season);

    // ��������״̬������Ϊ����������
    void update(int days);

    // ��ˮ����
    void water();

    // ʩ�ʲ���
    void fertilize();

    // ��������Ƿ�����
    void checkDisease();

    // ��鵱ǰ�����Ƿ��ʺ���ֲ������
    bool isSeasonValid(const std::string& currentSeason) const;

    // ��ȡ��ǰ����������׶�
    GrowthStage getGrowthStage() const;

    // ��������Ƿ�����
    bool isDiseased() const { return isDiseasedFlag; }

    // ��ȡ���������
    std::string get_Name() const { return name; }

    // ��ȡ�������ֲ����
    std::string getSeason() const { return season; }

    // ��������Ƿ�����ջ�
    bool isReadyToHarvest() const;

    // ��ʾȱˮ����
    void showWaterAnimation();

    // ��ʾȱ�ʶ���
    void showFertilizeAnimation();

    // ��̬��Ա���������ڳ�ʼ������Ĳ���
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
    static std::unordered_map<std::string, int> growthTimes;       // �������������������
    static std::unordered_map<std::string, int> waterThresholds;   // ����ȱˮ��ֵ
    static std::unordered_map<std::string, int> fertilizerThresholds; // ����ȱ����ֵ

    // ������ʾ��ͼƬ
    void setGrowthStageImage();
};

#endif // CROP_H