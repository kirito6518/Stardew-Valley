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
    backpackLayer = BackpackLayer::create("ui/backpack.png", 30); // 创建背包层，10*3格子
    backpackLayer->retain(); // 保留背包层，防止被释放

    maxItems = 30;           // 设置背包物品上限
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
bool BackpackManager::addItem(Item* newitem,int amount)
{
    if (!newitem)
    {
        return false;
    }

    if (isFull())
    {
        log("Backpack is full! Cannot add more items.");
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

    newitem->retain();//防止其在被销毁时为空

    // 添加物品到背包
    items.pushBack(newitem);

    // 获取物品图标并设置用户数据
    auto itemSprite = newitem->getIcon();
    itemSprite->setUserData(newitem); // 将 Item 对象与物品图标关联

    // 将物品图标添加到背包层
    static_cast<BackpackLayer*>(backpackLayer)->addItem(itemSprite);

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

Item* BackpackManager::getItemByName(const std::string& itemName) {
    
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


