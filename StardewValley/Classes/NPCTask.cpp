#include "NPCTask.h"
#include "BackpackManager.h" 
#include "TaskItemManager.h"
#include "TaskItem.h"
#include "NPC.h"
#include "NPCManager.h"
#include "TaskManager.h"
#include <chrono>

// 注释掉 GameTimeManager 的引用
#if 0
#include "GameTimeManager.h" // 假设有一个管理游戏时间的类
#endif

float Clock::getElapsedTime()
{
    static auto startTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - startTime);
    return duration.count() / 1000000.0f; // 返回秒
}

NPCTask::NPCTask(std::string npcName)
    : npcName(npcName), cooldownTime(0.0f), cooldownEndTime(0.0f)
{
    haveTask = true;//初始为有任务
    needItem = nullptr;

    // 随机获取物品唯一标识符
    std::random_device rd;
    std::mt19937 gen(rd());
    int minItemId = 1;
    int maxItemId = 20; // 根据任务物品的唯一标识符范围调整

    int getOnlyNum;
    if (npcName == "Alice") { // 店长
        getOnlyNum = gen() % 4 + 1; // 1-5
    }
    else if (npcName == "Bob") { // 渔夫
        getOnlyNum = gen() % 5 + 6; // 6-10
    }
    else if (npcName == "Mary") { // 农民
        getOnlyNum = gen() % 6 + 11; // 11-16
    }
    else if (npcName == "Annie") { // 牧民
        getOnlyNum = gen() % 4 + 17; // 17-20
    }
    else {
        getOnlyNum = 1;
    }
    
    auto item = TaskItemManager::getInstance()->getTaskItemById(getOnlyNum);
    if (item) {
        needItem = item;
        needItemName = item->getName();
    }

    // 随机获取需要物品数量（1-10）
    std::uniform_int_distribution<> dis(1, 10);
    needItemCount = dis(gen);


    //此处对应每个npc给他们对应的List精灵
    if (npcName == "Alice") {
        taskList = Sprite::create("ui/Alice_task.png");
    }
    else if (npcName == "Bob") {
        taskList = Sprite::create("ui/Bob_task.png");
    }
    else if (npcName == "Mary") {
        taskList = Sprite::create("ui/Mary_task.png");
    }
    else if (npcName == "Annie") {
        taskList = Sprite::create("ui/Annie_task.png");
    }
    else {
        taskList = Sprite::create("ui/default_task.png");
    }
    taskList->retain();
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

void NPCTask::complete()
{
    if (canComplete())
    {
        haveTask = false;
        // 完成任务，增加好感度
        int difficulty = needItemCount;
        int goodwillIncrease = difficulty * 2;
        NPC* npc = NPCManager::getInstance()->getNPCByName(npcName);
        if (npc)
        {
            npc->_relationship.increaseLevel(goodwillIncrease);
        }

        // 检查是否完成特殊任务
        if (npcName == "Alice" && needItemName == "GamA" && needItemCount == 99)
        {
            if (npc)
            {
                npc->_relationship.setSpecialTaskCompleted(true);
            }
        }

        // 设置任务冷却时间
        setCooldown(3.0f);
    }
}

void NPCTask::setCooldown(float cooldownTime)
{
    this->cooldownTime = cooldownTime;
    this->cooldownEndTime = Clock::getElapsedTime() + cooldownTime; // 假设Clock::getElapsedTime()获取当前时间
}

bool NPCTask::isOnCooldown() const
{
    float currentTime = Clock::getElapsedTime();
    return currentTime < cooldownEndTime;
}

float NPCTask::getRemainingCooldown() const
{
    float currentTime = Clock::getElapsedTime();
    if (currentTime < cooldownEndTime)
    {
        return cooldownEndTime - currentTime;
    }
    return 0.0f;
}

void NPCTask::renewTask()
{
    if (isOnCooldown())
    {
        haveTask = false;
    }
    else if (haveTask)
    {
        // 如果已经有任务，则不刷新
        return;
    }
    else
    {
        haveTask = true;
        needItem = nullptr;

        // 随机获取物品唯一标识符
        std::random_device rd;
        std::mt19937 gen(rd());
        int getOnlyNum;
        if (npcName == "Alice") { // 店长
            getOnlyNum = gen() % 5 + 1; // 1-5
        }
        else if (npcName == "Bob") { // 渔夫
            getOnlyNum = gen() % 5 + 6; // 6-10
        }
        else if (npcName == "Mary") { // 农民
            getOnlyNum = gen() % 6 + 11; // 11-17
        }
        else if (npcName == "Annie") { // 牧民
            getOnlyNum = gen() % 4 + 17; // 17-20
        }
        else {
            getOnlyNum = 1;
        }

        auto item = TaskItemManager::getInstance()->getTaskItemById(getOnlyNum);
        if (item) {
            needItem = item;
            needItemName = item->getName();
        }

        // 随机获取需要物品数量（1-10）
        std::uniform_int_distribution<> dis(1, 10);
        needItemCount = dis(gen);
    }
}