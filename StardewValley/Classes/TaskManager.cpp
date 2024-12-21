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
    // 初始化任务物品并设置稀有度
    TaskItem* gemA = TaskItem::create("mineral/GemA.png", "GemA", 1);
    gemA->setRarity(1);
    TaskItemManager::getInstance()->addTaskItem(gemA);

    TaskItem* gemB = TaskItem::create("mineral/GemB.png", "GemB", 2);
    gemB->setRarity(2);
    TaskItemManager::getInstance()->addTaskItem(gemB);

    TaskItem* gemC = TaskItem::create("mineral/GemC.png", "GemC", 3);
    gemC->setRarity(3);
    TaskItemManager::getInstance()->addTaskItem(gemC);

    TaskItem* gemD = TaskItem::create("mineral/GemD.png", "GemD", 4);
    gemD->setRarity(4);
    TaskItemManager::getInstance()->addTaskItem(gemD);

    TaskItem* gemE = TaskItem::create("mineral/GemE.png", "GemE", 5);
    gemE->setRarity(5);
    TaskItemManager::getInstance()->addTaskItem(gemE);

    // 鱼类，稀有度2
    TaskItem* fishA = TaskItem::create("fish/FishA.png", "FishA", 6);
    fishA->setRarity(2);
    TaskItemManager::getInstance()->addTaskItem(fishA);

    TaskItem* fishB = TaskItem::create("fish/FishB.png", "FishB", 7);
    fishB->setRarity(2);
    TaskItemManager::getInstance()->addTaskItem(fishB);

    TaskItem* fishC = TaskItem::create("fish/FishC.png", "FishC", 8);
    fishC->setRarity(2);
    TaskItemManager::getInstance()->addTaskItem(fishC);

    TaskItem* fishD = TaskItem::create("fish/FishD.png", "FishD", 9);
    fishD->setRarity(2);
    TaskItemManager::getInstance()->addTaskItem(fishD);

    TaskItem* fishE = TaskItem::create("fish/FishE.png", "FishE", 10);
    fishE->setRarity(2);
    TaskItemManager::getInstance()->addTaskItem(fishE);

    // 农作物
    TaskItem* onion = TaskItem::create("crops/Onion.png", "Onion", 11);
    onion->setRarity(4);
    TaskItemManager::getInstance()->addTaskItem(onion);

    TaskItem* potato = TaskItem::create("crops/Potato.png", "Potato", 12);
    potato->setRarity(3);
    TaskItemManager::getInstance()->addTaskItem(potato);

    TaskItem* carrot = TaskItem::create("crops/Carrot.png", "Carrot", 13);
    carrot->setRarity(2);
    TaskItemManager::getInstance()->addTaskItem(carrot);

    TaskItem* turnip = TaskItem::create("crops/Turnip.png", "Turnip", 14);
    turnip->setRarity(1);
    TaskItemManager::getInstance()->addTaskItem(turnip);

    TaskItem* radish = TaskItem::create("crops/Radish.png", "Radish", 15);
    radish->setRarity(2);
    TaskItemManager::getInstance()->addTaskItem(radish);

    TaskItem* spinach = TaskItem::create("crops/Spinach.png", "Spinach", 16);
    spinach->setRarity(3);
    TaskItemManager::getInstance()->addTaskItem(spinach);

    // 动物产品，稀有度2
    TaskItem* pork = TaskItem::create("animal/Pork.png", "Pork", 17);
    pork->setRarity(2);
    TaskItemManager::getInstance()->addTaskItem(pork);

    TaskItem* beef = TaskItem::create("animal/Beef.png", "Beef", 18);
    beef->setRarity(2);
    TaskItemManager::getInstance()->addTaskItem(beef);

    TaskItem* mutton = TaskItem::create("animal/Mutton.png", "Mutton", 19);
    mutton->setRarity(2);
    TaskItemManager::getInstance()->addTaskItem(mutton);

    TaskItem* chicken = TaskItem::create("animal/Chicken.png", "Chicken", 20);
    chicken->setRarity(2);
    TaskItemManager::getInstance()->addTaskItem(chicken);

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
