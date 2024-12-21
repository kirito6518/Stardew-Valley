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
    // ��ʼ��������Ʒ
    TaskItem::create("mineral/GemA.png", "GemA", 1);
    TaskItem::create("mineral/GemB.png", "GemB", 2);
    TaskItem::create("mineral/GemC.png", "GemC", 3);
    TaskItem::create("mineral/GemD.png", "GemD", 4);
    TaskItem::create("mineral/GemE.png", "GemE", 5);
    TaskItem::create("fish/FishA.png", "FishA", 6);
    TaskItem::create("fish/FishB.png", "FishB", 7);
    TaskItem::create("fish/FishC.png", "FishC", 8);
    TaskItem::create("fish/FishD.png", "FishD", 9);
    TaskItem::create("fish/FishE.png", "FishE", 10);
    TaskItem::create("crops/Onion.png", "Onion", 11);
    TaskItem::create("crops/Potato.png", "Potato", 12);
    TaskItem::create("crops/Carrot.png", "Carrot", 13);
    TaskItem::create("crops/Turnip.png", "Turnip", 14);
    TaskItem::create("crops/Potato.png", "Radish", 15);
    TaskItem::create("crops/Spinach.png", "Spinach", 16);
    TaskItem::create("animal/Pork.png", "Pork", 17);
    TaskItem::create("animal/Beef.png", "Beef", 18);
    TaskItem::create("animal/Mutton.png", "Muttun", 19);
    TaskItem::create("animal/Chicken.png", "Chicken", 20);

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
