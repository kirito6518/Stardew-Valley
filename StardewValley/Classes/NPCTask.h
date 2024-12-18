#ifndef NPCTASK_H
#define NPCTASK_H

#include "cocos2d.h"

USING_NS_CC;

class NPCTask : public Node {
public:
    NPCTask(const std::string& npcName, const std::string& description, const std::string& requiredItem, int requiredItemCount);

    // 获取 NPC 名称
    std::string getNPCName() const { return npcName; }

    // 获取任务描述
    std::string getDescription() const { return description; }

    // 获取所需物品名称
    std::string getRequiredItem() const { return requiredItem; }

    // 获取所需物品数量
    int getRequiredItemCount() const { return requiredItemCount; }

    // 检查任务是否可以完成
    bool canComplete() const;

    // 完成任务
    void complete();

    // 设置任务冷却时间
    void setCooldown(float cooldownTime);

    // 检查任务是否在冷却中
    bool isOnCooldown() const;

    // 获取任务冷却剩余时间
    float getRemainingCooldown() const;

private:
    std::string npcName;          // NPC 名称
    std::string description;      // 任务描述
    std::string requiredItem;     // 所需物品名称
    int requiredItemCount;        // 所需物品数量
    bool completed;               // 任务是否已完成
    float cooldownTime;           // 任务冷却时间
    float cooldownEndTime;        // 任务冷却结束时间
};

#endif // NPCTASK_H