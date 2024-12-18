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
    items.pushBack(item);
}


// 获取一个 Item 实例
Item* ItemManager::getItem(const std::string& itemName)
{
    Item* findItem=nullptr;
    for (auto item : items) {
        if (item->getName() == itemName)
        {
            findItem = item;
            return findItem;
        }
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

