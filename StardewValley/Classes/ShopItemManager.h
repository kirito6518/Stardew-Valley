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

    // �Ƴ�һ�� ShopItem ʵ��
    void removeShopItem(const std::string& itemName);

    // ��ȡһ�� ShopItem ʵ��
    ShopItem* getShopItem(const std::string& itemName);

    // ������� ShopItem ʵ��
    void clearAllShopItems();

    // ���� ShopItemManager ʵ��
    void destroyInstance();

private:
    static ShopItemManager* instance; // ����ʵ��
    std::unordered_map<std::string, ShopItem*> shopItems; // ���� ShopItem ʵ����ӳ��
};

#endif // __SHOP_ITEM_MANAGER_H__
