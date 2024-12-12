#include "BackpackManager.h"

USING_NS_CC;

BackpackManager* BackpackManager::getInstance()
{
    static BackpackManager instance; // 静态实例，确保全局唯一
    return &instance;
}

/*此处暂定*/
BackpackManager::BackpackManager()
{
    // 初始化背包层
    backpackLayer = BackpackLayer::create("backpack.png", 40); // 背包背景图片为 "backpack.png"，上限为 40 个物品
    backpackLayer->retain(); // 保留背包层，防止被释放

    // 初始化背包状态
    maxItems = 40;
    currentItems = 0;
}
/*此处暂定*/

BackpackManager::~BackpackManager()
{
    backpackLayer->release(); // 释放背包层
}

void BackpackManager::showBackpack(Node* parent)
{
    if (backpackLayer->getParent() == nullptr)
    {

        parent->addChild(backpackLayer,2); // 将背包层添加到当前场景
    }
}

void BackpackManager::hideBackpack()
{
    backpackLayer->removeFromParentAndCleanup(false); // 从父节点移除，但保留对象
}

bool BackpackManager::addItem(const std::string& itemImagePath)
{
    if (isFull())
    {
        log("Backpack is full! Cannot add more items.");
        return false;
    }

    // 调用背包层的添加物品方法
    static_cast<BackpackLayer*>(backpackLayer)->addItem(itemImagePath);

    // 更新当前物品数量
    currentItems++;
    return true;
}

bool BackpackManager::isFull() const
{
    return currentItems >= maxItems;
}