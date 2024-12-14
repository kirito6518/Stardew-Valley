#ifndef __ITEM_MANAGER_H__
#define __ITEM_MANAGER_H__

#include "cocos2d.h"
#include "Item.h"

USING_NS_CC;

class ItemManager
{
public:
    // 获取单例实例
    static ItemManager* getInstance();

    // 创建物品并存储
    Item* createItem(const std::string& itemImagePath, const std::string& itemName, ItemCategory category);

    // 获取物品
    Item* getItemByName(const std::string& itemName);

    // 获取所有物品
    const cocos2d::Vector<Item*>& getAllItems() const { return items; }

    // 释放物品
    void releaseItem(Item* item);

private:
    ItemManager();
    ~ItemManager();

    cocos2d::Vector<Item*> items; // 存储所有物品
};

#endif // __ITEM_MANAGER_H__