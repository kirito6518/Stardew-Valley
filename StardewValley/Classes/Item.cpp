#include "Item.h"
#include "BackpackManager.h"

USING_NS_CC;

// ������Ʒ
Item* Item::create(const std::string& itemImagePath, const std::string& itemName, ItemCategory category)
{
    auto item = new (std::nothrow) Item(); // ����һ���µ� Item ����
    if (item && item->init(itemImagePath, itemName, category)) // ��ʼ����Ʒ
    {
        item->autorelease(); // �Զ��ͷŶ���
        return item; // ���ش�������Ʒ
    }
    CC_SAFE_DELETE(item); // �����ʼ��ʧ�ܣ�ɾ������
    return nullptr; // ���ؿ�ָ��
}

// ��ʼ����Ʒ
bool Item::init(const std::string& itemImagePath, const std::string& itemName, ItemCategory category)
{
    if (!Node::init()) // ���û���ĳ�ʼ������
    {
        return false; // ��������ʼ��ʧ�ܣ����� false
    }

    // ��ʼ����Ʒ����
    this->itemName = itemName; // ������Ʒ����
    this->itemCategory = category; // ������Ʒ����
    this->itemCount = 1; // ��ʼ����Ʒ����Ϊ 1

    // ������Ʒͼ��
    itemIcon = Sprite::create(itemImagePath);
    if (!itemIcon) // ���ͼ���Ƿ񴴽��ɹ�
    {
        CCLOG("Failed to load item image: %s", itemImagePath.c_str());
        return false; // ���ͼ�괴��ʧ�ܣ����� false
    }

    std::string countStr = std::to_string(itemCount);
    itemCountLabel = Label::createWithSystemFont(countStr, "Arial", 24);
    itemCountLabel->setAnchorPoint(Vec2(0, 1));
    if (itemIcon) {
        auto itemPos=itemIcon->getPosition();
        itemCountLabel->setPosition(Vec2(itemPos.x, itemPos.y - 80));
        this->addChild(itemCountLabel, 4);
    }

    return true; // ��ʼ���ɹ������� true
}

// ������Ʒ����
void Item::increaseCount(int amount)
{
    itemCount += amount; // ������Ʒ����
}

// ������Ʒ����
void Item::decreaseCount(int amount)
{
    itemCount -= amount; // ������Ʒ����
    if (itemCount <= 0) // �������Ϊ 0
    {
        BackpackManager::getInstance()->removeItem(this); // ���� BackpackManager �� removeItem �����Ƴ���Ʒ
    }
}

// ʹ����Ʒ������ʹ�ý��,Ĭ��ʹ��ʧ��
bool Item::useItem(bool success)
{
 
    if (success) // ���ʹ�óɹ�
    {
        decreaseCount(); // ������Ʒ����
    }

    return success; // ����ʹ�ý��
}