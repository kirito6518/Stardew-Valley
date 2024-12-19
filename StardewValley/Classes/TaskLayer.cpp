#include "TaskLayer.h"
#include "TaskManager.h"
#include "SimpleAudioEngine.h"
#include "ShopItemManager.h"

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

    // 初始化任务详情界面
    taskDetailsUI = Sprite::create("ui/task_details_bg.png");
    taskDetailsUI->setAnchorPoint(Vec2(0.5, 0.5));
    taskDetailsUI->setPosition(visibleSize / 2);
    taskDetailsUI->setVisible(false);
    this->addChild(taskDetailsUI, 2);

    // 初始化任务详情标签
    taskDetailsLabel = Label::createWithTTF("", "fonts/Gen.ttf", 25);
    taskDetailsLabel->setAnchorPoint(Vec2(0, 1));
    taskDetailsLabel->setVisible(false);
    this->addChild(taskDetailsLabel, 3);

    // 创建关闭按钮
   /* closeButton = MenuItemImage::create(
        "ui/close_normal.png",
        "ui/close_pressed.png",
        CC_CALLBACK_1(TaskLayer::hideTaskDetails, this));*/

    if (!closeButton)
    {
        return false;
    }

    closeButton->setAnchorPoint(Vec2(1, 0));
    closeButton->setPosition(Vec2(visibleSize.width / 2 + taskDetailsUI->getContentSize().width / 2, visibleSize.height / 2 + taskDetailsUI->getContentSize().height / 2));
    closeButton->setVisible(false);
    this->addChild(closeButton);

    // 添加鼠标事件监听器
    setupMouseListener();

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

// 显示任务详情
void TaskLayer::showTaskDetails(const std::string& npcName)
{
#if 0
    auto taskDescription = TaskManager::getInstance();
    if (!taskDescription.empty())
    {
        taskDetailsUI->setVisible(true);
        taskDetailsLabel->setString(taskDescription);
        taskDetailsLabel->setPosition(taskDetailsUI->getPosition() + Vec2(-taskDetailsUI->getContentSize().width / 2 + 20, taskDetailsUI->getContentSize().height / 2 - 20));
        taskDetailsLabel->setVisible(true);
        closeButton->setVisible(true);
    }
#endif
}

// 隐藏任务详情
void TaskLayer::hideTaskDetails()
{
    taskDetailsUI->setVisible(false);
    taskDetailsLabel->setVisible(false);
    closeButton->setVisible(false);
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