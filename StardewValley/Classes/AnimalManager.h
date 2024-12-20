#ifndef _ANIMAL_MANAGER_H
#define _ANIMAL_MANAGER_H

#include "cocos2d.h"
#include <string>
#include "Animal.h"

USING_NS_CC;

// ���������
class AnimalManager : public Layer {
public:

    // ��ȡ����ʵ��
    static AnimalManager* getInstance();

    // ��ʼ��
    virtual bool init();

    // ���ض���
    void CreateAnimations(std::string& name);

    // ���Ӷ��ֻ����������壩
    bool AnimalManager::AddAnimal(const std::string& name);

    // ɾ�����ֻɾ��������壩
    bool AnimalManager::RemoveAnimal(const std::string& name);

    // ɾ��һ��������壨������
    void OldDie(const std::string& name);

    // ÿ֡���£������ָ��ʱ�䣬���и����ɳ�һ���׶�
    void UpdateAnimals(float dt);

    // �ر�����
    void HideRanch(Ref* sender);

    // ����һ����������� (x, y)�������� Vec2
    Vec2 GenerateRandomPosition();

    // �������ֶ������Ŀ
    void CreateNumber();

    Sprite* ranchLayer; // ��������
    MenuItemImage* outButton; // �˳���ť

    MenuItemImage* BuyButtonPig; // ����
    MenuItemImage* KillButtonPig; // ����
    MenuItemImage* BuyButtonCow; // ����
    MenuItemImage* KillButtonCow; // ����
    MenuItemImage* BuyButtonSheep; // ����
    MenuItemImage* KillButtonSheep; // ����
    MenuItemImage* BuyButtonChook; // ����
    MenuItemImage* KillButtonChook; // ����

    Animal* animals[4]; // ���ֶ��0����1��ţ��2����3�Ǽ�
    Label* animalNum[4]; // ���ֶ����������ʾ

    unsigned int timeRecord; // ��¼�ϴμ�¼��ʱ�䣬�Ӷ��滮����ĳ���
    unsigned int Time; // ÿ���׶ε�����ʱ��

    Scene* mainMap;
private:
    // ˽�й��캯������ֹ�ⲿֱ��ʵ����
    AnimalManager();

    // ����ʵ��
    static AnimalManager* _instance;
};

#endif // _ANIMAL_MANAGER_H