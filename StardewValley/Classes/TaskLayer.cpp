#include "TaskLayer.h"
#include "TaskManager.h"
#include "TaskItem.h"
#include "TaskItemManager.h"
#include "MainMap.h"
#include "NPCtask.h"
#include "NPCManager.h"
#include "NPC.h"
USING_NS_CC;


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
    taskUI = Sprite::create("ui/task.png");
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
    this->addChild(closeButton,4);

    //创建任务详情UI
    taskDetailsUi = Sprite::create("ui/task_detailsUI.png");
    taskDetailsUi->setAnchorPoint(Vec2(0, 0.5));
    taskDetailsUi->setPosition(TsakUIPos);
    taskDetailsUi -> setVisible(false);
    this->addChild(taskDetailsUi, 5);

    //创建需求物品数量标签
    needItemDeta =Label::createWithTTF("", "fonts/Gen.ttf", 30);
    needItemDeta->setAnchorPoint(Vec2(0, 0.5));
    needItemDeta->setVisible(false);
    this->addChild(needItemDeta, 6);

    //创建奖励好感度标签
    rewardGoodwill= Label::createWithTTF("10", "fonts/Gen.ttf", 30);
    rewardGoodwill->setAnchorPoint(Vec2(0, 0.5));
    rewardGoodwill->setVisible(false);
    this->addChild(rewardGoodwill, 6);

    //创建现有好感度标签
    nowGoodwill = Label::createWithTTF("", "fonts/Gen.ttf", 30);
    nowGoodwill->setAnchorPoint(Vec2(0, 0.5));
    nowGoodwill->setVisible(false);
    this->addChild(nowGoodwill, 6);

    //创建提交按钮
    submitButton = MenuItemImage::create(
        "ui/submit_normal.png",
        "ui/submit_pressed.png",
        CC_CALLBACK_1(TaskLayer::onSubmitButton, this));
    submitButton->setAnchorPoint(Vec2(0.5, 1));
    submitButton->setVisible(false);
    submitButton->setEnabled(false);//默认关闭其鼠标监听
    this->addChild(submitButton, 6);

    //创建提交结果标签
    resultLabel = Label::createWithTTF("", "fonts/Gen.ttf", 30);
    resultLabel->setAnchorPoint(Vec2(0.5, 0.5));
    resultLabel->setPosition(TsakUIPos);
    resultLabel->setVisible(false);
    this->addChild(resultLabel, 7);


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
    taskList->removeFromParentAndCleanup(false);
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
        int y = startY - count * space;
        list->setPosition(Vec2(x, y));
        count++;
    }

    //更新其他ui位置
    closeButton->setPosition(Vec2(TsakUIPos.x + TaskUISize.width, TsakUIPos.y + TaskUISize.height / 2));
    taskDetailsUi->setPosition(TsakUIPos);
    needItemDeta->setPosition(TsakUIPos + Vec2(150,-98));
    submitButton->setPosition(TsakUIPos + Vec2(TaskUISize.width/2+155, -TaskUISize.height / 2+100));
    resultLabel->setPosition(TsakUIPos+Vec2(100,0));
    rewardGoodwill->setPosition(TsakUIPos + Vec2(262, -192));
    nowGoodwill->setPosition(TsakUIPos + Vec2(262, -148));

}

//关闭按钮的回调函数
void TaskLayer::closeTaskUI(Ref* sender)
{
    TaskManager::getInstance()->hideTaskList();

    // 调用mainmap的恢复时间更新的函数
    dynamic_cast<MainMap*>(TaskManager::getInstance()->mainMap)->hideBackpack(sender);
}

//提交按钮的回调函数
void TaskLayer::onSubmitButton(Ref* sender)
{
    auto list = static_cast<Sprite*>(submitButton->getUserData());

    if (list)
    {
        auto task = static_cast<NPCTask*>(list->getUserData());
        bool success = task->canComplete();//检测是否能够完成任务

        if (success)
        {
            task->complete();//完成任务
            std::string getItem = task->getNeedItemName();
            // 获取背包中的任务物品
            auto item = BackpackManager::getInstance()->getItemByName(getItem);
            // 从背包中减少所需物品
            item->decreaseCount(task->getNeedItemCount());
            resultLabel->setString("Submit Success!");
            TaskManager::getInstance()->renewTask();
            //隐藏详细信息ui
            taskDetailsUi->setVisible(false);

            //隐藏需要物品信息
            needItemDeta->setVisible(false);

            //隐藏提交按钮
            submitButton->setVisible(false);
            submitButton->setEnabled(false);

            //隐藏好感度ui
            rewardGoodwill->setVisible(false);    
            nowGoodwill->setVisible(false);
        }
        else
        {
            resultLabel->setString("You Don't Have enough Items Left!");
        }

        resultLabel->setVisible(true);

        //更新物品位置
        this->renewPosition();

        this->scheduleOnce([this](float dt) {
            resultLabel->setVisible(false);
            }, 1.0f, "hide_result");
    }
}

