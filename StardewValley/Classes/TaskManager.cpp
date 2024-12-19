#include "TaskManager.h"
#include "TaskLayer.h"
#include "ShopItem.h"
#include "ShopItemManager.h"

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
    //Ĭ�����������ֺ��1�����õ�һ��������Ϊ��Ψһ��ʶ��
    ShopItem::create("crops/Onion.png", "1",0);//��Ϊ��ǰ������

    ShopItem::create("crops/Onion.png", "Onion1",1);

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

// ����NPC���ָ���������
void TaskManager::renewTask(const std::string& npcName)
{
   
}
