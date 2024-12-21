#include "TaskLayer.h"
#include "TaskManager.h"
#include "TaskItem.h"
#include "TaskItemManager.h"
#include "MainMap.h"
#include "NPCtask.h"
#include "NPCManager.h"
#include "NPC.h"
USING_NS_CC;


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
    taskUI = Sprite::create("ui/task.png");
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
    this->addChild(closeButton,4);

    //������������UI
    taskDetailsUi = Sprite::create("ui/task_detailsUI.png");
    taskDetailsUi->setAnchorPoint(Vec2(0, 0.5));
    taskDetailsUi->setPosition(TsakUIPos);
    taskDetailsUi -> setVisible(false);
    this->addChild(taskDetailsUi, 5);

    //����������Ʒ������ǩ
    needItemDeta =Label::createWithTTF("", "fonts/Gen.ttf", 30);
    needItemDeta->setAnchorPoint(Vec2(0, 0.5));
    needItemDeta->setVisible(false);
    this->addChild(needItemDeta, 6);

    //���������øжȱ�ǩ
    rewardGoodwill= Label::createWithTTF("10", "fonts/Gen.ttf", 30);
    rewardGoodwill->setAnchorPoint(Vec2(0, 0.5));
    rewardGoodwill->setVisible(false);
    this->addChild(rewardGoodwill, 6);

    //�������кøжȱ�ǩ
    nowGoodwill = Label::createWithTTF("", "fonts/Gen.ttf", 30);
    nowGoodwill->setAnchorPoint(Vec2(0, 0.5));
    nowGoodwill->setVisible(false);
    this->addChild(nowGoodwill, 6);

    //�����ύ��ť
    submitButton = MenuItemImage::create(
        "ui/submit_normal.png",
        "ui/submit_pressed.png",
        CC_CALLBACK_1(TaskLayer::onSubmitButton, this));
    submitButton->setAnchorPoint(Vec2(0.5, 1));
    submitButton->setVisible(false);
    submitButton->setEnabled(false);//Ĭ�Ϲر���������
    this->addChild(submitButton, 6);

    //�����ύ�����ǩ
    resultLabel = Label::createWithTTF("", "fonts/Gen.ttf", 30);
    resultLabel->setAnchorPoint(Vec2(0.5, 0.5));
    resultLabel->setPosition(TsakUIPos);
    resultLabel->setVisible(false);
    this->addChild(resultLabel, 7);


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
    taskList->removeFromParentAndCleanup(false);
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
        int y = startY - count * space;
        list->setPosition(Vec2(x, y));
        count++;
    }

    //��������uiλ��
    closeButton->setPosition(Vec2(TsakUIPos.x + TaskUISize.width, TsakUIPos.y + TaskUISize.height / 2));
    taskDetailsUi->setPosition(TsakUIPos);
    needItemDeta->setPosition(TsakUIPos + Vec2(150,-98));
    submitButton->setPosition(TsakUIPos + Vec2(TaskUISize.width/2+155, -TaskUISize.height / 2+100));
    resultLabel->setPosition(TsakUIPos+Vec2(100,0));
    rewardGoodwill->setPosition(TsakUIPos + Vec2(262, -192));
    nowGoodwill->setPosition(TsakUIPos + Vec2(262, -148));

}

//�رհ�ť�Ļص�����
void TaskLayer::closeTaskUI(Ref* sender)
{
    TaskManager::getInstance()->hideTaskList();

    // ����mainmap�Ļָ�ʱ����µĺ���
    dynamic_cast<MainMap*>(TaskManager::getInstance()->mainMap)->hideBackpack(sender);
}

//�ύ��ť�Ļص�����
void TaskLayer::onSubmitButton(Ref* sender)
{
    auto list = static_cast<Sprite*>(submitButton->getUserData());

    if (list)
    {
        auto task = static_cast<NPCTask*>(list->getUserData());
        bool success = task->canComplete();//����Ƿ��ܹ��������

        if (success)
        {
            task->complete();//�������
            std::string getItem = task->getNeedItemName();
            // ��ȡ�����е�������Ʒ
            auto item = BackpackManager::getInstance()->getItemByName(getItem);
            // �ӱ����м���������Ʒ
            item->decreaseCount(task->getNeedItemCount());
            resultLabel->setString("Submit Success!");
            TaskManager::getInstance()->renewTask();
            //������ϸ��Ϣui
            taskDetailsUi->setVisible(false);

            //������Ҫ��Ʒ��Ϣ
            needItemDeta->setVisible(false);

            //�����ύ��ť
            submitButton->setVisible(false);
            submitButton->setEnabled(false);

            //���غøж�ui
            rewardGoodwill->setVisible(false);    
            nowGoodwill->setVisible(false);
        }
        else
        {
            resultLabel->setString("You Don't Have enough Items Left!");
        }

        resultLabel->setVisible(true);

        //������Ʒλ��
        this->renewPosition();

        this->scheduleOnce([this](float dt) {
            resultLabel->setVisible(false);
            }, 1.0f, "hide_result");
    }
}

