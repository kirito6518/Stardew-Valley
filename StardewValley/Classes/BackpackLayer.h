#ifndef __BACKPACK_LAYER_H__
#define __BACKPACK_LAYER_H__

#include "cocos2d.h"
#include "Item.h"
#include "MainMap.h"


USING_NS_CC;

/**
 * @class BackpackLayer
 * @brief 背包层类，负责显示和管理背包中的物品。
 *
 * BackpackLayer 是一个 Cocos2d-x 的 Layer，用于显示背包界面。它包含了背包的背景、物品图标、物品数量、
 * 物品名称等信息。用户可以通过该层与背包进行交互，例如添加物品、移除物品、显示物品详情等。
 */
class BackpackLayer : public cocos2d::Layer
{
public:


    //创建一个 BackpackLayer 对象
    static BackpackLayer* create(const std::string& backpackBgPath, int maxItems);

    //初始化 BackpackLayer
    bool init(const std::string& backpackBgPath, int maxItems);

    //向背包中添加物品
    bool addItem(cocos2d::Sprite* itemSprite);

    //从背包中移除物品
    void removeItem(cocos2d::Sprite* itemSprite);

   //隐藏背包界面
    void hideBackpack(cocos2d::Ref* sender);

    // 获取所有物品的向量
    const cocos2d::Vector<Sprite*>& getItemSprites() const { return itemSprites; }

    //点击使用按钮的回调函数
    void onUseButtonClicked(Ref* sender);

    //点击摧毁按钮的回调函数
    void onDestroyButtonClicked(Ref* sender);

    //鼠标事件监听器与物品的交互
    void setupCombinedMouseListener();



    MenuItemImage* hideButton;//背包隐藏按钮

    cocos2d::Sprite* backpackBgSprite; ///< 背包背景精灵

    int gridWidth; ///< 背包格子的宽度（列数）
    int gridHeight; ///< 背包格子的高度（行数）
    int gridSpacing; ///< 背包格子之间的间隔
    float gridStartX; ///< 背包格子的起始 X 坐标
    float gridStartY; ///< 背包格子的起始 Y 坐标

    int maxItems; ///< 背包的最大物品数量
    int currentItems; ///< 当前背包中的物品数量

private:

    cocos2d::Vector<cocos2d::Sprite*> itemSprites; ///< 背包中的物品图标列表
    cocos2d::Label* itemNameLabel; ///< 物品名称标签
    cocos2d::Label* itemCountLabel; ///< 物品数量标签

    cocos2d::MenuItemImage* useButton; ///< 使用物品按钮
    cocos2d::Label* useResultLabel; ///< 使用物品结果标签

    cocos2d::MenuItemImage* destroyButton; ///< 摧毁物品按钮
    cocos2d::Label* destroyResultLabel;///< 摧毁物品结果标签

    cocos2d::Sprite* itemDetaUI;//显示物品详情的界面
    cocos2d::Label* itemDataLabel;//显示物品详情（名称）的标签


};

#endif // __BACKPACK_LAYER_H__