#include "TaskManager.h"

// ����ʵ��
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

// ���һ������
void TaskManager::addTask(NPCTask* task)
{
    tasks.pushBack(task);
}

// ��ȡһ������
NPCTask* TaskManager::getTask(const std::string& npcName)
{
    for (auto task : tasks) {
        if (task->getNPCName() == npcName)
        {
            return task;
        }
    }
    return nullptr;
}

// �����������
void TaskManager::clearAllTasks()
{
    tasks.clear();
}

// ����һ���µ�����
void TaskManager::generateNewTask(const std::string& npcName, const std::string& description, const std::string& requiredItem, int requiredItemCount)
{
    NPCTask* task = new NPCTask(npcName, description, requiredItem, requiredItemCount);
    addTask(task);
}

// ���� TaskManager ʵ��
void TaskManager::destroyInstance()
{
    if (instance)
    {
        delete instance;
        instance = nullptr; // ȷ��ʵ��������Ϊ nullptr�������ظ�ɾ��
    }
}