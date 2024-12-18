#ifndef __SHOP_LAYER_H__
#define __SHOP_LAYER_H__

#include "cocos2d.h"
#include "ShopItem.h" 


USING_NS_CC;

/**
 * @class ShopLayer
 * @brief 商店层类，负责显示和管理商店中的物品。
 *
 * ShopLayer 是一个 Cocos2d-x 的 Layer，用于显示商店界面。它包含了商店的背景、物品图标、物品数量、
 * 物品名称等信息。用户可以通过该层与商店进行交互，例如购买物品、显示物品详情等。
 */
class ShopLayer : public cocos2d::Layer
{
public:

    // 创建一个 ShopLayer 对象
    static ShopLayer* create(const std::string& shopBgPath, int maxItems);

    // 初始化 ShopLayer
    bool init(const std::string& shopBgPath, int maxItems);

    // 向商店中添加物品
    bool addItem(cocos2d::Sprite* itemSprite);

    // 从商店中移除物品
    void removeItem(cocos2d::Sprite* itemSprite);

    // 隐藏商店界面
    void hideShop(Ref* sender);

    // 获取所有物品的向量
    const cocos2d::Vector<Sprite*>& getItemSprites() const { return itemSprites; }

    // 点击购买按钮的回调函数
    void onBuyButtonClicked(Ref* sender);

    // 鼠标事件监听器与物品的交互
    void setupCombinedMouseListener();

    MenuItemImage* closeButton; // 商店关闭按钮

    cocos2d::Sprite* shopBgSprite; ///< 商店背景精灵
    cocos2d::Sprite* shopSprite;//商店招牌图片

    int gridWidth; ///< 商店格子的宽度（列数）
    int gridHeight; ///< 商店格子的高度（行数）
    int gridSpacing; ///< 商店格子之间的间隔
    float gridStartX; ///< 商店格子的起始 X 坐标
    float gridStartY; ///< 商店格子的起始 Y 坐标

    int maxItems; ///< 商店的最大物品数量
    int currentItems; ///< 当前商店中的物品数量

private:

    cocos2d::Vector<cocos2d::Sprite*> itemSprites; ///< 商店中的物品图标列表
    cocos2d::Label* itemNameLabel; ///< 物品名称标签
    cocos2d::Label* itemPriceLabel; ///< 物品价格标签

    cocos2d::MenuItemImage* buyButton; ///< 购买物品按钮
    cocos2d::Label* buyResultLabel; ///< 购买物品结果标签

    cocos2d::Sprite* itemDetailUI; // 显示物品详情的界面
    cocos2d::Label* itemDetailLabel; // 显示物品详情（名称）的标签
};

#endif // __SHOP_LAYER_H__