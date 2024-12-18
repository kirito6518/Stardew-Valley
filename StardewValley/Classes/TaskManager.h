#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "cocos2d.h"
#include "NPCTask.h"

USING_NS_CC;

class TaskManager {
public:
    static TaskManager* getInstance();
    void destroyInstance();

    // ���һ������
    void addTask(NPCTask* task);

    // ��ȡһ������
    NPCTask* getTask(const std::string& npcName);

    // �����������
    void clearAllTasks();

    // ����һ���µ�����
    void generateNewTask(const std::string& npcName, const std::string& description, const std::string& requiredItem, int requiredItemCount);

private:
    static TaskManager* instance;
    Vector<NPCTask*> tasks;
};

#endif // TASKMANAGER_H