#include "ShopItemManager.h"

// ����ʵ��
ShopItemManager* ShopItemManager::instance = nullptr;

// ��ȡ����ʵ��
ShopItemManager* ShopItemManager::getInstance()
{
    if (!instance)
    {
        instance = new ShopItemManager();
    }
    return instance;
}

// ���һ�� ShopItem ʵ��
void ShopItemManager::addShopItem(const std::string& itemName, ShopItem* item)
{
    shopItems[itemName] = item;
}

// �Ƴ�һ�� ShopItem ʵ��
void ShopItemManager::removeShopItem(const std::string& itemName)
{
    shopItems.erase(itemName);
}

// ��ȡһ�� ShopItem ʵ��
ShopItem* ShopItemManager::getShopItem(const std::string& itemName)
{
    auto it = shopItems.find(itemName);
    if (it != shopItems.end())
    {
        return it->second;
    }
    return nullptr;
}

// ������� ShopItem ʵ��
void ShopItemManager::clearAllShopItems()
{
    shopItems.clear();
}

// ���� ShopItemManager ʵ��
void ShopItemManager::destroyInstance()
{
    if (instance)
    {
        delete instance;
        instance = nullptr; // ȷ��ʵ��������Ϊ nullptr�������ظ�ɾ��
    }
}