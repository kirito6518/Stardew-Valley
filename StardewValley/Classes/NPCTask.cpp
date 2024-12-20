#include "NPCTask.h"
#include "BackpackManager.h" 
#include "TaskItemManager.h"
#include "TaskItem.h"


// 注释掉 GameTimeManager 的引用
#if 0
#include "GameTimeManager.h" // 假设有一个管理游戏时间的类
#endif

NPCTask::NPCTask(std::string npcName)
    : npcName(npcName), cooldownTime(0.0f), cooldownEndTime(0.0f)
{
    haveTask = true;//初始为有任务
    needItem = nullptr;

    int getOnlyNum = 1;//此处应通过随机获取物品唯一标识符，暂时先写死
    auto item = TaskItemManager::getInstance()->getTaskItemById(getOnlyNum);
    if (item) {
        needItem = item;
        needItemName = item->getName();
    }
    
    //此处写一个随机函数,随机获得所需物品个数,此处暂时先写死
    needItemCount = 1;

    //此处对应每个npc给他们对应的List精灵
    if (npcName == "Alice") {
        taskList = Sprite::create("ui/Alice_task.png");
        taskList->retain();
    }
    else if (npcName == "Bob") {

    }
    else {//此处为健壮性加上
        taskList = Sprite::create("ui/Alice_task.png");
        taskList->retain();
    }
}

//检测是否能够提交
bool NPCTask::canComplete()
{

    // 检查背包中是否有足够的所需物品
    auto item = BackpackManager::getInstance()->getItemByName(needItemName);
    if (item == nullptr) {
        return false;
    }

    if (item->getCount() < needItemCount) {
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
        item->decreaseCount(needItemCount);

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
    //若是，设置haveItem为 false
    //若否，设置haveItem为ture ,并利用物品唯一标识符随机生成所需物品和数量
    //例如
    haveTask = true;//根据是否冷却判断此处是否需要更改
    needItem = nullptr;

    int getOnlyNum = 1;//此处应通过随机获取物品唯一标识符，暂时先写死
    auto item = TaskItemManager::getInstance()->getTaskItemById(getOnlyNum);
    if (item) {
        needItem = item;
        needItemName = item->getName();
    }

    //此处写一个随机函数,随机获得所需物品个数,此处暂时先写死
    needItemCount = 1;
}