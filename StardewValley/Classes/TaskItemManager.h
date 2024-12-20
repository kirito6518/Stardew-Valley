#ifndef __TASK_ITEM_MANAGER_H__
#define __TASK_ITEM_MANAGER_H__

#include "TaskItem.h"
#include "cocos2d.h"

class TaskItemManager
{
public:
    // 获取单例实例
    static TaskItemManager* getInstance();

    // 添加一个 TaskItem 实例
    void addTaskItem(TaskItem* taskItem);

    // 通过名字获取一个 TaskItem 实例
    TaskItem* getTaskItemByName(std::string itemName);

    //通过id获取一个 TaskItem 实例
    TaskItem* getTaskItemById(int id);

    // 清空所有 TaskItem 实例
    void clearAllTaskItems();

    // 销毁 TaskItemManager 实例
    void destroyInstance();

private:
    static TaskItemManager* instance; // 单例实例
    cocos2d::Vector<TaskItem*> taskItems; // 存储 TaskItem 实例
};

#endif // __TASK_ITEM_MANAGER_H__