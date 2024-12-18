#include "TaskManager.h"

// 单例实例
TaskManager* TaskManager::instance = nullptr;

// 获取单例实例
TaskManager* TaskManager::getInstance()
{
    if (!instance)
    {
        instance = new TaskManager();
    }
    return instance;
}

// 添加一个任务
void TaskManager::addTask(NPCTask* task)
{
    tasks.pushBack(task);
}

// 获取一个任务
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

// 清空所有任务
void TaskManager::clearAllTasks()
{
    tasks.clear();
}

// 生成一个新的任务
void TaskManager::generateNewTask(const std::string& npcName, const std::string& description, const std::string& requiredItem, int requiredItemCount)
{
    NPCTask* task = new NPCTask(npcName, description, requiredItem, requiredItemCount);
    addTask(task);
}

// 销毁 TaskManager 实例
void TaskManager::destroyInstance()
{
    if (instance)
    {
        delete instance;
        instance = nullptr; // 确保实例被设置为 nullptr，避免重复删除
    }
}