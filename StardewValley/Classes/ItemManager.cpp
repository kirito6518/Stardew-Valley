#include "ItemManager.h"

USING_NS_CC;

// 获取单例实例
ItemManager* ItemManager::getInstance()
{
    static ItemManager instance;
    return &instance;
}

// 构造函数
ItemManager::ItemManager()
{
    // 初始化
}

// 析构函数
ItemManager::~ItemManager()
{
    // 释放所有物品
    for (auto item : items)
    {
        item->release();
    }
}

// 创建物品
Item* ItemManager::createItem(const std::string& itemImagePath, const std::string& itemName, ItemCategory category)
{
    auto item = Item::create(itemImagePath, itemName, category);
    if (item)
    {
        item->retain(); // 保留物品，防止被释放
        items.pushBack(item);
        return item;
    }
    return nullptr;
}

// 获取物品
Item* ItemManager::getItemByName(const std::string& itemName)
{
    for (auto item : items)
    {
        if (item->getName() == itemName)
        {
            return item;
        }
    }
    return nullptr;
}

// 释放物品
void ItemManager::releaseItem(Item* item)
{
    if (item)
    {
        items.eraseObject(item); // 从列表中移除物品
        item->release(); // 释放物品
    }
}