#ifndef __ITEM_MANAGER_H__
#define __ITEM_MANAGER_H__

#include "cocos2d.h"
#include "Item.h"

/**
 * @class ItemManager
 * @brief 物品管理器类，负责创建和管理物品对象。
 *
 * ItemManager 是一个单例类，用于创建和管理物品对象。它提供了创建物品、获取物品、释放物品等功能。
 */
class ItemManager
{
public:
    /**
     * @brief 获取 ItemManager 的单例实例。
     * @return 返回 ItemManager 的单例实例。
     */
    static ItemManager* getInstance();

    /**
     * @brief 创建一个物品对象。
     * @param itemImagePath 物品图标的路径。
     * @param itemName 物品的名称。
     * @param category 物品的分类。
     * @return 返回创建的物品对象，如果创建失败则返回 nullptr。
     */
    Item* createItem(const std::string& itemImagePath, const std::string& itemName, ItemCategory category);

    /**
     * @brief 根据名称获取物品对象。
     * @param itemName 物品的名称。
     * @return 返回对应的物品对象，如果未找到则返回 nullptr。
     */
    Item* getItemByName(const std::string& itemName);

    /**
     * @brief 释放物品对象。
     * @param item 要释放的物品对象。
     */
    void releaseItem(Item* item);

private:
    /**
     * @brief 构造函数，初始化 ItemManager。
     */
    ItemManager();

    /**
     * @brief 析构函数，释放所有物品对象。
     */
    ~ItemManager();

    cocos2d::Vector<Item*> items; ///< 物品对象列表
};

#endif // __ITEM_MANAGER_H__