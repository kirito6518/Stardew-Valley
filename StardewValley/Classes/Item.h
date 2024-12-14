#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"

USING_NS_CC;

// 物品分类枚举
enum class ItemCategory
{
    FISHING,   // 钓鱼用
    PLANTING,  // 种植用
    BREEDING,  // 养殖用
    TOOL,      // 工具
    OTHER      // 其他
};

// Item 类，表示一个物品
class Item : public cocos2d::Node
{
public:
    // 创建物品，传入图标路径、名称、分类
    static Item* create(const std::string& itemImagePath, const std::string& itemName, ItemCategory category);

    // 初始化方法
    virtual bool init(const std::string& itemImagePath, const std::string& itemName, ItemCategory category);

    // 获取物品名称（只读）
    const std::string& getName() const { return itemName; }

    // 获取物品图标（只读）
    Sprite* getIcon() const { return itemIcon; }

    // 获取物品分类（只读）
    ItemCategory getCategory() const { return itemCategory; }

    // 获取物品计数
    int getCount() const { return itemCount; }

    // 增加物品计数
    void increaseCount(int amount = 1);

    // 减少物品计数
    void decreaseCount(int amount = 1);

    // 使用物品，返回使用结果
    bool useItem();

private:
    std::string itemName;       // 物品名称
    Sprite*  itemIcon;           // 物品图标
    ItemCategory itemCategory;  // 物品分类
    int itemCount;                    // 物品计数
};

#endif // __ITEM_H__