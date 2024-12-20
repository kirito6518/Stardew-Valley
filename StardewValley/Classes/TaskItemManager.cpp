#include "TaskItemManager.h"

// ����ʵ��
TaskItemManager* TaskItemManager::instance = nullptr;

// ��ȡ����ʵ��
TaskItemManager* TaskItemManager::getInstance()
{
    if (!instance)
    {
        instance = new TaskItemManager();
    }
    return instance;
}

// ���һ�� TaskItem ʵ��
void TaskItemManager::addTaskItem(TaskItem* taskItem)
{
    taskItems.pushBack(taskItem);
}

// ͨ�����ֻ�ȡһ�� TaskItem ʵ��
TaskItem* TaskItemManager::getTaskItemByName(std::string itemName)
{
    for (auto taskItem : taskItems)
    {
        if (taskItem->getName()== itemName)
        {
            return taskItem;
        }
    }
    return nullptr;
}

// ͨ��id��ȡһ�� TaskItem ʵ��
TaskItem* TaskItemManager::getTaskItemById(int id)
{
    for (auto taskItem : taskItems)
    {
        if (taskItem->getTaskId() == id)
        {
            return taskItem;
        }
    }
    return nullptr;
}

// ������� TaskItem ʵ��
void TaskItemManager::clearAllTaskItems()
{
    taskItems.clear();
}

// ���� TaskItemManager ʵ��
void TaskItemManager::destroyInstance()
{
    if (instance)
    {
        delete instance;
        instance = nullptr; // ȷ��ʵ��������Ϊ nullptr�������ظ�ɾ��
    }
}