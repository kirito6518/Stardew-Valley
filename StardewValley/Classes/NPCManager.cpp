#include "NPCManager.h"
#include "AppDelegate.h"

void NPCManager::initNPCs() {
    // 创建一个 NPC 对象
    NPC* npc1 = new NPC(1, "Bob", "npc_bob.png");
    npc1->setDialogue("Hello, Gz and Lkc. You are two big god!!!");
    npc1->setRelationship(0);
    npc1->setLocation(cocos2d::Vec2(200, 200)); // 设置 NPC 的初始位置
    _npcs.push_back(npc1); // 将 NPC 添加到 NPC 列表中
}

// 初始化任务列表
void NPCManager::initTasks() {
    // 创建一个任务对象
    NPCTask* task1 = new NPCTask(1, "收集木材", "收集10块木材", "收集", 100);
    _tasks.push_back(task1);
}

// 每帧更新游戏逻辑
void NPCManager::update(float dt) {
    // 更新游戏逻辑
}

void NPCManager::checkPlayerInteraction(const cocos2d::Vec2& playerPosition) {
    for (auto npc : _npcs) {
        // 计算玩家与 NPC 的距离
        float distance = playerPosition.distance(npc->getLocation());

        // 调试输出距离
        CCLOG("Player-NPC distance: %f", distance);

        // 检查玩家是否靠近 NPC
        if (distance < 50) { // 假设交互距离为 50 像素
            npc->interactWithPlayer(); // 触发交互
        }
        else {
            npc->removeDialogue(); // 玩家远离 NPC 时移除对话框
        }
    }
}