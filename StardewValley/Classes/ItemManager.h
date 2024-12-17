#ifndef __ITEM_MANAGER_H__
#define __ITEM_MANAGER_H__

#include "Item.h"
#include <unordered_map>
#include <unordered_set>

class ItemManager
{
public:
    // 获取单例实例
    static ItemManager* getInstance();

    // 添加一个 Item 实例
    void addItem(const std::string& itemName, Item* item);

    // 移除一个 Item 实例
    void removeItem(const std::string& itemName);

    // 获取一个 Item 实例
    Item* getItem(const std::string& itemName);

    //清除ItemManager
    void destroyInstance();


    // 清空所有 Item 实例
    void clearAllItems();

    // 设置售卖物品列表
    void setSellableItems(const std::unordered_set<std::string>& sellableItemNames);

private:
    static ItemManager* instance; // 单例实例
    std::unordered_map<std::string, Item*> items; // 全局物品实例映射
};

#endif // __ITEM_MANAGER_H__
