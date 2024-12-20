#ifndef __TASK_ITEM_MANAGER_H__
#define __TASK_ITEM_MANAGER_H__

#include "TaskItem.h"
#include "cocos2d.h"

class TaskItemManager
{
public:
    // ��ȡ����ʵ��
    static TaskItemManager* getInstance();

    // ���һ�� TaskItem ʵ��
    void addTaskItem(TaskItem* taskItem);

    // ͨ�����ֻ�ȡһ�� TaskItem ʵ��
    TaskItem* getTaskItemByName(std::string itemName);

    //ͨ��id��ȡһ�� TaskItem ʵ��
    TaskItem* getTaskItemById(int id);

    // ������� TaskItem ʵ��
    void clearAllTaskItems();

    // ���� TaskItemManager ʵ��
    void destroyInstance();

private:
    static TaskItemManager* instance; // ����ʵ��
    cocos2d::Vector<TaskItem*> taskItems; // �洢 TaskItem ʵ��
};

#endif // __TASK_ITEM_MANAGER_H__