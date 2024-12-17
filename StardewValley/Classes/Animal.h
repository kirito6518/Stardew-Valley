#ifndef ANIMAL_H
#define ANIMAL_H

#include "cocos2d.h"
#include <string>
#include <unordered_map>

// �����࣬�̳���cocos2d::Node
class Animal : public cocos2d::Node {
public:
    // ���캯��
    Animal(const std::string& name, const std::string& breedSeason);

    // �ж϶����Ƿ����������Ʒ
    bool canProduce() const;

    // ���¶����״̬
    void update(int days);

    // �ռ�����Ĳ�Ʒ
    void collectProduct();

    // �ж϶����Ƿ�����ڵ�ǰ���ڷ�ֳ
    bool canBreed(const std::string& currentSeason) const;

    // ��ֳ�������һ���µĶ������
    Animal* breed() const;

    // ιʳ����
    void feed();

    // �ж϶����Ƿ񼢶�
    bool isHungry() const;

    // ��ȡ��������
    std::string get_Name() const { return name; }

    // ��ȡ��Ʒ����
    std::string getProductType() const { return productType; }

    // ��ȡ��������
    int getFertilizerCount() const { return fertilizerCount; }

    // ��ȡÿ��ιʳ��
    int getFeedAmount() const { return feedAmount; }

    // ��ʾ��������
    void showHungryAnimation();

    // ��̬��Ա���������ڳ�ʼ���������
    static void initializeAnimalParameters();

private:
    std::string name;               // ��������
    std::string productType;        // ��Ʒ���ͣ���ţ�̡������ȣ�
    int daysSinceLastProduct;       // �ϴ�������Ʒ�������
    int fertilizerCount;            // ����������ÿ��������Ʒʱ���ɣ�
    std::string breedSeason;        // ��ֳ����
    int hungerThreshold;            // ������ֵ
    int feedAmount;                 // ÿ��ιʳ��
    int daysSinceLastFed;           // �ϴ�ιʳ�������
    int lifespan;                   // ����
    cocos2d::Sprite* sprite;        // ������ʾ����ľ���

    // ��̬��Ա�������洢����Ĳ���
    static std::unordered_map<std::string, int> productTimes;
    static std::unordered_map<std::string, std::string> productTypes;
    static std::unordered_map<std::string, int> hungerThresholds;
    static std::unordered_map<std::string, int> feedAmounts;
    static std::unordered_map<std::string, int> lifespans;
};

#endif // ANIMAL_H