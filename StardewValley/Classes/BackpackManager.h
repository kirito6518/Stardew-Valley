#ifndef __BACKPACK_MANAGER_H__
#define __BACKPACK_MANAGER_H__

#include "cocos2d.h"
#include "BackpackLayer.h"
#include "Item.h"

class BackpackManager
{
public:
    static BackpackManager* getInstance();

    void showBackpack(cocos2d::Node* parent);
    void hideBackpack();

    // 添加物品到背包
    bool addItem(const std::string& itemImagePath, const std::string& itemName, ItemCategory category);

    // 移除物品
    void removeItem(Item* item);

    // 检查背包是否已满
    bool isFull() const;

private:
    BackpackManager();
    ~BackpackManager();

    cocos2d::Layer* backpackLayer; // 背包层
    int maxItems;                  // 背包物品上限
    int currentItems;              // 当前背包中的物品数量

    // 物品容器
    cocos2d::Vector<Item*> items;
};

#endif // __BACKPACK_MANAGER_H__