#ifndef __BACKPACK_MANAGER_H__
#define __BACKPACK_MANAGER_H__

#include "cocos2d.h"
#include "BackpackLayer.h"
#include "Item.h"

USING_NS_CC;

/**
 * @class BackpackManager
 * @brief 背包管理器类，负责管理背包的显示和物品的添加、移除。
 *
 * BackpackManager 是一个单例类，用于管理背包的显示和物品的添加、移除。它负责与 BackpackLayer 进行交互，
 * 并提供添加物品、移除物品、检查背包是否已满等功能。
 */
class BackpackManager
{
public:
    /**
     * @brief 获取 BackpackManager 的单例实例。
     * @return 返回 BackpackManager 的单例实例。
     */
    static BackpackManager* getInstance();

    /**
     * @brief 显示背包界面。
     * @param parent 背包界面要添加到的父节点。
     */
    void showBackpack(cocos2d::Node* parent);

    /**
     * @brief 隐藏背包界面。
     */
    void hideBackpack();

    /**
     * @brief 向背包中添加物品。
     * @param itemImagePath 物品图标的路径。
     * @param itemName 物品的名称。
     * @param category 物品的分类。
     * @return 返回是否成功添加物品。
     */
    bool addItem(const std::string& itemImagePath, const std::string& itemName, ItemCategory category);

    /**
     * @brief 从背包中移除物品。
     * @param item 要移除的物品对象。
     */
    void removeItem(Item* item);

    /**
     * @brief 检查背包是否已满。
     * @return 返回背包是否已满。
     */
    bool isFull() const;

    BackpackLayer* backpackLayer; ///< 背包层对象
private:
    /**
     * @brief 构造函数，初始化 BackpackManager。
     */
    BackpackManager();

    /**
     * @brief 析构函数，释放资源。
     */
    ~BackpackManager();

    cocos2d::Vector<Item*> items; ///< 背包中的物品列表
    int maxItems; ///< 背包的最大物品数量
    int currentItems; ///< 当前背包中的物品数量
};

#endif // __BACKPACK_MANAGER_H__