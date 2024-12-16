#pragma once
#include <string>

// ���ڹ�������
class SeasonManager {
public:
    // ����ö��
    enum Season {
        Spring,
        Summer,
        Autumn,
        Winter
    };

    // ���캯��
    SeasonManager();

    // ���¼���
    void updateSeason(int days);

    // ��ȡ��ǰ����
    Season getCurrentSeason() const;

    // ��ȡ��ǰ���ڵ�����
    std::string getCurrentSeasonName() const;

private:
    Season currentSeason; // ��ǰ����
    int daysInCurrentSeason; // ��ǰ���ڵ�����
    static const int DAYS_PER_SEASON = 15; // ÿ�����ڳ���10��
};