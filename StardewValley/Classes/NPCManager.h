#pragma once
#ifndef NPCMANAGER_H
#define NPCMANAGER_H

#include <vector>
#include "NPC.h"
#include "NPCTask.h"

// NPC�������ࣺ�������NPC������ͽ����߼�
class NPCManager {
public:
    // ��ʼ��NPC�б�
    void initNPCs();
    // ��ʼ�������б�
    void initTasks();
    // ÿ֡������Ϸ�߼�
    void update(float dt);

    // ��������NPC�Ľ���
    void checkPlayerInteraction(const cocos2d::Vec2& playerPosition);

    std::vector<NPC*> _npcs; // NPC�б�
    std::vector<NPCTask*> _tasks; // �����б�
private:
  
};

#endif // NPCMANAGER_H