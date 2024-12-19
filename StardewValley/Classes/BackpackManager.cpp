#include "BackpackManager.h"
#include "BackpackLayer.h"
#include "Item.h"

USING_NS_CC;

// ��ʼ������ʵ��
BackpackManager* BackpackManager::instance = nullptr;

// ��ȡ����ʵ��
BackpackManager* BackpackManager::getInstance()
{

    if (!instance)
    {
        instance = new BackpackManager();
    }
    return instance;
}

// ���캯��
BackpackManager::BackpackManager()
{
    backpackLayer = BackpackLayer::create("ui/backpack.png", 30); // ���������㣬10*3����
    backpackLayer->retain(); // ���������㣬��ֹ���ͷ�

    maxItems = 30;           // ���ñ�����Ʒ����
    currentItems = 0;        // ��ʼ����ǰ��Ʒ����
    

    //�˴�ͳһ�������п��ܷ��뱳������Ʒ,
    // ��һ������Ϊ�����۸񣬵ڶ�������Ϊ����۸񣬵���������Ϊ��ʼ������ȱʡΪ0��

    Item::create("tool/Coin.png", "Coin", ItemCategory::Tool, 1, 1);// ���ؽ�ң�����������
    Item::create("tool/FishingGear.png", "Fishing\nGear", ItemCategory::Tool, 1, 1);// ���ص���ͣ�����������
    Item::create("tool/Fork.png", "Fork", ItemCategory::Tool, 1, 1);// ���ز��ӣ�����������
    Item::create("tool/Pickaxe.png", "Pickaxe", ItemCategory::Tool, 1, 1);// ���ظ��ӣ�����������
    Item::create("tool/WaterPot.png", "WaterPot", ItemCategory::Tool, 1, 1);// ����ˮƿ������������
    Item::create("tool/AntiInsect.png", "Anti\nInsect", ItemCategory::Tool, 0, 0);// ���س��湤�ߣ�����������
    Item::create("tool/Fertilizer.png", "Fertilizer", ItemCategory::Tool, 0, 0);// ���ط��ϣ�����������

    Item::create("mineral/GemA.png", "GemA", ItemCategory::Mine, 5, 5);// ���ر�ʯA
    Item::create("mineral/GemB.png", "GemB", ItemCategory::Mine, 10, 10);// ���ر�ʯB
    Item::create("mineral/GemC.png", "GemC", ItemCategory::Mine, 15, 15);// ���ر�ʯC
    Item::create("mineral/GemD.png", "GemD", ItemCategory::Mine, 20, 20);// ���ر�ʯD
    Item::create("mineral/GemE.png", "GemE", ItemCategory::Mine, 25, 25);// ���ر�ʯE

    Item::create("fish/FishA.png", "FishA", ItemCategory::Fish, 2, 2);// ������A
    Item::create("fish/FishB.png", "FishB", ItemCategory::Fish, 2, 2);// ������B
    Item::create("fish/FishC.png", "FishC", ItemCategory::Fish, 2, 2);// ������C
    Item::create("fish/FishD.png", "FishD", ItemCategory::Fish, 2, 2);// ������D
    Item::create("fish/FishE.png", "FishE", ItemCategory::Fish, 2, 2);// ������E
    Item::create("fish/Bait.png", "Bait", ItemCategory::Tool, 0, 1);// ���ض��ϣ�����������
    Item::create("fish/Box.png", "Box", ItemCategory::Tool, 0, 0);// �������ӣ�����������

    Item::create("crops/Onion.png", "Onion", ItemCategory::Crops, 1, 2);//������й�ʵ
    Item::create("crops/OnionSeed.png", "Onion\nSeed", ItemCategory::Seed, 0, 1);// �����������

    Item::create("animal/Pork.png", "Pork", ItemCategory::AnimalProduct, 2, 3);//��������
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
        parent->addChild(backpackLayer, 4); // ����������ӵ���ǰ����
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

    bool ifHaveSame = false;

    // ����Ƿ�������ͬ��Ʒ
    for (auto item : items)
    {

        if ( newitem->getName() == item->getName() )
        {
            ifHaveSame = true;
            // ������Ʒ����
            newitem->increaseCount(amount);
            return true;
        }
    }

    if (!ifHaveSame) {
        // ������Ʒ����
        newitem->increaseCount(amount);
        
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

//���BackpackManager
void BackpackManager::destroyInstance()
{
    if (instance)
    {
        delete instance;
        instance = nullptr; // ��ʵ��ָ����Ϊ nullptr����ֹҰָ��
    }
}


