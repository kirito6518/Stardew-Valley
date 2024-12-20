#include "TaskItemManager.h"

// 单例实例
TaskItemManager* TaskItemManager::instance = nullptr;

// 获取单例实例
TaskItemManager* TaskItemManager::getInstance()
{
    if (!instance)
    {
        instance = new TaskItemManager();
    }
    return instance;
}

// 添加一个 TaskItem 实例
void TaskItemManager::addTaskItem(TaskItem* taskItem)
{
    taskItems.pushBack(taskItem);
}

// 通过名字获取一个 TaskItem 实例
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

// 通过id获取一个 TaskItem 实例
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

// 清空所有 TaskItem 实例
void TaskItemManager::clearAllTaskItems()
{
    taskItems.clear();
}

// 销毁 TaskItemManager 实例
void TaskItemManager::destroyInstance()
{
    if (instance)
    {
        delete instance;
        instance = nullptr; // 确保实例被设置为 nullptr，避免重复删除
    }
}