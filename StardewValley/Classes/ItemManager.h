#ifndef __ITEM_MANAGER_H__
#define __ITEM_MANAGER_H__

#include "cocos2d.h"
#include "Item.h"

USING_NS_CC;

class ItemManager
{
public:
    // ��ȡ����ʵ��
    static ItemManager* getInstance();

    // ������Ʒ���洢
    Item* createItem(const std::string& itemImagePath, const std::string& itemName, ItemCategory category);

    // ��ȡ��Ʒ
    Item* getItemByName(const std::string& itemName);

    // ��ȡ������Ʒ
    const cocos2d::Vector<Item*>& getAllItems() const { return items; }

    // �ͷ���Ʒ
    void releaseItem(Item* item);

private:
    ItemManager();
    ~ItemManager();

    cocos2d::Vector<Item*> items; // �洢������Ʒ
};

#endif // __ITEM_MANAGER_H__