#ifndef __SHOP_ITEM_H__
#define __SHOP_ITEM_H__

#include "cocos2d.h"


/**
 * @class ShopItem
 * @brief 商店物品类，表示商店中的单个物品。
 *
 * ShopItem 类表示商店中的单个物品，包含了物品的名称、价格、图标等信息。
 * 它提供了购买物品的功能。
 */
class ShopItem : public cocos2d::Node
{
public:

    // 创建一个 ShopItem 对象
    static ShopItem* create(const std::string& itemImagePath, const std::string& itemName, int sellingPrice, int buyingPrice);

    // 初始化 ShopItem 对象
    bool init(const std::string& itemImagePath, const std::string& itemName, int sellingPrice, int buyingPrice);

    // 获取物品的名称
    const std::string& getName() const { return itemName; }

    // 获取物品的购买价格
    int getBuyingPrice() const { return buyingPrice; }

    // 获取物品的图标精灵
    cocos2d::Sprite* getIcon() const { return itemIcon; }

    

private:

    std::string itemName; ///< 物品的名称
    cocos2d::Sprite* itemIcon; ///< 物品的图标精灵
    cocos2d::Label* itemCountLabel; ///< 物品数量标签，在商店中，所有物品数量都为1
    int sellingPrice;///< 物品的卖出价格
    int buyingPrice;///< 物品的买入价格
};

#endif // __SHOP_ITEM_H__