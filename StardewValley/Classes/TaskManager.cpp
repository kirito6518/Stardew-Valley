#include "TaskManager.h"
#include "TaskLayer.h"
#include "TaskItem.h"
#include "TaskItemManager.h"
#include "NPCTask.h"

USING_NS_CC;

// ��ʼ������ʵ��
TaskManager* TaskManager::instance = nullptr;

// ��ȡ����ʵ��
TaskManager* TaskManager::getInstance()
{
    if (!instance)
    {
        instance = new(std::nothrow) TaskManager();
    }
    return instance;
}

// ���캯��
TaskManager::TaskManager()
{
    taskLayer = TaskLayer::create();
    taskLayer->retain();

    //���л����������������Ʒ���ڴ˴����أ���ò�Ҫ�����ִ����з�����Ʒ
    // ��ʼ��������Ʒ������ϡ�ж�
    TaskItem* gemA = TaskItem::create("mineral/GemA.png", "GemA", 1);
    gemA->setRarity(1);
    TaskItemManager::getInstance()->addTaskItem(gemA);

    TaskItem* gemB = TaskItem::create("mineral/GemB.png", "GemB", 2);
    gemB->setRarity(2);
    TaskItemManager::getInstance()->addTaskItem(gemB);

    TaskItem* gemC = TaskItem::create("mineral/GemC.png", "GemC", 3);
    gemC->setRarity(3);
    TaskItemManager::getInstance()->addTaskItem(gemC);

    TaskItem* gemD = TaskItem::create("mineral/GemD.png", "GemD", 4);
    gemD->setRarity(4);
    TaskItemManager::getInstance()->addTaskItem(gemD);

    TaskItem* gemE = TaskItem::create("mineral/GemE.png", "GemE", 5);
    gemE->setRarity(5);
    TaskItemManager::getInstance()->addTaskItem(gemE);

    // ���࣬ϡ�ж�2
    TaskItem* fishA = TaskItem::create("fish/FishA.png", "FishA", 6);
    fishA->setRarity(2);
    TaskItemManager::getInstance()->addTaskItem(fishA);

    TaskItem* fishB = TaskItem::create("fish/FishB.png", "FishB", 7);
    fishB->setRarity(2);
    TaskItemManager::getInstance()->addTaskItem(fishB);

    TaskItem* fishC = TaskItem::create("fish/FishC.png", "FishC", 8);
    fishC->setRarity(2);
    TaskItemManager::getInstance()->addTaskItem(fishC);

    TaskItem* fishD = TaskItem::create("fish/FishD.png", "FishD", 9);
    fishD->setRarity(2);
    TaskItemManager::getInstance()->addTaskItem(fishD);

    TaskItem* fishE = TaskItem::create("fish/FishE.png", "FishE", 10);
    fishE->setRarity(2);
    TaskItemManager::getInstance()->addTaskItem(fishE);

    // ũ����
    TaskItem* onion = TaskItem::create("crops/Onion.png", "Onion", 11);
    onion->setRarity(4);
    TaskItemManager::getInstance()->addTaskItem(onion);

    TaskItem* potato = TaskItem::create("crops/Potato.png", "Potato", 12);
    potato->setRarity(3);
    TaskItemManager::getInstance()->addTaskItem(potato);

    TaskItem* carrot = TaskItem::create("crops/Carrot.png", "Carrot", 13);
    carrot->setRarity(2);
    TaskItemManager::getInstance()->addTaskItem(carrot);

    TaskItem* turnip = TaskItem::create("crops/Turnip.png", "Turnip", 14);
    turnip->setRarity(1);
    TaskItemManager::getInstance()->addTaskItem(turnip);

    TaskItem* radish = TaskItem::create("crops/Radish.png", "Radish", 15);
    radish->setRarity(2);
    TaskItemManager::getInstance()->addTaskItem(radish);

    TaskItem* spinach = TaskItem::create("crops/Spinach.png", "Spinach", 16);
    spinach->setRarity(3);
    TaskItemManager::getInstance()->addTaskItem(spinach);

    // �����Ʒ��ϡ�ж�2
    TaskItem* pork = TaskItem::create("animal/Pork.png", "Pork", 17);
    pork->setRarity(2);
    TaskItemManager::getInstance()->addTaskItem(pork);

    TaskItem* beef = TaskItem::create("animal/Beef.png", "Beef", 18);
    beef->setRarity(2);
    TaskItemManager::getInstance()->addTaskItem(beef);

    TaskItem* mutton = TaskItem::create("animal/Mutton.png", "Mutton", 19);
    mutton->setRarity(2);
    TaskItemManager::getInstance()->addTaskItem(mutton);

    TaskItem* chicken = TaskItem::create("animal/Chicken.png", "Chicken", 20);
    chicken->setRarity(2);
    TaskItemManager::getInstance()->addTaskItem(chicken);

    // ��ʼ���ĸ�NPC������
    // �곤
    NPCTask* shopOwner = new NPCTask("Alice");
    addTaskList(shopOwner);
    tasks.pushBack(shopOwner);

    // ���
    NPCTask* fisher = new NPCTask("Bob");
    addTaskList(fisher);
    tasks.pushBack(fisher);

    // ũ��
    NPCTask* farmer = new NPCTask("Mary");
    addTaskList(farmer);
    tasks.pushBack(farmer);

    // ����
    NPCTask* rancher = new NPCTask("Annie");
    addTaskList(rancher);
    tasks.pushBack(rancher);
    
}

// ��������
TaskManager::~TaskManager()
{
    taskLayer->release(); // �ͷ������б��
}

// ��ʾ�����б�
void TaskManager::showTaskList(Node* parent)
{
    if (taskLayer->getParent() == nullptr)
    {
        parent->addChild(taskLayer, 4); // �������б����ӵ���ǰ����
    }
}

// ���������б�
void TaskManager::hideTaskList()
{
    taskLayer->removeFromParentAndCleanup(false); // �Ӹ��ڵ��Ƴ�������������
}

//��������б�
bool TaskManager::addTaskList(NPCTask* task)
{
    if (!task) {
        return false;
    }

    if (!task->getHaveTask()) {
        return false;
    }

    task->retain(); // ��ֹ���ڱ�����ʱΪ��


    // ��ȡ�б�ʵ���������û�����
    auto listSprite = task->getIcon();
    listSprite->setUserData(task);// �� task �������б�ͼ�����

    // ���б�ͼ����ӵ������
    static_cast<TaskLayer*>(taskLayer)->addList(listSprite);

    return true;
}


// ��������״̬
void TaskManager::renewTask()
{
    for (auto task : tasks) {
        task->renewTask();
        if (!task->getHaveTask()) {
            static_cast<TaskLayer*>(taskLayer)->removeItem(task->getIcon());
        }
        else {
            // ��ȡ�б�ʵ���������û�����
            auto listSprite = task->getIcon();
            if (!listSprite->getParent()) {//ȷ��listSpriteû�и��ڵ�
                listSprite->setUserData(task);// �� task �������б�ͼ�����
                // ���б�ͼ����ӵ������
                static_cast<TaskLayer*>(taskLayer)->addList(listSprite);
            }         
        }

    }
}
