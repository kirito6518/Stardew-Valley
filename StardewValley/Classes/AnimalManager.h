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



private:
    // ˽�й��캯������ֹ�ⲿֱ��ʵ����
    AnimalManager();

    // ����ʵ��
    static AnimalManager* _instance;
};

#endif // _ANIMAL_MANAGER_H