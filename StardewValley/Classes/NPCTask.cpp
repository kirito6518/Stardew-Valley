#include "NPCTask.h"
#include "BackpackManager.h" 
#include "ShopItemManager.h"


// 注释掉 GameTimeManager 的引用
#if 0
#include "GameTimeManager.h" // 假设有一个管理游戏时间的类
#endif

NPCTask::NPCTask(const std::string& npcName, const std::string& description, const std::string& requiredItem, int requiredItemCount)
    : npcName(npcName), description(description), needItemName(needItemName), requiredItemCount(requiredItemCount), cooldownTime(0.0f), cooldownEndTime(0.0f)
{

    //此处写一个随机函数，利用物品唯一标识符随机获得所需物品及所需个数

}

//检测是否能够提交
bool NPCTask::canComplete()
{
    std::string getItem= needItemName;
    getItem.pop_back();
    // 检查背包中是否有足够的所需物品
    auto item = BackpackManager::getInstance()->getItemByName(getItem);
    if (item == nullptr) {
        return false;
    }

    if (item->getCount() < requiredItemCount) {
        return false;
    }

    return true;
}

//完成任务
void NPCTask::complete()
{


    if (canComplete())
    {
        std::string getItem = needItemName;
        getItem.pop_back();
        // 获取背包中的任务物品
        auto item = BackpackManager::getInstance()->getItemByName(getItem);
        // 从背包中减少所需物品
        item->decreaseCount(requiredItemCount);

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

//更新任务状态
void NPCTask::renewTask()
{
    //先判断是否处于任务冷却中
    //若是，设置ShopItem* needItem（所需物品）为 “1”
    //若否，利用物品唯一标识符随机生成所需物品和数量
}