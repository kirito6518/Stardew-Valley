#include "TaskLayer.h"
#include "TaskManager.h"
#include "SimpleAudioEngine.h"
#include "ShopItemManager.h"

USING_NS_CC;
using namespace CocosDenshion;

// ���������б��
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

// ��ʼ�������б��
bool TaskLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // ��ȡ��������
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ��ʼ�������������
    taskDetailsUI = Sprite::create("ui/task_details_bg.png");
    taskDetailsUI->setAnchorPoint(Vec2(0.5, 0.5));
    taskDetailsUI->setPosition(visibleSize / 2);
    taskDetailsUI->setVisible(false);
    this->addChild(taskDetailsUI, 2);

    // ��ʼ�����������ǩ
    taskDetailsLabel = Label::createWithTTF("", "fonts/Gen.ttf", 25);
    taskDetailsLabel->setAnchorPoint(Vec2(0, 1));
    taskDetailsLabel->setVisible(false);
    this->addChild(taskDetailsLabel, 3);

    // �����رհ�ť
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

    // �������¼�������
    setupMouseListener();

    return true;
}

// �������б����������
void TaskLayer::addTask(const std::string& npcName, const std::string& taskDescription)
{
    
}

// �Ƴ�����
void TaskLayer::removeTask(const std::string& npcName)
{
    //tasks.erase(npcName);
}

// ��ʾ��������
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

// ������������
void TaskLayer::hideTaskDetails()
{
    taskDetailsUI->setVisible(false);
    taskDetailsLabel->setVisible(false);
    closeButton->setVisible(false);
}

// ��������¼�������
void TaskLayer::setupMouseListener()
{
    auto mouseListener = EventListenerMouse::create();

    // ������¼�
    mouseListener->onMouseDown = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // �������� NPC ���ƣ��������Ƿ�����ĳ�� NPC
        /*for (auto& taskPair : tasks)
        {
            auto npcName = taskPair.first;

            // ��ȡ NPC ���Ʊ�ǩ������
            auto npcLabel = Label::createWithTTF(npcName, "fonts/Gen.ttf", 25);
            npcLabel->setPosition(Vec2(100, 500 - 50 * std::distance(tasks.begin(), tasks.find(npcName))));

            // ���� NPC ���Ʊ�ǩ�ı߽��
            Rect npcBoundingBox = Rect(npcLabel->getPosition().x, npcLabel->getPosition().y, npcLabel->getContentSize().width, npcLabel->getContentSize().height);

            if (npcBoundingBox.containsPoint(mousePosition))
            {
                // ��ʾ��������
                showTaskDetails(npcName);
                return;
            }
        }*/
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}