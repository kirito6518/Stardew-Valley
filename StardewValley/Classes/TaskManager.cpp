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
    //��һ��������Ϊ��Ψһ��ʶ��
    TaskItem::create("crops/Onion.png", "Onion",1);


    //�ĸ�npc����ĳ�ʼ���ڴ˼���
    NPCTask* Alice=new NPCTask("Alice");
    addTaskList(Alice);
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
