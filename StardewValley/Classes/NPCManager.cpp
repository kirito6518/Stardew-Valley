#include "NPCManager.h"
#include "AppDelegate.h"

// ����ʵ��
NPCManager* NPCManager::instance = nullptr;

// ��ȡ����ʵ��
NPCManager* NPCManager::getInstance()
{
    if (!instance)
    {
        instance = new NPCManager();
    }
    return instance;
}

//���캯�����ڴ˴���ʼ������NPC
NPCManager::NPCManager()
{
    // ����һ�� NPC ����
    NPC* npc1 = new NPC(1, "Bob", "npc_bob.png");
    npc1->setDialogue("Hello, Gz and Lkc. You are two big god!!!");
    npc1->setRelationship(0);
    npc1->setLocation(cocos2d::Vec2(400, 200)); // ���� NPC �ĳ�ʼλ��
    _npcs.push_back(npc1); // �� NPC ��ӵ� NPC �б���
    auto npc1Body = PhysicsBody::createBox(npc1->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    npc1Body->setDynamic(false);
    npc1Body->setCollisionBitmask(0x01);
    npc1Body->setContactTestBitmask(0x01);
    npc1->setPhysicsBody(npc1Body);
    npc1->setName("npc1");
    npcBodys.push_back(npc1Body); // �� NPC������ ��ӵ� NPC������ �б���

    NPC* npc2 = new NPC(2, "ZY", "npc_zy.png");
    npc2->setDialogue("Hello,Welcome to my shop!!!");
    npc2->setLocation(cocos2d::Vec2(400, 400)); // ���� NPC �ĳ�ʼλ��
    _npcs.push_back(npc2); // �� NPC ��ӵ� NPC �б���
    auto npc2Body = PhysicsBody::createBox(npc2->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    npc2Body->setDynamic(false);
    npc2Body->setCollisionBitmask(0x01);
    npc2Body->setContactTestBitmask(0x01);
    npc2->setPhysicsBody(npc2Body);
    npc2->setName("npc2");
    npcBodys.push_back(npc2Body); // �� NPC������ ��ӵ� NPC������ �б���
}


#if 0 //��ʱע�͵����񲿷�
// ��ʼ�������б�
void NPCManager::initTasks() {
    // ����һ���������
    NPCTask* task1 = new NPCTask(1, "�ռ�ľ��", "�ռ�10��ľ��", "�ռ�", 100);
    _tasks.push_back(task1);
}
#endif

// ÿ֡������Ϸ�߼�
void NPCManager::update(float dt) {
    // ������Ϸ�߼�
}

void NPCManager::checkPlayerInteraction(const cocos2d::Vec2& playerPosition) {
    for (auto npc : _npcs) {
        // ��������� NPC �ľ���
        float distance = playerPosition.distance(npc->getLocation());

        // �����������
        // CCLOG("Player-NPC distance: %f", distance);

        // �������Ƿ񿿽� NPC
        if (distance < 50) { // ���轻������Ϊ 50 ����
            npc->interactWithPlayer(); // ��������
        }
        else {
            npc->removeDialogue(); // ���Զ�� NPC ʱ�Ƴ��Ի���
        }
    }
}