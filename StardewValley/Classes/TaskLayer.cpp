#include "TaskLayer.h"
#include "TaskManager.h"
#include "SimpleAudioEngine.h"
#include "ShopItemManager.h"
#include "MainMap.h"

USING_NS_CC;
using namespace CocosDenshion;

// 创建任务列表层
TaskLayer* TaskLayer::create()
{
    auto layer = new (std::nothrow) TaskLayer();
    if (layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

// 初始化任务列表层
bool TaskLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // 获取窗口数据
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 初始化任务界面
    taskUI = Sprite::create("ui/taskUI0.png");
    taskUI->setAnchorPoint(Vec2(0, 0.5));
    taskUI->setPosition(Vec2(visibleSize.width/2-100, visibleSize.height/2));
    this->addChild(taskUI, 4);

    //获取任务界面信息
    auto TaskUISize = taskUI->getContentSize();
    auto TsakUIPos = taskUI->getPosition();

    // 创建关闭按钮
    closeButton = MenuItemImage::create(
        "ui/close_normal.png",
        "ui/close_pressed.png",
        CC_CALLBACK_1(TaskLayer::closeTaskUI, this));
    closeButton->setAnchorPoint(Vec2(1, 0));
    closeButton->setPosition(Vec2(TsakUIPos.x+ TaskUISize.width, TsakUIPos.y+ TaskUISize.height/2));
    closeButton->setVisible(false);
    this->addChild(closeButton,4);

    // 添加鼠标事件监听器
    setupMouseListener();

    return true;
}


//添加任务列表到layer中
bool TaskLayer::addList(Sprite* taskList)
{

    //获取任务界面信息
    auto TaskUISize = taskUI->getContentSize();
    auto TsakUIPos = taskUI->getPosition();


    //物品坐标相对于初始坐标的偏移量
    int dx, dy;
    taskList->setAnchorPoint(Vec2(1, 0));

    taskList->setPosition(Vec2(TsakUIPos.x, TsakUIPos.y+ TaskUISize.height/2));
    // 将物品图标添加到背包层
    this->addChild(taskList, 4);
    lists.pushBack(taskList);

#if 0
    // 为物品图标设置用户数据（即 Item 对象）
    Item* item = static_cast<Item*>(taskList->getUserData());
    if (item)
    {
        itemSprite->setUserData(item);
    }

    currentItems++;
#endif
    return true;
}


// 向任务列表中添加任务
void TaskLayer::addTask(const std::string& npcName, const std::string& taskDescription)
{
    
}

// 移除任务
void TaskLayer::removeTask(const std::string& npcName)
{
    //tasks.erase(npcName);
}


void TaskLayer::closeTaskUI(Ref* sender)
{
    TaskManager::getInstance()->hideTaskList();

    // 调用mainmap的恢复时间更新的函数
    dynamic_cast<MainMap*>(TaskManager::getInstance()->mainMap)->hideBackpack(sender);
}

// 设置鼠标事件监听器
void TaskLayer::setupMouseListener()
{
    auto mouseListener = EventListenerMouse::create();

    // 鼠标点击事件
    mouseListener->onMouseDown = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // 遍历所有 NPC 名称，检查鼠标是否点击了某个 NPC
        /*for (auto& taskPair : tasks)
        {
            auto npcName = taskPair.first;

            // 获取 NPC 名称标签的坐标
            auto npcLabel = Label::createWithTTF(npcName, "fonts/Gen.ttf", 25);
            npcLabel->setPosition(Vec2(100, 500 - 50 * std::distance(tasks.begin(), tasks.find(npcName))));

            // 计算 NPC 名称标签的边界框
            Rect npcBoundingBox = Rect(npcLabel->getPosition().x, npcLabel->getPosition().y, npcLabel->getContentSize().width, npcLabel->getContentSize().height);

            if (npcBoundingBox.containsPoint(mousePosition))
            {
                // 显示任务详情
                showTaskDetails(npcName);
                return;
            }
        }*/
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}