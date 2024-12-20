#pragma once
#ifndef NPCMANAGER_H
#define NPCMANAGER_H

#include <vector>
#include "NPC.h"
#include "NPCTask.h"
#include <cocos2d.h>
#include "chipmunk.h"

USING_NS_CC;

// NPC�������ࣺ�������NPC������ͽ����߼�
class NPCManager {
public:

    // ��ʼ�������б�
    //void initTasks();
    
    // ÿ֡������Ϸ�߼�
    void update(float dt);

    // ��������NPC�Ľ���
    void checkPlayerInteraction(const cocos2d::Vec2& playerPosition);

    // ��ȡ����ʵ��
    static NPCManager* getInstance();
 
    std::vector<NPC*> _npcs; // NPC�б�
    std::vector<PhysicsBody*> npcBodys; // npc��������
    //std::vector<NPCTask*> _tasks; // �����б�

    NPC* getNPCByName(const std::string& name);
private:

    //���캯������ʼ��NPC
    NPCManager::NPCManager();
    NPCManager::~NPCManager();
    static NPCManager* instance; // ����ʵ��
  
};

#endif // NPCMANAGER_