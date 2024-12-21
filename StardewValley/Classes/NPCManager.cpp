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
    // ��ʼ�� NPC 1 (Bob)
    NPC* npc1 = new NPC(1, "Bob", "npc_Fisher.png");
    npc1->setDialogue({ "What kind of fish will I catch today?", "I caught a big treasure chest yesterday!", "I want to change to a gold fishing rod." });
    npc1->setLocation(cocos2d::Vec2(400, 200));
    _npcs.push_back(npc1);
    auto npc1Body = PhysicsBody::createBox(npc1->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    npc1Body->setDynamic(false);
    npc1Body->setCollisionBitmask(0x01);
    npc1Body->setContactTestBitmask(0x01);
    npc1->setPhysicsBody(npc1Body);
    npc1->setName("npc1");
    npcBodys.push_back(npc1Body);

    // ��ʼ�� NPC 2 (Alice)
    NPC* npc2 = new NPC(2, "Alice", "npc_Shopper.png");
    npc2->setDialogue({ "Hello, Welcome to my shop!", "bro, I will never deceive you.", "I like gems, can you give them to me?" });
    npc2->setLocation(cocos2d::Vec2(400, 400));
    _npcs.push_back(npc2);
    auto npc2Body = PhysicsBody::createBox(npc2->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    npc2Body->setDynamic(false);
    npc2Body->setCollisionBitmask(0x01);
    npc2Body->setContactTestBitmask(0x01);
    npc2->setPhysicsBody(npc2Body);
    npc2->setName("npc2");
    npcBodys.push_back(npc2Body);

    // ��ʼ�� NPC 3 (Mary)
    NPC* npc3 = new NPC(3, "Mary", "npc_Farmer.png");
    npc3->setDialogue({ "Remember to water and get rid of insects in time!", "You can't grow piglets in farmland!", "Gemstones do not grow in farmland." });
    npc3->setLocation(cocos2d::Vec2(400, 300));
    _npcs.push_back(npc3);
    auto npc3Body = PhysicsBody::createBox(npc3->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    npc3Body->setDynamic(false);
    npc3Body->setCollisionBitmask(0x01);
    npc3Body->setContactTestBitmask(0x01);
    npc3->setPhysicsBody(npc3Body);
    npc3->setName("npc3");
    npcBodys.push_back(npc3Body);

    // ��ʼ�� NPC 4 (Annie)
    NPC* npc4 = new NPC(4, "Annie", "npc_Rancher.png");
    npc4->setDialogue({ "I have the fattest pigs.", "Aha,you're like a cute little pig.", "I love my animals!" });
    npc4->setLocation(cocos2d::Vec2(400, 400));
    _npcs.push_back(npc4);
    auto npc4Body = PhysicsBody::createBox(npc4->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    npc4Body->setDynamic(false);
    npc4Body->setCollisionBitmask(0x01);
    npc4Body->setContactTestBitmask(0x01);
    npc4->setPhysicsBody(npc4Body);
    npc4->setName("npc4");
    npcBodys.push_back(npc4Body);

}

NPCManager::~NPCManager() {
    for (auto npc : _npcs) {
        delete npc;
    }
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

NPC* NPCManager::getNPCByName(const std::string& name)
{
    for (auto npc : _npcs)
    {
        if (npc->_name == name)
            return npc;
    }
    return nullptr;
}