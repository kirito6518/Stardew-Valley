#pragma once
#include <string>

class SeasonManager {
public:
    // ����ö��
    enum Season {
        Spring,
        Summer,
        Autumn,
        Winter
    };

    // ��ȡ����ʵ��
    static SeasonManager* getInstance();

    // ���¼���
    void updateSeason(int days);

    // ��ȡ��ǰ����
    Season getCurrentSeason() const;

    // ��ȡ��ǰ��������
    std::string getCurrentSeasonName() const;

    // ��ȡ��ǰ���ڵ�����
    int getDaysInCurrentSeason() const { return daysInCurrentSeason; }

    // ���캯��˽�л�
    SeasonManager();

    // ��ֹ��������͸�ֵ����
    SeasonManager(const SeasonManager&) = delete;
    SeasonManager& operator=(const SeasonManager&) = delete;

    Season currentSeason; // ��ǰ����
    int daysInCurrentSeason; // ��ǰ���ڵ�����
    static const int DAYS_PER_SEASON = 15; // ÿ�����ڵ�����

    static SeasonManager* instance; // ����ʵ��
private:
    
};