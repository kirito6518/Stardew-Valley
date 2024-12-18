﻿#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include <functional>

//物品分类枚举，定义了物品的类型。
enum class ItemCategory
{
    Tool,         // 工具
    Fish,         // 鱼
    Seed,         // 种子
    Crops,        // 作物产品
    AnimalProduct,// 动物产品（生肉和鸡蛋）
    Food,         // 食物
    Consumable,   // 消耗品
    Equipment,    // 装备
    Quest,        // 任务物品
    Mine          // 矿物     
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

    // 定义一个回调函数类型，用于处理使用逻辑
    using UseItemCallback = std::function<bool()>;

    // 设置自定义的 useItem 回调函数
    void setUseItemCallback(UseItemCallback callback)
    {
        useItemCallback = callback;
    }



    //创建一个 Item 对象
    static Item* create(const std::string& itemImagePath, const std::string& itemName, ItemCategory category,
                           int sellingPrice=0, int buyingPrice=0,int amount=0);

    //初始化 Item 对象
    bool init(const std::string& itemImagePath, const std::string& itemName, ItemCategory category, 
              int sellingPrice, int buyingPrice,int amount);

    //增加物品的数量。
    void increaseCount(int amount = 1);

    //减少物品的数量
    void decreaseCount(int amount = 1);

    //使用物品逻辑
    bool useItem();

    //清空物品
    void clearItem();
 
    // 使用物品函数，接受一个回调函数来处理使用逻辑
    bool useItem(int count, UseItemCallback callback);

    //获取物品的名称
    const std::string& getName() const { return itemName; }

    //获取物品的数量。
    int getCount() const { return itemCount; }

    //获取物品卖出价格
    int getsellingPrice() const { return sellingPrice; }

    //获取物品买入价格
    int getbuyingPrice() const { return buyingPrice; }

    //获取物品分类
    ItemCategory getitemCategory() const { return itemCategory; }

    // 获取物品的图标精灵
    cocos2d::Sprite* getIcon() const { return itemIcon; }

    void updateCountLabel();

private:
    UseItemCallback useItemCallback; // 保存自定义的 useItem 回调函数

    std::string itemName; ///< 物品的名称
    ItemCategory itemCategory; ///< 物品的分类

    int sellingPrice;//物品卖出价格
    int buyingPrice;//物品买入价格
    int itemCount; ///< 物品的数量
    cocos2d::Label* itemCountLabel; ///< 物品数量标签
    cocos2d::Sprite* itemIcon; ///< 物品的图标精灵



};

#endif // __ITEM_H__