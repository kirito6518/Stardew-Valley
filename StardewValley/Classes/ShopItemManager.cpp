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
    shopItems.pushBack(item);
}



// ��ȡһ�� ShopItem ʵ��
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