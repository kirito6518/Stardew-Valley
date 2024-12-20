#include "TaskLayer.h"
#include "TaskManager.h"
#include "SimpleAudioEngine.h"
#include "TaskItem.h"
#include "TaskItemManager.h"
#include "MainMap.h"
#include "NPCtask.h"

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

    // ��ʼ���������
    taskUI = Sprite::create("ui/taskUI.png");
    taskUI->setAnchorPoint(Vec2(0, 0.5));
    taskUI->setPosition(Vec2(visibleSize.width/2-100, visibleSize.height/2));
    this->addChild(taskUI, 4);

    //��ȡ���������Ϣ
    auto TaskUISize = taskUI->getContentSize();
    auto TsakUIPos = taskUI->getPosition();

    // �����رհ�ť
    closeButton = MenuItemImage::create(
        "ui/close_normal.png",
        "ui/close_pressed.png",
        CC_CALLBACK_1(TaskLayer::closeTaskUI, this));
    closeButton->setAnchorPoint(Vec2(1, 0));
    closeButton->setPosition(Vec2(TsakUIPos.x+ TaskUISize.width, TsakUIPos.y+ TaskUISize.height/2));
    closeButton->setVisible(false);
    this->addChild(closeButton,4);

    //������������UI
    taskDetailsUi = Sprite::create("ui/task_detailsUI.png");
    taskDetailsUi->setAnchorPoint(Vec2(0, 0.5));
    taskDetailsUi->setPosition(TsakUIPos);
    taskDetailsUi -> setVisible(false);
    this->addChild(taskUI, 5);

    //����������Ʒ����
    needItem = Sprite::create();
    needItem->setAnchorPoint(Vec2(0, 0.5));
    needItem->setPosition(TsakUIPos+Vec2(300,-400));
    needItem->setVisible(false);
    this->addChild(taskUI, 6);

    //����������Ʒ������ǩ
    needItemCount =Label::createWithTTF("", "fonts/Gen.ttf", 30);
    needItemCount->setAnchorPoint(Vec2(0, 0.5));
    needItemCount->setPosition(TsakUIPos + Vec2(350, -400));
    needItemCount->setVisible(false);
    this->addChild(needItemCount, 6);

    //�����ύ��ť
    submitButton = MenuItemImage::create(
        "ui/CloseNormal.png",
        "ui/CloseSelected.png",
        CC_CALLBACK_1(TaskLayer::closeTaskUI, this));
    submitButton->setAnchorPoint(Vec2(1, 0));
    submitButton->setPosition(TsakUIPos+Vec2(400, -500));
    submitButton->setVisible(false);
    this->addChild(submitButton, 6);

    //�����ύ�ɹ���ǩ
    submitSuccess = Label::createWithTTF("Submit Success!", "fonts/Gen.ttf", 30);
    submitSuccess->setAnchorPoint(Vec2(0.5, 0.5));
    submitSuccess->setPosition(TsakUIPos);
    submitSuccess->setVisible(false);
    this->addChild(submitSuccess, 7);

    //�����ύʧ�ܱ�ǩ
    submitFailed = Label::createWithTTF("You Don't Have Enough Item!", "fonts/Gen.ttf", 30);
    submitFailed->setAnchorPoint(Vec2(0.5, 0.5));
    submitFailed->setPosition(TsakUIPos);
    submitFailed->setVisible(false);
    this->addChild(submitFailed, 7);

    // �������¼�������
    setupMouseListener();

    return true;
}


//��������б�layer��
bool TaskLayer::addList(Sprite* taskList)
{

    //��ȡ���������Ϣ
    auto TaskUISize = taskUI->getContentSize();
    auto TsakUIPos = taskUI->getPosition();


    taskList->setAnchorPoint(Vec2(1, 1));
    taskList->setPosition(Vec2(TsakUIPos.x, TsakUIPos.y+ TaskUISize.height/2));
    // ��List��ӵ������
    this->addChild(taskList, 4);
    lists.pushBack(taskList);


    return true;
}

// �Ƴ��б�
void TaskLayer::removeItem(Sprite* taskList)
{

    lists.eraseObject(taskList);
    taskList->removeFromParent();
}

//����λ��
void TaskLayer::renewPosition()
{
    //��ȡ���������Ϣ
    auto TaskUISize = taskUI->getContentSize();
    auto TsakUIPos = taskUI->getPosition();

    //����listλ��
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

    //��������uiλ��
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

    // ����mainmap�Ļָ�ʱ����µĺ���
    dynamic_cast<MainMap*>(TaskManager::getInstance()->mainMap)->hideBackpack(sender);
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