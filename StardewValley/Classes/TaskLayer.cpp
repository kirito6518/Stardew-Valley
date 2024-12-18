#include "TaskLayer.h"
#include "TaskManager.h"
#include "NPCManager.h" // 假设有一个管理 NPC 好感度的类

USING_NS_CC;

// 创建任务层
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

// 初始化任务层
bool TaskLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // 获取窗口数据
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 加载任务背景图片
    taskBgSprite = Sprite::create("ui/task_bg.png");
    taskBgSprite->setAnchorPoint(Vec2(0.5, 0.5));
    taskBgSprite->setPosition(visibleSize / 2);
    this->addChild(taskBgSprite, 2);

    // 初始化任务标签
    taskLabel = Label::createWithTTF("", "fonts/Gen.ttf", 20);
    taskLabel->setAnchorPoint(Vec2(0, 1));
    taskLabel->setVisible(false);
    this->addChild(taskLabel, 3);

    // 初始化完成按钮
    completeButton = MenuItemImage::create(
        "ui/complete_button_normal.png",
        "ui/complete_button_pressed.png",
        CC_CALLBACK_1(TaskLayer::completeTask, this));
    completeButton->setAnchorPoint(Vec2(1, 1));
    completeButton->setPosition(Vec2(visibleSize.width / 2 + 50, visibleSize.height / 2 - 50));
    this->addChild(completeButton, 3);
    completeButton->setEnabled(false);

    // 添加鼠标事件监听器
    setupMouseListener();

    return true;
}

// 添加任务到任务层
void TaskLayer::addTask(NPCTask* task)
{
    taskList.pushBack(task);
    updateTaskUI(task);
}

// 移除任务
void TaskLayer::removeTask(NPCTask* task)
{
    taskList.eraseObject(task);
    task->removeFromParent();
}

// 更新任务UI
void TaskLayer::updateTaskUI(NPCTask* task)
{
    // 显示任务信息
    std::string taskInfo = task->getDescription() + "\nRequired: " + task->getRequiredItem() + " x" + std::to_string(task->getRequiredItemCount());
    taskLabel->setString(taskInfo);
    taskLabel->setPosition(taskBgSprite->getPosition() + Vec2(0, 50));
    taskLabel->setVisible(true);

    // 显示完成按钮
    completeButton->setUserData(task);
    completeButton->setVisible(true);
    completeButton->setEnabled(!task->isOnCooldown()); // 如果任务在冷却中，禁用按钮
}

// 点击任务的回调函数
void TaskLayer::onTaskClicked(NPCTask* task)
{
    // 显示任务详细信息
    taskLabel->setString(task->getDescription());
    taskLabel->setPosition(taskBgSprite->getPosition() + Vec2(0, 50));
    taskLabel->setVisible(true);

    // 显示完成按钮
    completeButton->setUserData(task);
    completeButton->setVisible(true);
    completeButton->setEnabled(!task->isOnCooldown()); // 如果任务在冷却中，禁用按钮
}

// 完成任务
void TaskLayer::completeTask(Ref* sender)
{
    auto task = static_cast<NPCTask*>(completeButton->getUserData());

    if (task)
    {
        // 检查任务是否可以完成
        if (task->canComplete())
        {
            // 完成任务并增加 NPC 好感度
            task->complete();
            //NPCManager::getInstance()->increaseAffinity(task->getNPCName());

            // 隐藏任务UI
            taskLabel->setVisible(false);
            completeButton->setVisible(false);
            completeButton->setEnabled(false);

            // 提示任务完成
            taskLabel->setString("Task Completed!");
            taskLabel->setVisible(true);

            // 设置任务冷却时间
            task->setCooldown(60.0f); // 假设冷却时间为 60 秒
        }
        else
        {
            // 提示任务无法完成
            taskLabel->setString("Cannot complete task!");
        }
    }
}

// 鼠标监听事件与任务内元素的交互
void TaskLayer::setupMouseListener()
{
    auto mouseListener = EventListenerMouse::create();

    // 鼠标移动事件
    mouseListener->onMouseMove = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // 遍历所有任务，检查鼠标是否悬停在某个任务上
        for (auto task : taskList)
        {
            Vec2 taskPosition = task->getPosition();
            Rect taskBoundingBox = Rect(taskPosition.x, taskPosition.y - 50, 200, 50);

            if (taskBoundingBox.containsPoint(mousePosition))
            {
                // 显示任务名称
                taskLabel->setString(task->getDescription());
                taskLabel->setPosition(taskPosition + Vec2(0, 30));
                taskLabel->setVisible(true);
                return;
            }
        }

        // 如果鼠标不在任何任务上，隐藏任务名称
        taskLabel->setVisible(false);
        };

    // 鼠标点击事件
    mouseListener->onMouseDown = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // 遍历所有任务，检查鼠标是否点击了某个任务
        for (auto task : taskList)
        {
            Vec2 taskPosition = task->getPosition();
            Rect taskBoundingBox = Rect(taskPosition.x, taskPosition.y - 50, 200, 50);

            if (taskBoundingBox.containsPoint(mousePosition))
            {
                onTaskClicked(task);
                return;
            }
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}