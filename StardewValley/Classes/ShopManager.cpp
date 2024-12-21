#include "ShopManager.h"
#include "ShopLayer.h"
#include "ShopItem.h"  
#include "ShopItemManager.h" 
#include "BackpackManager.h"
#include "ItemManager.h"

USING_NS_CC;

// ��ʼ������ʵ��
ShopManager* ShopManager::instance = nullptr;

// ��ȡ����ʵ��
ShopManager* ShopManager::getInstance()
{
    if (!instance)
    {
        instance = new ShopManager();
    }
    return instance;
}

// ���캯��
ShopManager::ShopManager()
{
    shopLayer = ShopLayer::create("ui/backpack.png", 30); // �����̵�㣬10*3����
    shopLayer->retain(); // �����̵�㣬��ֹ���ͷ�

    maxItems = 30;           // �����̵���Ʒ����
    currentItems = 0;        // ��ʼ����ǰ��Ʒ����

    //�˴����������̵��л���ֵ���Ʒ
    // ��һ������Ϊ�����۸񣬵ڶ�������Ϊ����۸�
    ShopItem::create("crops/OnionSeed.png", "Onion\nSeed", 0, 1); // �������
    ShopItem::create("crops/RadishSeed.png", "Radish\nSeed", 0, 1); // ���ܲ�����
    ShopItem::create("crops/PotatoSeed.png", "Potato\nSeed", 0, 1); // ����������
    ShopItem::create("crops/CarrotSeed.png", "Carrot\nSeed", 0, 1); // ���ܲ�����
    ShopItem::create("crops/TurnipSeed.png", "Turnip\nSeed", 0, 1); // ���ܲ�����
    ShopItem::create("crops/SpinachSeed.png", "Spinach\nSeed", 0, 1); // �ײ�����
    

    ShopItem::create("mineral/GemA.png", "GemA", 5, 5);// ���ر�ʯA
    ShopItem::create("mineral/GemB.png", "GemB", 10, 10);// ���ر�ʯB
    ShopItem::create("mineral/GemC.png", "GemC", 15, 15);// ���ر�ʯC
    ShopItem::create("mineral/GemD.png", "GemD", 20, 20);// ���ر�ʯD
    ShopItem::create("mineral/GemE.png", "GemE", 25, 25);// ���ر�ʯE

    ShopItem::create("fish/Bait.png", "Bait", 0, 1); // ����
    ShopItem::create("tool/Fertilizer.png", "Fertilizer", 0, 2); // ����
}

// ��������
ShopManager::~ShopManager()
{
    shopLayer->release(); // �ͷ��̵��
}

// ��ʾ�̵�
void ShopManager::showShop(Node* parent)
{
    if (shopLayer->getParent() == nullptr)
    {
        parent->addChild(shopLayer, 2); // ���̵����ӵ���ǰ����
    }
}

// �����̵�
void ShopManager::hideShop()
{
    shopLayer->removeFromParentAndCleanup(false); // �Ӹ��ڵ��Ƴ�������������
}

// �����Ʒ���̵�
bool ShopManager::addItem(ShopItem* newitem)
{
    if (!newitem)
    {
        return false;
    }

    if (isFull())
    {
        //log("Shop is full! Cannot add more items.");
        return false;
    }


    // ����Ƿ�������ͬ��Ʒ
    for (auto item : items)
    {
        if (item->getName() == newitem->getName())  {return false;}
    }

    newitem->retain(); // ��ֹ���ڱ�����ʱΪ��

    // �����Ʒ���̵�
    items.pushBack(newitem);

    // ��ȡ��Ʒͼ�겢�����û�����
    auto itemSprite = newitem->getIcon();  
    itemSprite->setUserData(newitem); // �� ShopItem ��������Ʒͼ�����

    // ����Ʒͼ����ӵ��̵��
    static_cast<ShopLayer*>(shopLayer)->addItem(itemSprite);

    // ���µ�ǰ��Ʒ����
    currentItems++;
    return true;
}

// �Ƴ���Ʒ
void ShopManager::removeItem(ShopItem* item) 
{
    items.eraseObject(item);
    static_cast<ShopLayer*>(shopLayer)->removeItem(item->getIcon());
    currentItems--;
}

// ����̵��Ƿ�����
bool ShopManager::isFull() const
{
    return currentItems >= maxItems;
}

// ������Ʒ
bool ShopManager::buyItem(ShopItem* item)  // �滻 Item*
{
    // �������ʵ�ֹ����߼�������������Ƿ����㹻�Ľ�ң�Ȼ�����ұ����п۳���Ҳ������Ʒ

    int coinCount = 0;
    std::string toBuyitemName = item->getName();
    Item* coin = BackpackManager::getInstance()->getItemByName("Coin");
    if (coin) {
        coinCount = coin->getCount();
    }
    else {
        return false;
    }

    //��ȡ��Ʒ�۸�
    int Price = ShopItemManager::getInstance()->getShopItem(toBuyitemName)->getBuyingPrice();

    if (coinCount >= Price) {
        coin->decreaseCount(Price);
        Item* getitem = ItemManager::getInstance()->getItem(toBuyitemName);
        BackpackManager::getInstance()->addItem(getitem,1);
        return true;
    }

    return false;
}

// ������Ʒ���ֻ��ʵ��
ShopItem* ShopManager::getItemByName(const std::string& itemName) { 
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