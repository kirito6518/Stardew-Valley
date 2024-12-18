#ifndef __BRING_MINE_H__
#define __BRING_MINE_H__

#include "cocos2d.h"

USING_NS_CC;

class ChooseMineLayer : public Layer
{
public:
    // 获取单例实例
    static ChooseMineLayer* getInstance();

    // 初始化
    virtual bool init();

    // 改变矿物
    void ChangeMine(Ref* sender);

    // 不改变矿物
    void NoChangeMine(Ref* sender);

    Scene* cave; // 场景

    Sprite* chooseLayer;
    MenuItemImage* yesButton;//yes按钮
    MenuItemImage* noButton;//no按钮

    int chooseMine; // 选择的矿物，范围1-5，0表示未选择

private:
    // 私有构造函数，防止外部直接实例化
    ChooseMineLayer();

    // 单例实例
    static ChooseMineLayer* _instance;
};

#endif // __BRING_MINE_H__