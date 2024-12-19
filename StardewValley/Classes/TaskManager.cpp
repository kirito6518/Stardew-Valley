#include "TaskManager.h"
#include "TaskLayer.h"
#include "ShopItem.h"
#include "ShopItemManager.h"

USING_NS_CC;

// 初始化单例实例
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

// 构造函数
TaskManager::TaskManager()
{
    taskLayer = TaskLayer::create();
    taskLayer->retain(); // 保留任务列表层，防止被释放

    //所有会出现在任务栏的物品都在此处加载
    //默认在正常名字后加1，利用第一个数字作为其唯一标识符
    ShopItem::create("crops/Onion.png", "1",0);//意为当前无任务

    ShopItem::create("crops/Onion.png", "Onion1",1);

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

// 根据NPC名字更新其任务
void TaskManager::renewTask(const std::string& npcName)
{
   
}
