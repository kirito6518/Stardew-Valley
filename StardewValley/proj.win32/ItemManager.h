#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include "Item.h"
#include "cocos2d.h"
USING_NS_CC;

class ItemManager : public cocos2d::Ref
{
public:
    static ItemManager* getInstance()
    {
        static ItemManager instance;
        return &instance;
    }

    void addItem(Item* item)
    {
        if (item)
        {
            item->retain(); // �������ü���
            items.pushBack(item);
        }
    }

    void removeItem(Item* item)
    {
        if (item)
        {
            items.eraseObject(item);
            item->release(); // �������ü���
        }
    }

    ~ItemManager()
    {
        // �������������ͷ����� Item ʵ��
        for (auto item : items)
        {
            item->release();
        }
    }

private:
    cocos2d::Vector<Item*> items;
};

#endif // __ITEM_MANAGER_H__