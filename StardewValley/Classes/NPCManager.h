#pragma once
#ifndef NPCMANAGER_H
#define NPCMANAGER_H

#include <vector>
#include "NPC.h"
#include "NPCTask.h"
#include <cocos2d.h>
#include "chipmunk.h"

USING_NS_CC;

// NPC管理器类：负责管理NPC、任务和交互逻辑
class NPCManager {
public:

    // 初始化任务列表
    //void initTasks();
    
    // 每帧更新游戏逻辑
    void update(float dt);

    // 检查玩家与NPC的交互
    void checkPlayerInteraction(const cocos2d::Vec2& playerPosition);

    // 获取单例实例
    static NPCManager* getInstance();
 
    std::vector<NPC*> _npcs; // NPC列表
    std::vector<PhysicsBody*> npcBodys; // npc的物理体
    //std::vector<NPCTask*> _tasks; // 任务列表

    NPC* getNPCByName(const std::string& name);
private:

    //构造函数，初始化NPC
    NPCManager::NPCManager();
    NPCManager::~NPCManager();
    static NPCManager* instance; // 单例实例
  
};

#endif // NPCMANAGER_