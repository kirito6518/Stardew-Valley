#ifndef __ITEM_MANAGER_H__
#define __ITEM_MANAGER_H__

#include "Item.h"
USING_NS_CC;

class ItemManager
{
public:
    // 获取单例实例
    static ItemManager* getInstance();

    // 添加一个 Item 实例
    void addItem(const std::string& itemName, Item* item);


    // 获取一个 Item 实例
    Item* getItem(const std::string& itemName);

    //清除ItemManager
    void destroyInstance();


    // 清空所有 Item 实例
    void clearAllItems();


private:

    static ItemManager* instance; // 单例实例
    cocos2d::Vector<Item*> items; ///< 物品列表
};

#endif // __ITEM_MANAGER_H__
