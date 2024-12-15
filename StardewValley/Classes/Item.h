#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"

/**
 * @enum ItemCategory
 * @brief 物品分类枚举，定义了物品的类型。
 */
enum class ItemCategory
{
    Consumable, ///< 消耗品
    Equipment,  ///< 装备
    Quest       ///< 任务物品
};

/**
 * @class Item
 * @brief 物品类，表示背包中的单个物品。
 *
 * Item 类表示背包中的单个物品，包含了物品的名称、分类、数量、图标等信息。
 * 它提供了增加、减少物品数量的方法，以及使用物品的功能。
 */
class Item : public cocos2d::Node
{
public:
    /**
     * @brief 创建一个 Item 对象。
     * @param itemImagePath 物品图标的路径。
     * @param itemName 物品的名称。
     * @param category 物品的分类。
     * @return 返回创建的 Item 对象，如果创建失败则返回 nullptr。
     */
    static Item* create(const std::string& itemImagePath, const std::string& itemName, ItemCategory category);

    /**
     * @brief 初始化 Item 对象。
     * @param itemImagePath 物品图标的路径。
     * @param itemName 物品的名称。
     * @param category 物品的分类。
     * @return 返回是否初始化成功。
     */
    bool init(const std::string& itemImagePath, const std::string& itemName, ItemCategory category);

    /**
     * @brief 增加物品的数量。
     * @param amount 增加的数量，默认为 1。
     */
    void increaseCount(int amount = 1);

    /**
     * @brief 减少物品的数量。
     * @param amount 减少的数量，默认为 1。
     */
    void decreaseCount(int amount = 1);

    /**
     * @brief 使用物品。
     * @return 返回使用物品是否成功。
     */
    bool useItem(bool success=false);

    /**
     * @brief 获取物品的名称。
     * @return 返回物品的名称。
     */
    const std::string& getName() const { return itemName; }

    /**
     * @brief 获取物品的数量。
     * @return 返回物品的数量。
     */
    int getCount() const { return itemCount; }

    /**
     * @brief 获取物品的图标精灵。
     * @return 返回物品的图标精灵。
     */
    cocos2d::Sprite* getIcon() const { return itemIcon; }

    void update updateCountLabel

private:
    std::string itemName; ///< 物品的名称
    ItemCategory itemCategory; ///< 物品的分类
    int itemCount; ///< 物品的数量
    cocos2d::Label* itemCountLabel; ///< 物品数量标签
    cocos2d::Sprite* itemIcon; ///< 物品的图标精灵
};

#endif // __ITEM_H__