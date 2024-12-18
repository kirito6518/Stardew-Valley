#ifndef __SHOP_ITEM_MANAGER_H__
#define __SHOP_ITEM_MANAGER_H__

#include "ShopItem.h"


class ShopItemManager
{
public:
    // 获取单例实例
    static ShopItemManager* getInstance();

    // 添加一个 ShopItem 实例
    void addShopItem(const std::string& itemName, ShopItem* item);

    // 获取一个 ShopItem 实例
    ShopItem* getShopItem(const std::string& itemName);

    // 清空所有 ShopItem 实例
    void clearAllShopItems();

    // 销毁 ShopItemManager 实例
    void destroyInstance();

private:
    static ShopItemManager* instance; // 单例实例
    cocos2d::Vector<ShopItem*> shopItems; // 所有 ShopItem 实例的
};

#endif // __SHOP_ITEM_MANAGER_H__
