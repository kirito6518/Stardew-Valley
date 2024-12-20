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
        instance = new TaskManager();
    }
    return instance;
}

// ���캯��
TaskManager::TaskManager()
{
    taskLayer = TaskLayer::create();
    taskLayer->retain(); // ���������б�㣬��ֹ���ͷ�


    //���л����������������Ʒ���ڴ˴�����
    //��һ��������Ϊ��Ψһ��ʶ��
    TaskItem::create("crops/Onion.png", "Onion",1);


    //�ĸ�npc����ĳ�ʼ���ڴ˼���
    NPCTask* Alice=new NPCTask("Alice");
    tasks.pushBack(Alice);
    //��������....

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
bool TaskManager::addTaskLIst(NPCTask* task)
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

// �Ƴ������б�
void TaskManager::removeList(NPCTask* task)
{
    if (!task->getHaveTask()) {
        static_cast<TaskLayer*>(taskLayer)->removeItem(task->getIcon());
    }
}


// ����NPC���ָ���������
void TaskManager::renewTask(const std::string& npcName)
{
   
}
