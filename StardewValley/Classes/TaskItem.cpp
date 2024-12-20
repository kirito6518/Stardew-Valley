#include "TaskItem.h"
#include "TaskItemManager.h"

// 创建任务物品
TaskItem* TaskItem::create(const std::string& itemImagePath, const std::string& itemName, int ItemId)
{
    auto taskItem = new (std::nothrow) TaskItem(); // 创建一个新的 TaskItem 对象
    if (taskItem && taskItem->init(itemImagePath, itemName, ItemId)) // 初始化物品
    {
        taskItem->autorelease(); // 自动释放对象
        return taskItem; // 返回创建的物品
    }
    CC_SAFE_DELETE(taskItem); // 如果初始化失败，删除对象
    return nullptr; // 返回空指针
}

// 初始化任务物品
bool TaskItem::init(const std::string& itemImagePath, const std::string& itemName, int ItemId)
{
    if (!Node::init()) // 调用基类的初始化方法
    {
        return false; // 如果基类初始化失败，返回 false
    }

    // 初始化物品属性
    this->itemName = itemName; // 设置物品名称

    //设置物品标识符
    ItemId = ItemId;

    // 创建物品图标
    itemIcon = cocos2d::Sprite::create(itemImagePath);
    if (!itemIcon) // 检查图标是否创建成功
    {
        CCLOG("Failed to load item image: %s", itemImagePath.c_str());
        return false; // 如果图标创建失败，返回 false
    }
    itemIcon->retain(); // 保留 itemIcon

    // 将物品实例注册到 TaskItemManager
    TaskItemManager::getInstance()->addTaskItem(this);

    return true; // 初始化成功，返回 true
}