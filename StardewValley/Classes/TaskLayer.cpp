#include "TaskLayer.h"
#include "TaskManager.h"
#include "NPCManager.h" // ������һ������ NPC �øжȵ���

USING_NS_CC;

// ���������
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

// ��ʼ�������
bool TaskLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // ��ȡ��������
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // �������񱳾�ͼƬ
    taskBgSprite = Sprite::create("ui/task_bg.png");
    taskBgSprite->setAnchorPoint(Vec2(0.5, 0.5));
    taskBgSprite->setPosition(visibleSize / 2);
    this->addChild(taskBgSprite, 2);

    // ��ʼ�������ǩ
    taskLabel = Label::createWithTTF("", "fonts/Gen.ttf", 20);
    taskLabel->setAnchorPoint(Vec2(0, 1));
    taskLabel->setVisible(false);
    this->addChild(taskLabel, 3);

    // ��ʼ����ɰ�ť
    completeButton = MenuItemImage::create(
        "ui/complete_button_normal.png",
        "ui/complete_button_pressed.png",
        CC_CALLBACK_1(TaskLayer::completeTask, this));
    completeButton->setAnchorPoint(Vec2(1, 1));
    completeButton->setPosition(Vec2(visibleSize.width / 2 + 50, visibleSize.height / 2 - 50));
    this->addChild(completeButton, 3);
    completeButton->setEnabled(false);

    // �������¼�������
    setupMouseListener();

    return true;
}

// ������������
void TaskLayer::addTask(NPCTask* task)
{
    taskList.pushBack(task);
    updateTaskUI(task);
}

// �Ƴ�����
void TaskLayer::removeTask(NPCTask* task)
{
    taskList.eraseObject(task);
    task->removeFromParent();
}

// ��������UI
void TaskLayer::updateTaskUI(NPCTask* task)
{
    // ��ʾ������Ϣ
    std::string taskInfo = task->getDescription() + "\nRequired: " + task->getRequiredItem() + " x" + std::to_string(task->getRequiredItemCount());
    taskLabel->setString(taskInfo);
    taskLabel->setPosition(taskBgSprite->getPosition() + Vec2(0, 50));
    taskLabel->setVisible(true);

    // ��ʾ��ɰ�ť
    completeButton->setUserData(task);
    completeButton->setVisible(true);
    completeButton->setEnabled(!task->isOnCooldown()); // �����������ȴ�У����ð�ť
}

// �������Ļص�����
void TaskLayer::onTaskClicked(NPCTask* task)
{
    // ��ʾ������ϸ��Ϣ
    taskLabel->setString(task->getDescription());
    taskLabel->setPosition(taskBgSprite->getPosition() + Vec2(0, 50));
    taskLabel->setVisible(true);

    // ��ʾ��ɰ�ť
    completeButton->setUserData(task);
    completeButton->setVisible(true);
    completeButton->setEnabled(!task->isOnCooldown()); // �����������ȴ�У����ð�ť
}

// �������
void TaskLayer::completeTask(Ref* sender)
{
    auto task = static_cast<NPCTask*>(completeButton->getUserData());

    if (task)
    {
        // ��������Ƿ�������
        if (task->canComplete())
        {
            // ����������� NPC �øж�
            task->complete();
            //NPCManager::getInstance()->increaseAffinity(task->getNPCName());

            // ��������UI
            taskLabel->setVisible(false);
            completeButton->setVisible(false);
            completeButton->setEnabled(false);

            // ��ʾ�������
            taskLabel->setString("Task Completed!");
            taskLabel->setVisible(true);

            // ����������ȴʱ��
            task->setCooldown(60.0f); // ������ȴʱ��Ϊ 60 ��
        }
        else
        {
            // ��ʾ�����޷����
            taskLabel->setString("Cannot complete task!");
        }
    }
}

// �������¼���������Ԫ�صĽ���
void TaskLayer::setupMouseListener()
{
    auto mouseListener = EventListenerMouse::create();

    // ����ƶ��¼�
    mouseListener->onMouseMove = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // �����������񣬼������Ƿ���ͣ��ĳ��������
        for (auto task : taskList)
        {
            Vec2 taskPosition = task->getPosition();
            Rect taskBoundingBox = Rect(taskPosition.x, taskPosition.y - 50, 200, 50);

            if (taskBoundingBox.containsPoint(mousePosition))
            {
                // ��ʾ��������
                taskLabel->setString(task->getDescription());
                taskLabel->setPosition(taskPosition + Vec2(0, 30));
                taskLabel->setVisible(true);
                return;
            }
        }

        // �����겻���κ������ϣ�������������
        taskLabel->setVisible(false);
        };

    // ������¼�
    mouseListener->onMouseDown = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // �����������񣬼������Ƿ�����ĳ������
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