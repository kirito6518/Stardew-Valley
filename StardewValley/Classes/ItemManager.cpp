#include "ItemManager.h"

// ��ʼ������ʵ��
ItemManager* ItemManager::instance = nullptr;

// ��ȡ����ʵ��
ItemManager* ItemManager::getInstance()
{
    if (!instance)
    {
        instance = new ItemManager();
    }
    return instance;
}

// ���һ�� Item ʵ��
void ItemManager::addItem(const std::string& itemName, Item* item)
{
    items[itemName] = item;
}

// �Ƴ�һ�� Item ʵ��
void ItemManager::removeItem(const std::string& itemName)
{
    items.erase(itemName);
}

// ��ȡһ�� Item ʵ��
Item* ItemManager::getItem(const std::string& itemName)
{
    auto it = items.find(itemName);
    if (it != items.end())
    {
        return it->second;
    }
    return nullptr;
}

// ������� Item ʵ��
void ItemManager::clearAllItems()
{
    items.clear();
}

//���ItemManager
void ItemManager::destroyInstance()
{
    if (instance)
    {
        delete instance;
        instance = nullptr; // ��ʵ��ָ����Ϊ nullptr����ֹҰָ��
    }
}

// ����������Ʒ�б�
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