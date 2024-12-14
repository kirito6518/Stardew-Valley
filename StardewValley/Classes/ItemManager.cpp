#include "ItemManager.h"

USING_NS_CC;

// ��ȡ����ʵ��
ItemManager* ItemManager::getInstance()
{
    static ItemManager instance;
    return &instance;
}

// ���캯��
ItemManager::ItemManager()
{
    // ��ʼ��
}

// ��������
ItemManager::~ItemManager()
{
    // �ͷ�������Ʒ
    for (auto item : items)
    {
        item->release();
    }
}

// ������Ʒ
Item* ItemManager::createItem(const std::string& itemImagePath, const std::string& itemName, ItemCategory category)
{
    auto item = Item::create(itemImagePath, itemName, category);
    if (item)
    {
        item->retain(); // ������Ʒ����ֹ���ͷ�
        items.pushBack(item);
        return item;
    }
    return nullptr;
}

// ��ȡ��Ʒ
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

// �ͷ���Ʒ
void ItemManager::releaseItem(Item* item)
{
    if (item)
    {
        items.eraseObject(item); // ���б����Ƴ���Ʒ
        item->release(); // �ͷ���Ʒ
    }
}