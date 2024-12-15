#include "Item.h"
#include "BackpackManager.h"

USING_NS_CC;

// 创建物品
Item* Item::create(const std::string& itemImagePath, const std::string& itemName, ItemCategory category)
{
    auto item = new (std::nothrow) Item(); // 创建一个新的 Item 对象
    if (item && item->init(itemImagePath, itemName, category)) // 初始化物品
    {
        item->autorelease(); // 自动释放对象
        return item; // 返回创建的物品
    }
    CC_SAFE_DELETE(item); // 如果初始化失败，删除对象
    return nullptr; // 返回空指针
}

// 初始化物品
bool Item::init(const std::string& itemImagePath, const std::string& itemName, ItemCategory category)
{
    if (!Node::init()) // 调用基类的初始化方法
    {
        return false; // 如果基类初始化失败，返回 false
    }

    // 初始化物品属性
    this->itemName = itemName; // 设置物品名称
    this->itemCategory = category; // 设置物品分类
    this->itemCount = 1; // 初始化物品计数为 1

    // 创建物品图标
    itemIcon = Sprite::create(itemImagePath);
    if (!itemIcon) // 检查图标是否创建成功
    {
        CCLOG("Failed to load item image: %s", itemImagePath.c_str());
        return false; // 如果图标创建失败，返回 false
    }

    // 创建数量标签
    itemCountLabel = Label::createWithTTF(std::to_string(itemCount), "fonts/Gen.ttf", 25);
    itemCountLabel->setAnchorPoint(Vec2(0.5, 0.5)); // 设置标签的锚点为中心
    itemCountLabel->setPosition(Vec2(itemIcon->getContentSize().width / 2 + 25, 20));// 设置标签在物品图标下方
    itemIcon->addChild(itemCountLabel, 3); // 将标签添加到物品图标中

#if 0
    std::string countStr = std::to_string(itemCount);
    itemCountLabel = Label::createWithSystemFont(countStr, "Arial", 24);
    itemCountLabel->setAnchorPoint(Vec2(0, 1));
    if (itemIcon) {
        auto itemPos=itemIcon->getPosition();
        itemCountLabel->setPosition(Vec2(itemIcon->getContentSize().width / 2, -20));
        this->addChild(itemCountLabel, 4);
    }
#endif
    return true; // 初始化成功，返回 true
}

void Item::increaseCount(int amount)
{
    itemCount += amount; // 增加物品计数
    updateCountLabel(); // 更新数量标签
}

void Item::decreaseCount(int amount)
{
    itemCount -= amount; // 减少物品计数
    if (itemCount <= 0) // 如果计数为 0
    {
        BackpackManager::getInstance()->removeItem(this); // 调用 BackpackManager 的 removeItem 方法移除物品
    }
    else
    {
        updateCountLabel(); // 更新数量标签
    }
}

// 使用物品，返回使用结果,默认使用失败
bool Item::useItem(bool success)
{
 
    if (success) // 如果使用成功
    {
        decreaseCount(); // 减少物品计数
    }

    return success; // 返回使用结果
}

void Item::updateCountLabel()
{
    if (itemCountLabel)
    {
        itemCountLabel->setString(std::to_string(itemCount));
    }
}