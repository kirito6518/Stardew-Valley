#include "ShopItem.h"
#include "ShopItemManager.h"
#include "BackpackManager.h"
USING_NS_CC;

// �����̵���Ʒ
ShopItem* ShopItem::create(const std::string& itemImagePath, const std::string& itemName, int sellingPrice, int buyingPrice)
{
    auto shopItem = new (std::nothrow) ShopItem(); // ����һ���µ� ShopItem ����
    if (shopItem && shopItem->init(itemImagePath, itemName, sellingPrice,buyingPrice)) // ��ʼ����Ʒ
    {
        shopItem->autorelease(); // �Զ��ͷŶ���
        return shopItem; // ���ش�������Ʒ
    }
    CC_SAFE_DELETE(shopItem); // �����ʼ��ʧ�ܣ�ɾ������
    return nullptr; // ���ؿ�ָ��
}

// ��ʼ���̵���Ʒ
bool ShopItem::init(const std::string& itemImagePath, const std::string& itemName, int sellingPrice, int buyingPrice)
{
    if (!Node::init()) // ���û���ĳ�ʼ������
    {
        return false; // ��������ʼ��ʧ�ܣ����� false
    }

    // ��ʼ����Ʒ����
    this->itemName = itemName; // ������Ʒ����
    this->sellingPrice = sellingPrice; // ������Ʒ�����۸�
    this->buyingPrice = buyingPrice;//������Ʒ����۸�

    // ������Ʒͼ��
    itemIcon = Sprite::create(itemImagePath);
    if (!itemIcon) // ���ͼ���Ƿ񴴽��ɹ�
    {
        CCLOG("Failed to load item image: %s", itemImagePath.c_str());
        return false; // ���ͼ�괴��ʧ�ܣ����� false
    }
    itemIcon->retain(); // ���� itemIcon

    // ����Ʒʵ��ע�ᵽ ShopItemManager
    ShopItemManager::getInstance()->addShopItem(itemName, this);

    return true; // ��ʼ���ɹ������� true
}

