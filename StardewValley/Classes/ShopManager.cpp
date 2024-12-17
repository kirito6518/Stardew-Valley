#include "ShopManager.h"
#include "ShopLayer.h"
#include "Item.h"
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
    addItem(ItemManager::getInstance()->getItem("Onion\nSeed"));
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
bool ShopManager::addItem(Item* newitem)
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

    bool ifHaveSame = false;


    newitem->retain(); // ��ֹ���ڱ�����ʱΪ��

    // �����Ʒ���̵�
    items.pushBack(newitem);

    // ��ȡ��Ʒͼ�겢�����û�����
    auto itemSprite = newitem->getIcon();
    itemSprite->setUserData(newitem); // �� Item ��������Ʒͼ�����

    // ����Ʒͼ����ӵ��̵��
    static_cast<ShopLayer*>(shopLayer)->addItem(itemSprite);

    // ���µ�ǰ��Ʒ����
    currentItems++;
    return true;
}

// �Ƴ���Ʒ
void ShopManager::removeItem(Item* item)
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
bool ShopManager::buyItem(Item* item)
{
    // �������ʵ�ֹ����߼�������������Ƿ����㹻�Ľ�ң�Ȼ�����ұ����п۳���Ҳ������Ʒ
    // ����ʵ�����������

    int coinCount =0;
    Item* coin = BackpackManager::getInstance()->getItemByName("Coin");
    if (coin) {
        coinCount = coin->getCount();
    }
    else {
        return false;
    }
    int Price = ItemManager::getInstance()->getItem(item->getName())->getbuyingPrice();
    if (coinCount >= Price) {

        coin->decreaseCount(Price);
        return true;
    }

    return true;
}

// ������Ʒ���ֻ��ʵ��
Item* ShopManager::getItemByName(const std::string& itemName) {
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