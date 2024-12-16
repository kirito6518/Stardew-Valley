#pragma once
#ifndef NPCMANAGER_H
#define NPCMANAGER_H

#include <vector>
#include "NPC.h"
#include "NPCTask.h"

// NPC管理器类：负责管理NPC、任务和交互逻辑
class NPCManager {
public:
    // 初始化NPC列表
    void initNPCs();
    // 初始化任务列表
    void initTasks();
    // 每帧更新游戏逻辑
    void update(float dt);

    // 检查玩家与NPC的交互
    void checkPlayerInteraction(const cocos2d::Vec2& playerPosition);

    std::vector<NPC*> _npcs; // NPC列表
    std::vector<NPCTask*> _tasks; // 任务列表
private:
  
};

#endif // NPCMANAGER_H