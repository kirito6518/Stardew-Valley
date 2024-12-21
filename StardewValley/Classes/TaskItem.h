#pragma once
#ifndef __TASK_ITEM_H__
#define __TASK_ITEM_H__

#include "cocos2d.h"

/**
 * @class TaskItem
 * @brief 任务物品类，表示任务中的单个物品。
 *
 * TaskItem 类表示任务中的单个物品，包含了物品的名称、描述、图标等信息。
 * 它提供了任务物品的基本操作。
 */
class TaskItem : public cocos2d::Node
{
public:
    // 创建一个 TaskItem 对象
    static TaskItem* create(const std::string& itemImagePath, const std::string& itemName, int ItemId);

    // 初始化 TaskItem 对象
    bool init(const std::string& itemImagePath, const std::string& itemName, int ItemId);

    // 获取物品的名称
    const std::string& getName() const { return itemName; }

    // 获取物品的图标精灵
    cocos2d::Sprite* getIcon() const { return itemIcon; }

    // 获取物品的唯一标识符
    int getTaskId() const { return taskId; }

    int getRarity() const { return rarity; }

    void setRarity(int r) { rarity = r; }

private:

    int taskId; ///< 物品的唯一标识符
    std::string itemName; ///< 物品的名称
    cocos2d::Sprite* itemIcon; ///< 物品的图标精灵
    int rarity; // 物品的稀有度
};

#endif // __TASK_ITEM_H__