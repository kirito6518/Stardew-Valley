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
    items.pushBack(item);
}


// ��ȡһ�� Item ʵ��
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

