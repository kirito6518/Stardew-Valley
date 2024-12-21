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
    // 初始化任务物品
    TaskItem::create("mineral/GemA.png", "GemA", 1);
    TaskItem::create("mineral/GemB.png", "GemB", 2);
    TaskItem::create("mineral/GemC.png", "GemC", 3);
    TaskItem::create("mineral/GemD.png", "GemD", 4);
    TaskItem::create("mineral/GemE.png", "GemE", 5);
    TaskItem::create("fish/FishA.png", "FishA", 6);
    TaskItem::create("fish/FishB.png", "FishB", 7);
    TaskItem::create("fish/FishC.png", "FishC", 8);
    TaskItem::create("fish/FishD.png", "FishD", 9);
    TaskItem::create("fish/FishE.png", "FishE", 10);
    TaskItem::create("crops/Onion.png", "Onion", 11);
    TaskItem::create("crops/Potato.png", "Potato", 12);
    TaskItem::create("crops/Carrot.png", "Carrot", 13);
    TaskItem::create("crops/Turnip.png", "Turnip", 14);
    TaskItem::create("crops/Potato.png", "Radish", 15);
    TaskItem::create("crops/Spinach.png", "Spinach", 16);
    TaskItem::create("animal/Pork.png", "Pork", 17);
    TaskItem::create("animal/Beef.png", "Beef", 18);
    TaskItem::create("animal/Mutton.png", "Muttun", 19);
    TaskItem::create("animal/Chicken.png", "Chicken", 20);

    // 初始化四个NPC的任务
    // 店长
    NPCTask* shopOwner = new NPCTask("Alice");
    addTaskList(shopOwner);
    tasks.pushBack(shopOwner);

    // 渔夫
    NPCTask* fisher = new NPCTask("Bob");
    addTaskList(fisher);
    tasks.pushBack(fisher);

    // 农民
    NPCTask* farmer = new NPCTask("Mary");
    addTaskList(farmer);
    tasks.pushBack(farmer);

    // 牧民
    NPCTask* rancher = new NPCTask("Annie");
    addTaskList(rancher);
    tasks.pushBack(rancher);
    
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
        task->renewTask();
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
