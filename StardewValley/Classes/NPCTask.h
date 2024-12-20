#ifndef NPCTASK_H
#define NPCTASK_H

#include "cocos2d.h"
#include "TaskItemManager.h"
#include "TaskItem.h"

USING_NS_CC;

class NPCTask : public Node {
public:
    NPCTask(std::string npcName);

    // 获取 NPC 名称
    std::string getNPCName() const { return npcName; }

    // 获取所需物品名称
    std::string getRequiredItem() const { return needItemName; }

    // 获取所需物品数量
    int getRequiredItemCount() const { return needItemCount; }

    // 检查任务是否可以完成
    bool canComplete();

    // 完成任务
    void complete();

    // 设置任务冷却时间
    void setCooldown(float cooldownTime);

    // 检查任务是否在冷却中
    bool isOnCooldown() const;

    // 获取任务冷却剩余时间
    float getRemainingCooldown() const;

    //更新任务状态
    void renewTask();

    //获取该任务是否存在
    bool getHaveTask() {return haveTask;}

    //获取任务所需物品实例
    TaskItem* getNeedItem() { return needItem; }

    //获取list精灵
    Sprite* getIcon() { return taskList; }
private:
    
    TaskItem* needItem;           //所需物品
    Sprite* taskList;             //该角色的任务列表精灵
    bool haveTask;                //判断是否有任务
    std::string npcName;          // NPC 名称
    std::string needItemName;     // 所需物品名称
    int needItemCount;        // 所需物品数量
    float cooldownTime;           // 任务冷却时间
    float cooldownEndTime;        // 任务冷却结束时间
};

#endif // NPCTASK_H