// ��������¼�������
void TaskLayer::setupMouseListener()
{
    // �Ƴ�֮ǰ�󶨵��¼�������
    _eventDispatcher->removeEventListenersForTarget(this);

    auto mouseListener = EventListenerMouse::create();

    //������Ʒλ��
    this->renewPosition();

    // ������¼�
    mouseListener->onMouseDown = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // ��ȡ����ͷ��ƫ����
        Vec2 cameraOffset = this->getParent()->getPosition();

        // ���������ת��Ϊ����ڳ���������
        mousePosition -= cameraOffset;

        //��ȡ���������Ϣ
        auto TaskUISize = taskUI->getContentSize();
        auto TsakUIPos = taskUI->getPosition();

        // ��������listͼ�꣬�������Ƿ�����ĳ����Ʒ
        for (auto list : lists)
        {
            // ��ȡlist����ĵ�ǰ����
            Vec2 listPosition = list->getPosition();
            auto listSize = list->getContentSize();
            // ����list����ı߽��
            Rect listBoundingBox = Rect(listPosition.x-listSize.width, listPosition.y - listSize.height, 
                                           listSize.width, listSize.height);

            //��ȡ�������
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
                //��ʾ��ϸ��Ϣui
                taskDetailsUi->setPosition(TsakUIPos);
                taskDetailsUi->setVisible(true);
                
                //��ʾ��Ҫ��Ʒ��Ϣ
                std::string deta;
                deta = std::to_string(task->getNeedItemCount())+"   " + task->getNeedItemName();
                needItemDeta->setString(deta);
                needItemDeta->setVisible(true);

                //��ʾ�ύ��ť
                submitButton->setUserData(list); // ��list�������ύ��ť����
                submitButton->setVisible(true);
                submitButton->setEnabled(true);

                //��ȡ��ǰ�ø�
                std::string name=task->getNPCName();
                int goodwill = NPCManager::getInstance()->getNPCByName(name)->getFavorability();
                nowGoodwill->setString(std::to_string(goodwill));

                //��ȡ�����ø�
                int reward = task->getNeedItemCount() * 2;
                rewardGoodwill->setString(std::to_string(reward));
                //��ʾ�ø�ui
                rewardGoodwill->setVisible(true);
                nowGoodwill->setVisible(true);
                
                return;
            }
        }

        // ����Ƿ����� closeButton
        Vec2 closeButtonPosition = closeButton->getPosition();
        Size closeButtonSize = closeButton->getContentSize();
        Rect closeButtonBoundingBox = Rect(closeButtonPosition.x - closeButtonSize.width,
            closeButtonPosition.y,
            closeButtonSize.width, closeButtonSize.height);

        if (closeButtonBoundingBox.containsPoint(mousePosition))
        {
            // �������� closeButton���л�������״̬��ͼƬ
            closeButton->setNormalImage(Sprite::create("ui/close_pressed.png"));
            return;
        }

        // ����Ƿ����� submitButton
        Vec2 submitButtonPosition = submitButton->getPosition();
        Size submitButtonSize = submitButton->getContentSize();
        Rect submitButtonBoundingBox = Rect(submitButtonPosition.x - submitButtonSize.width/2,
            submitButtonPosition.y- submitButtonSize.height,
            submitButtonSize.width, submitButtonSize.height);

        if (submitButtonBoundingBox.containsPoint(mousePosition))
        {
            // �������� submitButton���л�������״̬��ͼƬ
            submitButton->setNormalImage(Sprite::create("ui/submit_pressed.png"));
            return;
        }
    };

    // ����ͷ��¼�
    mouseListener->onMouseUp = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // ��ȡ����ͷ��ƫ����
        Vec2 cameraOffset = this->getParent()->getPosition();

        // ���������ת��Ϊ����ڳ���������
        mousePosition -= cameraOffset;

        //��ȡ���������Ϣ
        auto TaskUISize = taskUI->getContentSize();
        auto TsakUIPos = taskUI->getPosition();

        // ����Ƿ����� closeButton
        Vec2 closeButtonPosition = closeButton->getPosition();
        Size closeButtonSize = closeButton->getContentSize();
        Rect closeButtonBoundingBox = Rect(closeButtonPosition.x - closeButtonSize.width,
            closeButtonPosition.y,
            closeButtonSize.width, closeButtonSize.height);

        if (closeButtonBoundingBox.containsPoint(mousePosition))
        {
            // �������� closeButton���л�������״̬��ͼƬ�����������
            closeButton->setNormalImage(Sprite::create("ui/close_normal.png"));
            closeTaskUI(nullptr); // ���������

            //����ͼƬ
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

            // ������ƷUI
            taskDetailsUi->setVisible(false);
            needItemDeta->setVisible(false);
            resultLabel->setVisible(false);

            //���غøж�ui
             //��ʾ�ø�ui
            rewardGoodwill->setVisible(false);
            nowGoodwill->setVisible(false);


            // ����ύ��ť�İ󶨼��ɼ�
            submitButton->setUserData(nullptr);
            submitButton->setVisible(false);
        }
        else
        {
            // �����������ʱ���ڰ�ť�����ڣ�Ҳ�л�������״̬
            closeButton->setNormalImage(Sprite::create("ui/close_normal.png"));
        }

        // ����Ƿ����� submitButton
        if (submitButton) {
            Vec2 submitButtonPosition = submitButton->getPosition();
            Size submitButtonSize = submitButton->getContentSize();
            Rect submitButtonBoundingBox = Rect(submitButtonPosition.x - submitButtonSize.width/2,
                submitButtonPosition.y - submitButtonSize.height,
                submitButtonSize.width, submitButtonSize.height);

            if (submitButtonBoundingBox.containsPoint(mousePosition))
            {
                // �������� submitButton���л�������״̬��ͼƬ��ִ���߼�
                submitButton->setNormalImage(Sprite::create("ui/submit_normal.png"));
                submitButton->activate(); // ִ���߼�
            }
            else
            {
                // �����������ʱ���ڰ�ť�����ڣ�Ҳ�л�������״̬
                submitButton->setNormalImage(Sprite::create("ui/submit_normal.png"));
            }
        }
        };


    //������Ʒλ��
    this->renewPosition();

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}