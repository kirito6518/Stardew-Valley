#include "NPCManager.h"
#include "AppDelegate.h"

void NPCManager::initNPCs() {
    // ����һ�� NPC ����
    NPC* npc1 = new NPC(1, "Bob", "npc_bob.png");
    npc1->setDialogue("Hello, Gz and Lkc. You are two big god!!!");
    npc1->setRelationship(0);
    npc1->setLocation(cocos2d::Vec2(200, 200)); // ���� NPC �ĳ�ʼλ��
    _npcs.push_back(npc1); // �� NPC ��ӵ� NPC �б���
}

// ��ʼ�������б�
void NPCManager::initTasks() {
    // ����һ���������
    NPCTask* task1 = new NPCTask(1, "�ռ�ľ��", "�ռ�10��ľ��", "�ռ�", 100);
    _tasks.push_back(task1);
}

// ÿ֡������Ϸ�߼�
void NPCManager::update(float dt) {
    // ������Ϸ�߼�
}

void NPCManager::checkPlayerInteraction(const cocos2d::Vec2& playerPosition) {
    for (auto npc : _npcs) {
        // ��������� NPC �ľ���
        float distance = playerPosition.distance(npc->getLocation());

        // �����������
        CCLOG("Player-NPC distance: %f", distance);

        // �������Ƿ񿿽� NPC
        if (distance < 50) { // ���轻������Ϊ 50 ����
            npc->interactWithPlayer(); // ��������
        }
        else {
            npc->removeDialogue(); // ���Զ�� NPC ʱ�Ƴ��Ի���
        }
    }
}