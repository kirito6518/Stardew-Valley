#include "BackpackManager.h"
#include "BackpackLayer.h"
#include "Item.h"

USING_NS_CC;

// ��ȡ����ʵ��
BackpackManager* BackpackManager::getInstance()
{
    static BackpackManager instance;
    return &instance;
}

// ���캯��
BackpackManager::BackpackManager()
{
    backpackLayer = BackpackLayer::create("ui/backpack.png", 40); // ����������
    backpackLayer->retain(); // ���������㣬��ֹ���ͷ�

    maxItems = 40;           // ���ñ�����Ʒ����
    currentItems = 0;        // ��ʼ����ǰ��Ʒ����
}

// ��������
BackpackManager::~BackpackManager()
{
    backpackLayer->release(); // �ͷű�����
}

// ��ʾ����
void BackpackManager::showBackpack(Node* parent)
{
    if (backpackLayer->getParent() == nullptr)
    {
        parent->addChild(backpackLayer, 2); // ����������ӵ���ǰ����
    }
}

// ���ر���
void BackpackManager::hideBackpack()
{
    backpackLayer->removeFromParentAndCleanup(false); // �Ӹ��ڵ��Ƴ�������������
}

// �����Ʒ������
bool BackpackManager::addItem(const std::string& itemImagePath, const std::string& itemName, ItemCategory category)
{
    if (isFull())
    {
        log("Backpack is full! Cannot add more items.");
        return false;
    }

    // ����Ƿ�������ͬ��Ʒ
    for (auto item : items)
    {
        if (item->getName() == itemName)
        {
            // ������Ʒ����
            item->increaseCount();
            return true;
        }
    }

    // ��������Ʒ
    auto item = Item::create(itemImagePath, itemName, category);
    if (!item)
    {
        CCLOG("Failed to create item: %s", itemName.c_str());
        return false;
    }

    // �����Ʒ������
    items.pushBack(item);
    static_cast<BackpackLayer*>(backpackLayer)->addItem(item->getIcon());

    // ���µ�ǰ��Ʒ����
    currentItems++;
    return true;
}

// �Ƴ���Ʒ
void BackpackManager::removeItem(Item* item)
{
    items.eraseObject(item);
    static_cast<BackpackLayer*>(backpackLayer)->removeItem(item->getIcon());
    currentItems--;
}

// ��鱳���Ƿ�����
bool BackpackManager::isFull() const
{
    return currentItems >= maxItems;
}