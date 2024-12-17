#ifndef __SHOP_MANAGER_H__
#define __SHOP_MANAGER_H__

#include "cocos2d.h"
#include "ShopLayer.h"
#include "Item.h"

USING_NS_CC;

/**
 * @class ShopManager
 * @brief 商店管理器类，负责管理商店的显示和物品的添加、移除。
 *
 * ShopManager 是一个单例类，用于管理商店的显示和物品的添加、移除。它负责与 ShopLayer 进行交互，
 * 并提供添加物品、移除物品、检查商店是否已满等功能。
 */
class ShopManager : public cocos2d::Layer
{
public:
    /**
     * @brief 获取 ShopManager 的单例实例。
     * @return 返回 ShopManager 的单例实例。
     */
    static ShopManager* getInstance();

    /**
     * @brief 显示商店界面。
     * @param parent 商店界面要添加到的父节点。
     */
    void showShop(cocos2d::Node* parent);

    /**
     * @brief 隐藏商店界面。
     */
    void hideShop();

    /**
     * @brief 向商店中添加物品。
     * @param item 要添加的物品对象。
     * @param amount 添加物品的数量，默认为1
     * @return 返回是否成功添加物品。
     */
    bool addItem(Item* item, int amount = 1);

    /**
     * @brief 从商店中移除物品。
     * @param item 要移除的物品对象。
     */
    void removeItem(Item* item);

    /**
     * @brief 检查商店是否已满。
     * @return 返回商店是否已满。
     */
    bool isFull() const;

    /**
     * @brief 购买物品。
     * @param item 要购买的物品对象。
     * @return 返回是否成功购买物品。
     */
    bool buyItem(Item* item);

    // 获取所有物品的向量
    const cocos2d::Vector<Item*>& getItems() { return items; }

    // 根据物品名字获得实例
    Item* getItemByName(const std::string& itemName);

    ShopLayer* shopLayer; ///< 商店层对象

    Scene* mainMap;

private:

    static ShopManager* instance; // 单例实例

    /**
     * @brief 构造函数，初始化 ShopManager。
     */
    ShopManager();

    /**
     * @brief 析构函数，释放资源。
     */
    ~ShopManager();

    cocos2d::Vector<Item*> items; ///< 商店中的物品列表
    int maxItems; ///< 商店的最大物品数量
    int currentItems; ///< 当前商店中的物品数量
};

#endif // __SHOP_MANAGER_H__