// 设置鼠标事件监听器
void TaskLayer::setupMouseListener()
{
    // 移除之前绑定的事件监听器
    _eventDispatcher->removeEventListenersForTarget(this);

    auto mouseListener = EventListenerMouse::create();

    //更新物品位置
    this->renewPosition();

    // 鼠标点击事件
    mouseListener->onMouseDown = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // 获取摄像头的偏移量
        Vec2 cameraOffset = this->getParent()->getPosition();

        // 将鼠标坐标转换为相对于场景的坐标
        mousePosition -= cameraOffset;

        //获取任务界面信息
        auto TaskUISize = taskUI->getContentSize();
        auto TsakUIPos = taskUI->getPosition();

        // 遍历所有list图标，检查鼠标是否点击了某个物品
        for (auto list : lists)
        {
            // 获取list精灵的当前坐标
            Vec2 listPosition = list->getPosition();
            auto listSize = list->getContentSize();
            // 计算list精灵的边界框
            Rect listBoundingBox = Rect(listPosition.x-listSize.width, listPosition.y - listSize.height, 
                                           listSize.width, listSize.height);

            //获取任务对象
            NPCTask* task = static_cast<NPCTask*>(list->getUserData());

            if (listBoundingBox.containsPoint(mousePosition))
            {
                if (task->getNPCName() == "Alice") {
                    list->setTexture("ui/Alice_selected.png");
                    for (auto list : lists) {
                        if (static_cast<NPCTask*>(list->getUserData())->getNPCName()=="Bob") {
                            list->setTexture("ui/Bob_task.png");
                        }
                        else if (static_cast<NPCTask*>(list->getUserData())->getNPCName() == "Mary") {
                            list->setTexture("ui/Mary_task.png");
                        }
                        else if(static_cast<NPCTask*>(list->getUserData())->getNPCName() == "Annie"){
                            list->setTexture("ui/Annie_task.png");
                        }
                    }
                }
                else if (task->getNPCName() == "Bob") {
                    list->setTexture("ui/Bob_selected.png");
                    for (auto list : lists) {
                        if (static_cast<NPCTask*>(list->getUserData())->getNPCName() == "Alice") {
                            list->setTexture("ui/Alice_task.png");
                        }
                        else if (static_cast<NPCTask*>(list->getUserData())->getNPCName() == "Mary") {
                            list->setTexture("ui/Mary_task.png");
                        }
                        else if(static_cast<NPCTask*>(list->getUserData())->getNPCName() == "Annie"){
                            list->setTexture("ui/Annie_task.png");
                        }
                    }
                }
                else if (task->getNPCName() == "Mary") {
                    list->setTexture("ui/Mary_selected.png");
                    for (auto list : lists) {
                        if (static_cast<NPCTask*>(list->getUserData())->getNPCName() == "Alice") {
                            list->setTexture("ui/Alice_task.png");
                        }
                        else if (static_cast<NPCTask*>(list->getUserData())->getNPCName() == "Bob") {
                            list->setTexture("ui/Bob_task.png");
                        }
                        else if(static_cast<NPCTask*>(list->getUserData())->getNPCName() == "Annie") {
                            list->setTexture("ui/Annie_task.png");
                        }
                    }
                }
                else {
                    list->setTexture("ui/Annie_selected.png");
                    for (auto list : lists) {
                        if (static_cast<NPCTask*>(list->getUserData())->getNPCName() == "Alice") {
                            list->setTexture("ui/Alice_task.png");
                        }
                        else if (static_cast<NPCTask*>(list->getUserData())->getNPCName() == "Bob") {
                            list->setTexture("ui/Bob_task.png");
                        }
                        else if(static_cast<NPCTask*>(list->getUserData())->getNPCName() == "Mary"){
                            list->setTexture("ui/Mary_task.png");
                        }
                    }
                }
                //显示详细信息ui
                taskDetailsUi->setPosition(TsakUIPos);
                taskDetailsUi->setVisible(true);
                
                //显示需要物品信息
                std::string deta;
                deta = std::to_string(task->getNeedItemCount())+"   " + task->getNeedItemName();
                needItemDeta->setString(deta);
                needItemDeta->setVisible(true);

                //显示提交按钮
                submitButton->setUserData(list); // 将list对象与提交按钮关联
                submitButton->setVisible(true);
                submitButton->setEnabled(true);

                //获取当前好感
                std::string name=task->getNPCName();
                int goodwill = NPCManager::getInstance()->getNPCByName(name)->getFavorability();
                nowGoodwill->setString(std::to_string(goodwill));

                //获取奖励好感
                int reward = task->getNeedItemCount() * 2;
                rewardGoodwill->setString(std::to_string(reward));
                //显示好感ui
                rewardGoodwill->setVisible(true);
                nowGoodwill->setVisible(true);
                
                return;
            }
        }

        // 检查是否点击了 closeButton
        Vec2 closeButtonPosition = closeButton->getPosition();
        Size closeButtonSize = closeButton->getContentSize();
        Rect closeButtonBoundingBox = Rect(closeButtonPosition.x - closeButtonSize.width,
            closeButtonPosition.y,
            closeButtonSize.width, closeButtonSize.height);

        if (closeButtonBoundingBox.containsPoint(mousePosition))
        {
            // 如果点击了 closeButton，切换到按下状态的图片
            closeButton->setNormalImage(Sprite::create("ui/close_pressed.png"));
            return;
        }

        // 检查是否点击了 submitButton
        Vec2 submitButtonPosition = submitButton->getPosition();
        Size submitButtonSize = submitButton->getContentSize();
        Rect submitButtonBoundingBox = Rect(submitButtonPosition.x - submitButtonSize.width/2,
            submitButtonPosition.y- submitButtonSize.height,
            submitButtonSize.width, submitButtonSize.height);

        if (submitButtonBoundingBox.containsPoint(mousePosition))
        {
            // 如果点击了 submitButton，切换到按下状态的图片
            submitButton->setNormalImage(Sprite::create("ui/submit_pressed.png"));
            return;
        }
    };

    // 鼠标释放事件
    mouseListener->onMouseUp = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // 获取摄像头的偏移量
        Vec2 cameraOffset = this->getParent()->getPosition();

        // 将鼠标坐标转换为相对于场景的坐标
        mousePosition -= cameraOffset;

        //获取任务界面信息
        auto TaskUISize = taskUI->getContentSize();
        auto TsakUIPos = taskUI->getPosition();

        // 检查是否点击了 closeButton
        Vec2 closeButtonPosition = closeButton->getPosition();
        Size closeButtonSize = closeButton->getContentSize();
        Rect closeButtonBoundingBox = Rect(closeButtonPosition.x - closeButtonSize.width,
            closeButtonPosition.y,
            closeButtonSize.width, closeButtonSize.height);

        if (closeButtonBoundingBox.containsPoint(mousePosition))
        {
            // 如果点击了 closeButton，切换回正常状态的图片并隐藏任务层
            closeButton->setNormalImage(Sprite::create("ui/close_normal.png"));
            closeTaskUI(nullptr); // 隐藏任务层

            //更换图片
            for (auto list : lists) {
                if (static_cast<NPCTask*>(list->getUserData())->getNPCName() == "Alice") {
                    list->setTexture("ui/Alice_task.png");
                }
                else if (static_cast<NPCTask*>(list->getUserData())->getNPCName() == "Bob") {
                    list->setTexture("ui/Bob_task.png");
                }
                else if (static_cast<NPCTask*>(list->getUserData())->getNPCName() == "Mary") {
                    list->setTexture("ui/Mary_task.png");
                }
                else {
                    list->setTexture("ui/Annie_task.png");
                }
            }

            // 隐藏物品UI
            taskDetailsUi->setVisible(false);
            needItemDeta->setVisible(false);
            resultLabel->setVisible(false);

            //隐藏好感度ui
             //显示好感ui
            rewardGoodwill->setVisible(false);
            nowGoodwill->setVisible(false);


            // 解除提交按钮的绑定及可见
            submitButton->setUserData(nullptr);
            submitButton->setVisible(false);
        }
        else
        {
            // 如果触摸结束时不在按钮区域内，也切换回正常状态
            closeButton->setNormalImage(Sprite::create("ui/close_normal.png"));
        }

        // 检查是否点击了 submitButton
        if (submitButton) {
            Vec2 submitButtonPosition = submitButton->getPosition();
            Size submitButtonSize = submitButton->getContentSize();
            Rect submitButtonBoundingBox = Rect(submitButtonPosition.x - submitButtonSize.width/2,
                submitButtonPosition.y - submitButtonSize.height,
                submitButtonSize.width, submitButtonSize.height);

            if (submitButtonBoundingBox.containsPoint(mousePosition))
            {
                // 如果点击了 submitButton，切换回正常状态的图片并执行逻辑
                submitButton->setNormalImage(Sprite::create("ui/submit_normal.png"));
                submitButton->activate(); // 执行逻辑
            }
            else
            {
                // 如果触摸结束时不在按钮区域内，也切换回正常状态
                submitButton->setNormalImage(Sprite::create("ui/submit_normal.png"));
            }
        }
        };


    //更新物品位置
    this->renewPosition();

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}