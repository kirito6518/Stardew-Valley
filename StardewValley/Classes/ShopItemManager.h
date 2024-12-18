#ifndef __SHOP_ITEM_MANAGER_H__
#define __SHOP_ITEM_MANAGER_H__

#include "ShopItem.h"


class ShopItemManager
{
public:
    // ��ȡ����ʵ��
    static ShopItemManager* getInstance();

    // ���һ�� ShopItem ʵ��
    void addShopItem(const std::string& itemName, ShopItem* item);

    // ��ȡһ�� ShopItem ʵ��
    ShopItem* getShopItem(const std::string& itemName);

    // ������� ShopItem ʵ��
    void clearAllShopItems();

    // ���� ShopItemManager ʵ��
    void destroyInstance();

private:
    static ShopItemManager* instance; // ����ʵ��
    cocos2d::Vector<ShopItem*> shopItems; // ���� ShopItem ʵ����
};

#endif // __SHOP_ITEM_MANAGER_H__
