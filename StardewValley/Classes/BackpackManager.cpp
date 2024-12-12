#include "BackpackManager.h"
#include "BackpackLayer.h"
#include "Item.h"

USING_NS_CC;

// 获取单例实例
BackpackManager* BackpackManager::getInstance()
{
    static BackpackManager instance;
    return &instance;
}

// 构造函数
BackpackManager::BackpackManager()
{
    backpackLayer = BackpackLayer::create("ui/backpack.png", 40); // 创建背包层
    backpackLayer->retain(); // 保留背包层，防止被释放

    maxItems = 40;           // 设置背包物品上限
    currentItems = 0;        // 初始化当前物品数量
}

// 析构函数
BackpackManager::~BackpackManager()
{
    backpackLayer->release(); // 释放背包层
}

// 显示背包
void BackpackManager::showBackpack(Node* parent)
{
    if (backpackLayer->getParent() == nullptr)
    {
        parent->addChild(backpackLayer, 2); // 将背包层添加到当前场景
    }
}

// 隐藏背包
void BackpackManager::hideBackpack()
{
    backpackLayer->removeFromParentAndCleanup(false); // 从父节点移除，但保留对象
}

// 添加物品到背包
bool BackpackManager::addItem(const std::string& itemImagePath, const std::string& itemName, ItemCategory category)
{
    if (isFull())
    {
        log("Backpack is full! Cannot add more items.");
        return false;
    }

    // 检查是否已有相同物品
    for (auto item : items)
    {
        if (item->getName() == itemName)
        {
            // 增加物品计数
            item->increaseCount();
            return true;
        }
    }

    // 创建新物品
    auto item = Item::create(itemImagePath, itemName, category);
    if (!item)
    {
        CCLOG("Failed to create item: %s", itemName.c_str());
        return false;
    }

    // 添加物品到背包
    items.pushBack(item);
    static_cast<BackpackLayer*>(backpackLayer)->addItem(item->getIcon());

    // 更新当前物品数量
    currentItems++;
    return true;
}

// 移除物品
void BackpackManager::removeItem(Item* item)
{
    items.eraseObject(item);
    static_cast<BackpackLayer*>(backpackLayer)->removeItem(item->getIcon());
    currentItems--;
}

// 检查背包是否已满
bool BackpackManager::isFull() const
{
    return currentItems >= maxItems;
}