#ifndef __BRING_MINE_H__
#define __BRING_MINE_H__

#include "cocos2d.h"

USING_NS_CC;

class ChooseMineLayer : public Layer
{
public:
    // ��ȡ����ʵ��
    static ChooseMineLayer* getInstance();

    // ��ʼ��
    virtual bool init();

    // �ı����
    void ChangeMine(Ref* sender);

    // ���ı����
    void NoChangeMine(Ref* sender);

    Scene* cave; // ����

    Sprite* chooseLayer;
    MenuItemImage* yesButton;//yes��ť
    MenuItemImage* noButton;//no��ť

    int chooseMine; // ѡ��Ŀ����Χ1-5��0��ʾδѡ��

private:
    // ˽�й��캯������ֹ�ⲿֱ��ʵ����
    ChooseMineLayer();

    // ����ʵ��
    static ChooseMineLayer* _instance;
};

#endif // __BRING_MINE_H__