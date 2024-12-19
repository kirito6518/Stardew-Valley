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
    NPC* npc1 = new NPC(1, "Bob", "npc_Fisher.png");
    npc1->setDialogue("What kind of fish will I catch today?");
    //npc1->setRelationship(0);
    npc1->setLocation(cocos2d::Vec2(400, 200)); // ���� NPC �ĳ�ʼλ��
    _npcs.push_back(npc1); // �� NPC ��ӵ� NPC �б���
    auto npc1Body = PhysicsBody::createBox(npc1->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    npc1Body->setDynamic(false);
    npc1Body->setCollisionBitmask(0x01);
    npc1Body->setContactTestBitmask(0x01);
    npc1->setPhysicsBody(npc1Body);
    npc1->setName("npc1");
    npcBodys.push_back(npc1Body); // �� NPC������ ��ӵ� NPC������ �б���

    NPC* npc2 = new NPC(2, "Alice", "npc_Shopper.png");
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

    // ����һ�� NPC ����
    NPC* npc3 = new NPC(3, "John", "npc_Farmer.png");
    npc3->setDialogue("Remember to water and get rid of insects in time!!!");
    npc3->setRelationship(0);
    npc3->setLocation(cocos2d::Vec2(400, 300)); // ���� NPC �ĳ�ʼλ��
    _npcs.push_back(npc3); // �� NPC ��ӵ� NPC �б���
    auto npc3Body = PhysicsBody::createBox(npc3->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    npc3Body->setDynamic(false);
    npc3Body->setCollisionBitmask(0x01);
    npc3Body->setContactTestBitmask(0x01);
    npc3->setPhysicsBody(npc3Body);
    npc3->setName("npc3");
    npcBodys.push_back(npc3Body); // �� NPC������ ��ӵ� NPC������ �б���

    NPC* npc4 = new NPC(4, "Mike", "npc_Shepherd.png");
    npc4->setDialogue("I have the fattest pigs.");
    npc4->setLocation(cocos2d::Vec2(400, 400)); // ���� NPC �ĳ�ʼλ��
    _npcs.push_back(npc4); // �� NPC ��ӵ� NPC �б���
    auto npc4Body = PhysicsBody::createBox(npc4->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    npc4Body->setDynamic(false);
    npc4Body->setCollisionBitmask(0x01);
    npc4Body->setContactTestBitmask(0x01);
    npc4->setPhysicsBody(npc4Body);
    npc4->setName("npc4");
    npcBodys.push_back(npc4Body); // �� NPC������ ��ӵ� NPC������ �б���
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