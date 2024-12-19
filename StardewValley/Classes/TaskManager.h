#ifndef __TASK_MANAGER_H__
#define __TASK_MANAGER_H__

#include "cocos2d.h"
#include "TaskLayer.h"
#include "NPCTask.h"

USING_NS_CC;

/**
 * @class TaskManager
 * @brief 任务管理器类，负责管理任务的生成、移除和完成。
 *
 * TaskManager 是一个单例类，用于管理任务的生成、移除和完成。它负责与 TaskLayer 进行交互，
 * 并提供添加任务、移除任务、检查任务是否完成等功能。
 */
class TaskManager : public cocos2d::Layer
{
public:
    //获取 TaskManager 的单例实例
    static TaskManager* getInstance();

    //显示任务列表界面
    void showTaskList(Node* parent);

    //隐藏任务列表界面
    void hideTaskList();

    //根据NPC名字更新其任务
    void renewTask(const std::string& npcName);

    //获取MainMap实例
    Scene* mainMap;

private:


    static TaskManager* instance; ///< 单例实例
    TaskLayer* taskLayer; ///< 任务列表层对象
    Vector < NPCTask*> tasks; ///< 任务列表

    /**
     * @brief 构造函数，初始化 TaskManager。
     */
    TaskManager();

    /**
     * @brief 析构函数，释放资源。
     */
    ~TaskManager();
};

#endif // __TASK_MANAGER_H__