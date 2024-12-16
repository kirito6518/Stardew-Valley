#include "Item.h"
#include "BackpackManager.h"

USING_NS_CC;



Item::~Item()
{
    if (itemIcon)
    {
        itemIcon->removeFromParent(); // ȷ�� itemIcon �Ӹ��ڵ����Ƴ�

    }
}


// ������Ʒ
Item* Item::create(const std::string& itemImagePath, const std::string& itemName, ItemCategory category,int amount)
{
    auto item = new (std::nothrow) Item(); // ����һ���µ� Item ����
    if (item && item->init(itemImagePath, itemName, category, amount)) // ��ʼ����Ʒ
    {
        item->autorelease(); // �Զ��ͷŶ���
        return item; // ���ش�������Ʒ
    }
    CC_SAFE_DELETE(item); // �����ʼ��ʧ�ܣ�ɾ������
    return nullptr; // ���ؿ�ָ��
}

// ��ʼ����Ʒ
bool Item::init(const std::string& itemImagePath, const std::string& itemName, ItemCategory category,int amount)
{
    if (!Node::init()) // ���û���ĳ�ʼ������
    {
        return false; // ��������ʼ��ʧ�ܣ����� false
    }

    // ��ʼ����Ʒ����
    this->itemName = itemName; // ������Ʒ����
    this->itemCategory = category; // ������Ʒ����
    this->itemCount = amount; // ��ʼ����Ʒ����

    // ������Ʒͼ��
    itemIcon = Sprite::create(itemImagePath);
    if (!itemIcon) // ���ͼ���Ƿ񴴽��ɹ�
    {
        CCLOG("Failed to load item image: %s", itemImagePath.c_str());
        return false; // ���ͼ�괴��ʧ�ܣ����� false
    }

    // ����������ǩ
    itemCountLabel = Label::createWithTTF(std::to_string(itemCount), "fonts/Gen.ttf", 25);
    itemCountLabel->setAnchorPoint(Vec2(0.5, 0.5)); // ���ñ�ǩ��ê��Ϊ����
    itemCountLabel->setPosition(Vec2(itemIcon->getContentSize().width / 2 + 25, 20));// ���ñ�ǩ����Ʒͼ���·�
    itemIcon->addChild(itemCountLabel, 3); // ����ǩ��ӵ���Ʒͼ����

    return true; // ��ʼ���ɹ������� true
}

void Item::increaseCount(int amount)
{
    itemCount += amount; // ������Ʒ����
    updateCountLabel(); // ����������ǩ
}

void Item::decreaseCount(int amount)
{
    itemCount -= amount; // ������Ʒ����
    if (itemCount <= 0) // �������Ϊ 0
    {
        itemCount = 0;
        BackpackManager::getInstance()->removeItem(this); // ���� BackpackManager �� removeItem �����Ƴ���Ʒ
        
    }
    else
    {
        updateCountLabel(); // ����������ǩ
    }
}

// �޸� useItem ����������һ���ص�����������ʹ���߼�
bool Item::useItem()
{
    if (useItemCallback)
    {
        return useItemCallback(); // �����ⲿ�ṩ�Ļص�����
    }
    else
    {
        // Ĭ��ʵ�֣�ʹ��ʧ��
        return false;
    }
}


void Item::updateCountLabel()
{
    if (itemCountLabel)
    {
        itemCountLabel->setString(std::to_string(itemCount));
    }
}