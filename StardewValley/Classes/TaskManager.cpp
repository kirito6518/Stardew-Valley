#include "TaskManager.h"
#include "TaskLayer.h"
#include "TaskItem.h"
#include "TaskItemManager.h"
#include "NPCTask.h"

USING_NS_CC;

// 初始化单例实例
TaskManager* TaskManager::instance = nullptr;

// 获取单例实例
TaskManager* TaskManager::getInstance()
{
    if (!instance)
    {
        instance = new(std::nothrow) TaskManager();
    }
    return instance;
}

// 构造函数
TaskManager::TaskManager()
{
    taskLayer = TaskLayer::create();
    taskLayer->retain();

    //所有会出现在任务栏的物品都在此处加载，最好不要用名字带换行符的物品
    //第一个数字作为其唯一标识符
    TaskItem::create("crops/Onion.png", "Onion",1);


    //四个npc任务的初始化在此加载
    NPCTask* Alice=new NPCTask("Alice");
    addTaskList(Alice);
    tasks.pushBack(Alice);
    //继续增加....

}

// 析构函数
TaskManager::~TaskManager()
{
    taskLayer->release(); // 释放任务列表层
}

// 显示任务列表
void TaskManager::showTaskList(Node* parent)
{
    if (taskLayer->getParent() == nullptr)
    {
        parent->addChild(taskLayer, 4); // 将任务列表层添加到当前场景
    }
}

// 隐藏任务列表
void TaskManager::hideTaskList()
{
    taskLayer->removeFromParentAndCleanup(false); // 从父节点移除，但保留对象
}

//添加任务列表
bool TaskManager::addTaskList(NPCTask* task)
{
    if (!task) {
        return false;
    }

    if (!task->getHaveTask()) {
        return false;
    }

    task->retain(); // 防止其在被销毁时为空


    // 获取列表实例并设置用户数据
    auto listSprite = task->getIcon();
    listSprite->setUserData(task);// 将 task 对象与列表图标关联

    // 将列表图标添加到任务层
    static_cast<TaskLayer*>(taskLayer)->addList(listSprite);

    return true;
}


// 更新任务状态
void TaskManager::renewTask()
{
    for (auto task : tasks) {
        if (!task->getHaveTask()) {
            static_cast<TaskLayer*>(taskLayer)->removeItem(task->getIcon());
        }
        else {
            // 获取列表实例并设置用户数据
            auto listSprite = task->getIcon();
            if (!listSprite->getParent()) {//确保listSprite没有父节点
                listSprite->setUserData(task);// 将 task 对象与列表图标关联
                // 将列表图标添加到任务层
                static_cast<TaskLayer*>(taskLayer)->addList(listSprite);
            }         
        }

    }
}
