#pragma once
#include <string>

class Crop {
public:
    Crop(std::string name, int growthTime, std::string season);

    bool isReadyToHarvest() const;
    void update(int days);
    void water();
    void fertilize();
    void checkDisease();
    bool isSeasonValid(const std::string& currentSeason) const;

    std::string getName() const { return name; }
    std::string getSeason() const { return season; }
    bool isDiseased() const { return isDiseased; }

private:
    std::string name;          // ��������
    int growthTime;            // ����ʱ�䣨����Ϸ����Ϊ��λ��
    std::string season;        // �ʺ���ֲ�ļ���
    bool isWatered;            // �Ƿ��ѽ�ˮ
    bool isFertilized;         // �Ƿ���ʩ��
    bool isDiseased;           // �Ƿ񻼲�
    int daysSincePlanted;      // ��ֲ�������
};
