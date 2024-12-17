#include "ItemManager.h"

// 初始化单例实例
ItemManager* ItemManager::instance = nullptr;

// 获取单例实例
ItemManager* ItemManager::getInstance()
{
    if (!instance)
    {
        instance = new ItemManager();
    }
    return instance;
}

// 添加一个 Item 实例
void ItemManager::addItem(const std::string& itemName, Item* item)
{
    items[itemName] = item;
}

// 移除一个 Item 实例
void ItemManager::removeItem(const std::string& itemName)
{
    items.erase(itemName);
}

// 获取一个 Item 实例
Item* ItemManager::getItem(const std::string& itemName)
{
    auto it = items.find(itemName);
    if (it != items.end())
    {
        return it->second;
    }
    return nullptr;
}

// 清空所有 Item 实例
void ItemManager::clearAllItems()
{
    items.clear();
}

//清除ItemManager
void ItemManager::destroyInstance()
{
    if (instance)
    {
        delete instance;
        instance = nullptr; // 将实例指针置为 nullptr，防止野指针
    }
}

// 设置售卖物品列表
void ItemManager::setSellableItems(const std::unordered_set<std::string>& sellableItemNames)
{
    for (const auto& itemName : sellableItemNames)
    {
        if (items.find(itemName) != items.end())
        {
            items[itemName]->setItemType(ItemType::Sellable);
        }
    }
}