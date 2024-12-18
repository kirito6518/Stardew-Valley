#include "NPCManager.h"
#include "AppDelegate.h"

// 单例实例
NPCManager* NPCManager::instance = nullptr;

// 获取单例实例
NPCManager* NPCManager::getInstance()
{
    if (!instance)
    {
        instance = new NPCManager();
    }
    return instance;
}

//构造函数，在此处初始化所有NPC
NPCManager::NPCManager()
{
    // 创建一个 NPC 对象
    NPC* npc1 = new NPC(1, "Bob", "npc_bob.png");
    npc1->setDialogue("Hello, Gz and Lkc. You are two big god!!!");
    npc1->setRelationship(0);
    npc1->setLocation(cocos2d::Vec2(400, 200)); // 设置 NPC 的初始位置
    _npcs.push_back(npc1); // 将 NPC 添加到 NPC 列表中
    auto npc1Body = PhysicsBody::createBox(npc1->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    npc1Body->setDynamic(false);
    npc1Body->setCollisionBitmask(0x01);
    npc1Body->setContactTestBitmask(0x01);
    npc1->setPhysicsBody(npc1Body);
    npc1->setName("npc1");
    npcBodys.push_back(npc1Body); // 将 NPC物理体 添加到 NPC物理体 列表中

    NPC* npc2 = new NPC(2, "ZY", "npc_zy.png");
    npc2->setDialogue("Hello,Welcome to my shop!!!");
    npc2->setLocation(cocos2d::Vec2(400, 400)); // 设置 NPC 的初始位置
    _npcs.push_back(npc2); // 将 NPC 添加到 NPC 列表中
    auto npc2Body = PhysicsBody::createBox(npc2->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    npc2Body->setDynamic(false);
    npc2Body->setCollisionBitmask(0x01);
    npc2Body->setContactTestBitmask(0x01);
    npc2->setPhysicsBody(npc2Body);
    npc2->setName("npc2");
    npcBodys.push_back(npc2Body); // 将 NPC物理体 添加到 NPC物理体 列表中
}


#if 0 //暂时注释掉任务部分
// 初始化任务列表
void NPCManager::initTasks() {
    // 创建一个任务对象
    NPCTask* task1 = new NPCTask(1, "收集木材", "收集10块木材", "收集", 100);
    _tasks.push_back(task1);
}
#endif

// 每帧更新游戏逻辑
void NPCManager::update(float dt) {
    // 更新游戏逻辑
}

void NPCManager::checkPlayerInteraction(const cocos2d::Vec2& playerPosition) {
    for (auto npc : _npcs) {
        // 计算玩家与 NPC 的距离
        float distance = playerPosition.distance(npc->getLocation());

        // 调试输出距离
        // CCLOG("Player-NPC distance: %f", distance);

        // 检查玩家是否靠近 NPC
        if (distance < 50) { // 假设交互距离为 50 像素
            npc->interactWithPlayer(); // 触发交互
        }
        else {
            npc->removeDialogue(); // 玩家远离 NPC 时移除对话框
        }
    }
}