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

    // ����Ʒͼ����ӵ� Item �ڵ���
    this->addChild(itemIcon);

    return true; // ��ʼ���ɹ������� true
}

void Item::increaseCount(int amount)
{
    itemCount += amount;
}

void Item::decreaseCount(int amount)
{
    itemCount -= amount;
    if (itemCount <= 0)
    {
        BackpackManager::getInstance()->removeItem(this);
    }
}

bool Item::useItem()
{
    bool success = true; // ģ��ʹ�óɹ�

    if (success)
    {
        decreaseCount();
    }

    return success;
}


/*�ݶ�*/
void Item::onItemClicked(Ref* sender)
{
    CCLOG("Item Name: %s, Count: %d", itemName.c_str(), itemCount);
}
/*�ݶ�*/