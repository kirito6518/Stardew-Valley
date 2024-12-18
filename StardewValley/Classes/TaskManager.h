#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "cocos2d.h"
#include "NPCTask.h"

USING_NS_CC;

class TaskManager {
public:
    static TaskManager* getInstance();
    void destroyInstance();

    // 添加一个任务
    void addTask(NPCTask* task);

    // 获取一个任务
    NPCTask* getTask(const std::string& npcName);

    // 清空所有任务
    void clearAllTasks();

    // 生成一个新的任务
    void generateNewTask(const std::string& npcName, const std::string& description, const std::string& requiredItem, int requiredItemCount);

private:
    static TaskManager* instance;
    Vector<NPCTask*> tasks;
};

#endif // TASKMANAGER_H