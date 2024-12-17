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
    backpackLayer = BackpackLayer::create("ui/backpack.png", 30); // ���������㣬10*3����
    backpackLayer->retain(); // ���������㣬��ֹ���ͷ�

    maxItems = 30;           // ���ñ�����Ʒ����
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
bool BackpackManager::addItem(Item* newitem,int amount)
{
    if (!newitem)
    {
        return false;
    }

    if (isFull())
    {
        log("Backpack is full! Cannot add more items.");
        return false;
    }

    // ����Ƿ�������ͬ��Ʒ
    for (auto item : items)
    {
        if (item->getName() == newitem->getName())
        {
            // ������Ʒ����
            item->increaseCount(amount);
            return true;
        }
    }


    newitem->retain();//��ֹ���ڱ�����ʱΪ��

    

    // �����Ʒ������
    items.pushBack(newitem);

    // ��ȡ��Ʒͼ�겢�����û�����
    auto itemSprite = newitem->getIcon();
    itemSprite->setUserData(newitem); // �� Item ��������Ʒͼ�����

    // ����Ʒͼ����ӵ�������
    static_cast<BackpackLayer*>(backpackLayer)->addItem(itemSprite);

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

Item* BackpackManager::getItemByName(const std::string& itemName) {
    
    // ������Ʒ�б�
    for (auto item : items)
    {
        // �����Ʒ�����Ƿ�ƥ��
        if (item->getName() == itemName)
        {
            return item; // ����ƥ�����Ʒʵ��
        }
    }

    return nullptr; // ���û���ҵ�ƥ�����Ʒ������ nullptr
}


