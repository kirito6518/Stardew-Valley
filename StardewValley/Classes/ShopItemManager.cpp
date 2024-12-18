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
    shopItems[itemName] = item;
}

// 移除一个 ShopItem 实例
void ShopItemManager::removeShopItem(const std::string& itemName)
{
    shopItems.erase(itemName);
}

// 获取一个 ShopItem 实例
ShopItem* ShopItemManager::getShopItem(const std::string& itemName)
{
    auto it = shopItems.find(itemName);
    if (it != shopItems.end())
    {
        return it->second;
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