#include "ShopItemManager.h"

// 单例实例
ShopItemManager* ShopItemManager::instance = nullptr;

// 获取单例实例
ShopItemManager* ShopItemManager::getInstance()
{
    if (!instance)
    {
        instance = new ShopItemManager();
    }
    return instance;
}

// 添加一个 ShopItem 实例
void ShopItemManager::addShopItem(const std::string& itemName, ShopItem* item)
{
    shopItems.pushBack(item);
}



// 获取一个 ShopItem 实例
ShopItem* ShopItemManager::getShopItem(const std::string& itemName)
{
    ShopItem* findItem = nullptr;
    for (auto item : shopItems) {
        if (item->getName() == itemName)
        {
            findItem = item;
            return findItem;
        }
    }

    return nullptr;
}

// 清空所有 ShopItem 实例
void ShopItemManager::clearAllShopItems()
{
    shopItems.clear();
}

// 销毁 ShopItemManager 实例
void ShopItemManager::destroyInstance()
{
    if (instance)
    {
        delete instance;
        instance = nullptr; // 确保实例被设置为 nullptr，避免重复删除
    }
}