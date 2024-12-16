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
            item->retain(); // 增加引用计数
            items.pushBack(item);
        }
    }

    void removeItem(Item* item)
    {
        if (item)
        {
            items.eraseObject(item);
            item->release(); // 减少引用计数
        }
    }

    ~ItemManager()
    {
        // 在析构函数中释放所有 Item 实例
        for (auto item : items)
        {
            item->release();
        }
    }

private:
    cocos2d::Vector<Item*> items;
};

#endif // __ITEM_MANAGER_H__