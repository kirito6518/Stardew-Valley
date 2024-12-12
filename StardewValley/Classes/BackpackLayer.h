#ifndef __BACKPACK_LAYER_H__
#define __BACKPACK_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

//BackpackLayer 负责显示背包背景和物品
class BackpackLayer : public cocos2d::Layer
{
public:
    // 创建背包层，传入背包背景图片路径和物品上限
    static BackpackLayer* create(const std::string& backpackBgPath, int maxItems);

    // 初始化方法
    virtual bool init(const std::string& backpackBgPath, int maxItems);

    // 添加物品到背包
    bool addItem(const std::string& itemImagePath);

    // 隐藏背包层
    void hideBackpack(Ref* sender);

private:
    // 背包背景精灵
    cocos2d::Sprite* backpackBgSprite;

    // 物品容器
    cocos2d::Vector<cocos2d::Sprite*> itemSprites;

    // 背包物品上限
    int maxItems;

    // 当前背包中的物品数量
    int currentItems;
};

#endif // __BACKPACK_LAYER_H__