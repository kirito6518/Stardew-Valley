#include "ShopManager.h"
#include "ShopLayer.h"
#include "Item.h"

USING_NS_CC;

// 获取单例实例
ShopManager* ShopManager::getInstance()
{
    static ShopManager instance;
    return &instance;
}

// 构造函数
ShopManager::ShopManager()
{
    shopLayer = ShopLayer::create("ui/shop.png", 30); // 创建商店层，10*3格子
    shopLayer->retain(); // 保留商店层，防止被释放

    maxItems = 30;           // 设置商店物品上限
    currentItems = 0;        // 初始化当前物品数量
}

// 析构函数
ShopManager::~ShopManager()
{
    shopLayer->release(); // 释放商店层
}

// 显示商店
void ShopManager::showShop(Node* parent)
{
    if (shopLayer->getParent() == nullptr)
    {
        parent->addChild(shopLayer, 2); // 将商店层添加到当前场景
    }
}

// 隐藏商店
void ShopManager::hideShop()
{
    shopLayer->removeFromParentAndCleanup(false); // 从父节点移除，但保留对象
}

// 添加物品到商店
bool ShopManager::addItem(Item* newitem, int amount)
{
    if (!newitem)
    {
        return false;
    }

    if (isFull())
    {
        log("Shop is full! Cannot add more items.");
        return false;
    }

    bool ifHaveSame = false;

    // 检查是否已有相同物品
    for (auto item : items)
    {
        if (item->getName() == newitem->getName())
        {
            ifHaveSame = true;
            // 增加物品计数
            newitem->increaseCount(amount);
            return true;
        }
    }

    if (!ifHaveSame) {
        // 增加物品计数
        newitem->increaseCount(amount);
    }

    newitem->retain(); // 防止其在被销毁时为空

    // 添加物品到商店
    items.pushBack(newitem);

    // 获取物品图标并设置用户数据
    auto itemSprite = newitem->getIcon();
    itemSprite->setUserData(newitem); // 将 Item 对象与物品图标关联

    // 将物品图标添加到商店层
    static_cast<ShopLayer*>(shopLayer)->addItem(itemSprite);

    // 更新当前物品数量
    currentItems++;
    return true;
}

// 移除物品
void ShopManager::removeItem(Item* item)
{
    items.eraseObject(item);
    static_cast<ShopLayer*>(shopLayer)->removeItem(item->getIcon());
    currentItems--;
}

// 检查商店是否已满
bool ShopManager::isFull() const
{
    return currentItems >= maxItems;
}

// 购买物品
bool ShopManager::buyItem(Item* item)
{
    // 这里可以实现购买逻辑，例如检查玩家是否有足够的金币，然后从玩家背包中扣除金币并添加物品
    // 具体实现由你来完成
    return true;
}

// 根据物品名字获得实例
Item* ShopManager::getItemByName(const std::string& itemName) {
    // 遍历物品列表
    for (auto item : items)
    {
        // 检查物品名称是否匹配
        if (item->getName() == itemName)
        {
            return item; // 返回匹配的物品实例
        }
    }

    return nullptr; // 如果没有找到匹配的物品，返回 nullptr
}