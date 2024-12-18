#include "NPCTask.h"
#include "BackpackManager.h" 

// 注释掉 GameTimeManager 的引用
#if 0
#include "GameTimeManager.h" // 假设有一个管理游戏时间的类
#endif

NPCTask::NPCTask(const std::string& npcName, const std::string& description, const std::string& requiredItem, int requiredItemCount)
    : npcName(npcName), description(description), requiredItem(requiredItem), requiredItemCount(requiredItemCount), completed(false), cooldownTime(0.0f), cooldownEndTime(0.0f)
{
}

bool NPCTask::canComplete() const
{
    // 检查背包中是否有足够的所需物品
    auto item = BackpackManager::getInstance()->getItemByName(requiredItem);
    return item != nullptr && item->getCount() >= requiredItemCount;
}

void NPCTask::complete()
{
    if (canComplete())
    {
        // 从背包中移除所需物品
        //BackpackManager::getInstance()->removeItem(requiredItem, requiredItemCount);

        // 标记任务为已完成
        completed = true;

        // 设置任务冷却时间
        setCooldown(60.0f); // 假设冷却时间为 60 秒
    }
}

void NPCTask::setCooldown(float cooldownTime)
{
    this->cooldownTime = cooldownTime;

    // 模拟当前时间
    float currentTime = 0.0f; // 假设当前时间为 0
    this->cooldownEndTime = currentTime + cooldownTime;
}

bool NPCTask::isOnCooldown() const
{
    // 模拟当前时间
    float currentTime = 0.0f; // 假设当前时间为 0
    return currentTime < cooldownEndTime;
}

float NPCTask::getRemainingCooldown() const
{
    // 模拟当前时间
    float currentTime = 0.0f; // 假设当前时间为 0
    if (currentTime < cooldownEndTime)
    {
        return cooldownEndTime - currentTime;
    }
    return 0.0f;
}