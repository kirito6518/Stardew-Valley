#include "TaskLayer.h"
#include "TaskManager.h"
#include "SimpleAudioEngine.h"
#include "TaskItem.h"
#include "TaskItemManager.h"
#include "MainMap.h"
#include "NPCtask.h"

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
    taskUI = Sprite::create("ui/taskUI.png");
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

    //创建任务详情UI
    taskDetailsUi = Sprite::create("ui/task_detailsUI.png");
    taskDetailsUi->setAnchorPoint(Vec2(0, 0.5));
    taskDetailsUi->setPosition(TsakUIPos);
    taskDetailsUi -> setVisible(false);
    this->addChild(taskUI, 5);

    //创建需求物品精灵
    needItem = Sprite::create();
    needItem->setAnchorPoint(Vec2(0, 0.5));
    needItem->setPosition(TsakUIPos+Vec2(300,-400));
    needItem->setVisible(false);
    this->addChild(taskUI, 6);

    //创建需求物品数量标签
    needItemCount =Label::createWithTTF("", "fonts/Gen.ttf", 30);
    needItemCount->setAnchorPoint(Vec2(0, 0.5));
    needItemCount->setPosition(TsakUIPos + Vec2(350, -400));
    needItemCount->setVisible(false);
    this->addChild(needItemCount, 6);

    //创建提交按钮
    submitButton = MenuItemImage::create(
        "ui/CloseNormal.png",
        "ui/CloseSelected.png",
        CC_CALLBACK_1(TaskLayer::closeTaskUI, this));
    submitButton->setAnchorPoint(Vec2(1, 0));
    submitButton->setPosition(TsakUIPos+Vec2(400, -500));
    submitButton->setVisible(false);
    this->addChild(submitButton, 6);

    //创建提交成功标签
    submitSuccess = Label::createWithTTF("Submit Success!", "fonts/Gen.ttf", 30);
    submitSuccess->setAnchorPoint(Vec2(0.5, 0.5));
    submitSuccess->setPosition(TsakUIPos);
    submitSuccess->setVisible(false);
    this->addChild(submitSuccess, 7);

    //创建提交失败标签
    submitFailed = Label::createWithTTF("You Don't Have Enough Item!", "fonts/Gen.ttf", 30);
    submitFailed->setAnchorPoint(Vec2(0.5, 0.5));
    submitFailed->setPosition(TsakUIPos);
    submitFailed->setVisible(false);
    this->addChild(submitFailed, 7);

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


    taskList->setAnchorPoint(Vec2(1, 1));
    taskList->setPosition(Vec2(TsakUIPos.x, TsakUIPos.y+ TaskUISize.height/2));
    // 将List添加到任务层
    this->addChild(taskList, 4);
    lists.pushBack(taskList);


    return true;
}

// 移除列表
void TaskLayer::removeItem(Sprite* taskList)
{

    lists.eraseObject(taskList);
    taskList->removeFromParent();
}

//更新位置
void TaskLayer::renewPosition()
{
    //获取任务界面信息
    auto TaskUISize = taskUI->getContentSize();
    auto TsakUIPos = taskUI->getPosition();

    //更新list位置
    int count = 0;
    const int space = 132;
    int startX = TsakUIPos.x;
    int startY = TsakUIPos.y + TaskUISize.height / 2;
    for (auto list : lists) {
        int x = startX;
        int y = startY + count * space;
        list->setPosition(Vec2(x, y));
        count++;
    }

    //更新其他ui位置
    closeButton->setPosition(Vec2(TsakUIPos.x + TaskUISize.width, TsakUIPos.y + TaskUISize.height / 2));
    taskDetailsUi->setPosition(TsakUIPos);
    needItem->setPosition(TsakUIPos + Vec2(300, -400));
    needItemCount->setPosition(TsakUIPos + Vec2(350, -400));
    submitButton->setPosition(TsakUIPos + Vec2(400, -500));
    submitSuccess->setPosition(TsakUIPos);
    submitFailed->setPosition(TsakUIPos);



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