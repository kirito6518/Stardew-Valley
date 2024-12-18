#include "BackpackLayer.h"
#include "BackpackManager.h"
#include "Item.h"
#include "AppDelegate.h"
#include "MainMap.h"
#include "ItemManager.h"


USING_NS_CC;



// ����������
BackpackLayer* BackpackLayer::create(const std::string& backpackBgPath, int maxItems)
{
    auto layer = new (std::nothrow) BackpackLayer();
    if (layer && layer->init(backpackBgPath, maxItems))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

// ��ʼ��������
bool BackpackLayer::init(const std::string& backpackBgPath, int maxItems)
{
    if (!Layer::init())
    {
        return false;
    }

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ���ر�������ͼƬ
    backpackBgSprite = Sprite::create(backpackBgPath);
    if (!backpackBgSprite)
    {
        CCLOG("Failed to load backpack background image: %s", backpackBgPath.c_str());
        return false;
    }

    backpackBgSprite->setAnchorPoint(Vec2(0.5, 0.5));
    backpackBgSprite->setPosition(visibleSize / 2);
    this->addChild(backpackBgSprite, 2);

    //��ȡ��������ͼ�ߴ缰����
    auto backpackSize = backpackBgSprite->getContentSize();
    auto backpackPos = backpackBgSprite->getPosition();

    // �����رհ�ť
    hideButton = MenuItemImage::create(
        "ui/close_normal.png",
        "ui/close_pressed.png",
        CC_CALLBACK_1(BackpackLayer::hideBackpack, this));

    if (!hideButton)
    {
        CCLOG("Failed to create hideButton!");
        return false;
    }

    hideButton->setAnchorPoint(Vec2(1, 0));
    hideButton->setPosition(Vec2(visibleSize.width / 2 + backpackSize.width / 2, visibleSize.height / 2 + backpackSize.height / 2));
    this->addChild(hideButton);

    // ��ʼ����������
    this->maxItems = maxItems;
    this->currentItems = 0;

    // ��ʼ����Ʒ���Ʊ�ǩ
    itemNameLabel = Label::createWithTTF("", "fonts/Gen.ttf", 20);
    itemNameLabel->setAnchorPoint(Vec2(0.5, 1));
    itemNameLabel->setVisible(false);
    this->addChild(itemNameLabel,3);

    //��ʼ��ʹ�ý����ǩ
    useResultLabel = Label::createWithTTF("", "fonts/Gen.ttf", 30);
    useResultLabel->setAnchorPoint(Vec2(0.5, 0.5));
    useResultLabel->setVisible(false);
    this->addChild(useResultLabel, 3);

    //��ʼ�����ٽ����ǩ
    destroyResultLabel = Label::createWithTTF("", "fonts/Gen.ttf", 30);
    destroyResultLabel->setAnchorPoint(Vec2(0.5, 0.5));
    destroyResultLabel->setVisible(false);
    this->addChild(destroyResultLabel, 3);

    //��ʼ����Ʒ��ϢUI
    itemDetaUI = Sprite::create("ui/itemDetaUI.png");
    itemDetaUI->setAnchorPoint(Vec2(1, 1));
    itemDetaUI->setVisible(false);
    this->addChild(itemDetaUI, 0);

    //��ʼ����Ʒ��Ϣ��ǩ
    itemDataLabel = Label::createWithTTF("", "fonts/Gen.ttf", 25);
    itemDataLabel->setAnchorPoint(Vec2(0, 1));
    itemDataLabel->setVisible(false);
    this->addChild(itemDataLabel, 3);


    //������Ʒʹ�ð�ť
    useButton = MenuItemImage::create(
        "ui/use_button_normal.png",  // ����״̬��ͼƬ
        "ui/use_button_pressed.png", // ����״̬��ͼƬ
        CC_CALLBACK_1(BackpackLayer::onUseButtonClicked, this)); // ����ص�����

    useButton->setAnchorPoint(Vec2(1, 1));  
    useButton->setPosition(Vec2(backpackPos.x - backpackSize.width / 2 - 20, backpackPos.y + 20));
    this->addChild(useButton,2);
    useButton->setVisible(false);
    // Ĭ�Ϲر� useButton ������¼�����
    useButton->setEnabled(false);

    //������Ʒ������ť
    destroyButton= MenuItemImage::create(
        "ui/sell_button_normal.png",  // ����״̬��ͼƬ
        "ui/sell_button_pressed.png", // ����״̬��ͼƬ
        CC_CALLBACK_1(BackpackLayer::onDestroyButtonClicked, this)); // ����ص�����
    destroyButton->setAnchorPoint(Vec2(1, 1));
    destroyButton->setPosition(Vec2(backpackPos.x - backpackSize.width / 2 - 20, backpackPos.y - 40));
    this->addChild(destroyButton,2);
    destroyButton->setVisible(false);
    // Ĭ�Ϲر� destroyButton ������¼�����
    destroyButton->setEnabled(false);

    //��ʼ��ȷ���Ƿ��۳���UI
    determineUI = Sprite::create("ui/determineUI.png");
    determineUI->setAnchorPoint(Vec2(0.5, 0.5));
    determineUI->setPosition(backpackPos);
    determineUI->setVisible(false);
    this->addChild(determineUI, 3);

    //��ʼ���۳��ɻ�ý����
    getCoinCount = Label::createWithTTF("", "fonts/Gen.ttf", 20);
    getCoinCount->setAnchorPoint(Vec2(0, 0));
    getCoinCount->setPosition(backpackPos+Vec2(50,-50));
    getCoinCount->setVisible(false);
    this->addChild(getCoinCount, 5);

    //��ʼ��yes��ť
    yesButton = MenuItemImage::create(
        "ui/yes_normal.png",  // ����״̬��ͼƬ
        "ui/yes_pressed.png", // ����״̬��ͼƬ
        CC_CALLBACK_1(BackpackLayer::onYesButtonClicked, this)); // ����ص�����
    yesButton->setAnchorPoint(Vec2(0, 0));
    yesButton->setPosition(backpackPos+Vec2(-100,-60));
    this->addChild(yesButton, 4);
    yesButton->setVisible(false);
    // Ĭ�Ϲر� destroyButton ������¼�����
    yesButton->setEnabled(false);

    //��ʼ��no��ť
    noButton = MenuItemImage::create(
        "ui/no_normal.png",  // ����״̬��ͼƬ
        "ui/no_pressed.png", // ����״̬��ͼƬ
        CC_CALLBACK_1(BackpackLayer::onNoButtonClicked, this)); // ����ص�����
    noButton->setAnchorPoint(Vec2(0, 0));
    noButton->setPosition(backpackPos + Vec2(100, -60));
    this->addChild(noButton, 4);
    noButton->setVisible(false);
    // Ĭ�Ϲر� destroyButton ������¼�����
    noButton->setEnabled(false);


    //�������¼�������
    setupCombinedMouseListener();

    // ��ʼ���������Ӳ���
    gridWidth = 80;
    gridHeight = 80;
    gridSpacing = 8;
    gridStartX = (visibleSize.width - backpackSize.width) / 2+8;
    gridStartY = (visibleSize.height + backpackSize.height) / 2-10;

    return true;
}

// �����Ʒ������
bool BackpackLayer::addItem(Sprite* itemSprite)
{
    if (currentItems >= maxItems)
    {
        CCLOG("Backpack is full! Cannot add more items.");
        return false;
    }

    auto backpackSize = backpackBgSprite->getContentSize();
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //��Ʒ��������ڳ�ʼ�����ƫ����
    int dx, dy;
    itemSprite->setAnchorPoint(Vec2(0, 1));


    // ȷ�� itemSprite û�и��ڵ�
    if (itemSprite->getParent() != nullptr)
    {
        CCLOG("Item sprite already has a parent!");
        return false;
    }

    dx = (currentItems % 10 )* (gridWidth + gridSpacing);
    dy = (currentItems / 10) * (gridHeight + gridSpacing);

    itemSprite->setPosition(Vec2(gridStartX +dx, gridStartY -dy));
    // ����Ʒͼ����ӵ�������
    this->addChild(itemSprite,2);
    itemSprites.pushBack(itemSprite);

    // Ϊ��Ʒͼ�������û����ݣ��� Item ����
    Item* item = static_cast<Item*>(itemSprite->getUserData());
    if (item)
    {
        itemSprite->setUserData(item);
    }

    currentItems++;
    return true;
}

// �Ƴ���Ʒ
void BackpackLayer::removeItem(Sprite* itemSprite)
{
    //������ƷUI
    itemDetaUI->setVisible(false);
    itemDataLabel->setVisible(false);

    //���ʹ�ð�ť�ʹݻٰ�ť�İ󶨼��ɼ�
    useButton->setUserData(nullptr);
    useButton->setVisible(false);
    destroyButton->setUserData(nullptr);
    destroyButton->setVisible(false);

    itemSprites.eraseObject(itemSprite);
    itemSprite->removeFromParentAndCleanup(false);
    currentItems--;
}

// ���ر���
void BackpackLayer::hideBackpack(Ref* sender)
{
    BackpackManager::getInstance()->hideBackpack();

    // ����mainmap�Ļָ�ʱ����µĺ���
    dynamic_cast<MainMap*>(BackpackManager::getInstance()->mainMap)->hideBackpack(sender);
}

//���±�������Ʒλ��
void BackpackLayer::renewPosition()
{
    //��ȡ��������ͼ�ߴ缰����
    auto backpackSize = backpackBgSprite->getContentSize();
    auto backpackPos = backpackBgSprite->getPosition();

    //���±�������Ʒλ��
    int dx, dy;   //��Ʒ��������ڱ�����ʼ�����ƫ����
    int Spcount = 0;
    int Itemcount = 0;
    auto parent = this->getParent();
    Vec2 cameraOffset = Vec2(0, 0);
    if (parent) {
        cameraOffset = parent->getPosition();
    }
    const cocos2d::Vector<Sprite*>& Itemsprites = getItemSprites();
    for (auto Itemsprite : Itemsprites)
    {
        dx = Spcount % 10 * (gridWidth + gridSpacing);
        dy = Spcount / 10 * (gridHeight + gridSpacing);
        Itemsprite->setPosition(backpackPos + Vec2(-backpackSize.width / 2 + dx + 8, backpackSize.height / 2 - dy - 10));
        Spcount++;
    }

    determineUI->setPosition(backpackPos);
    getCoinCount->setPosition(backpackPos + Vec2(90, -22));
    yesButton->setPosition(backpackPos + Vec2(-150, -90));
    noButton->setPosition(backpackPos + Vec2(30, -90));

}

//���ʹ�ð�ť�Ļص�����
void BackpackLayer::onUseButtonClicked(Ref* sender)
{
    destroyResultLabel->setVisible(false);

    auto item = static_cast<Item*>(useButton->getUserData());

    if (item)
    {
        bool success = item->useItem();

        if (success)
        {
            useResultLabel->setString("Use Success!");
        }
        else
        {
            useResultLabel->setString("You Can't Use This Item Now!");
        }

        useResultLabel->setVisible(true);

        this->renewPosition();//������Ʒλ��

        this->scheduleOnce([this](float dt) {
            useResultLabel->setVisible(false);
            }, 1.0f, "hide_use_result");
    }
}

//���yes��ť�Ļص�����
void BackpackLayer::onYesButtonClicked(Ref* sender)
{
    useResultLabel->setVisible(false);

    //������Ʒ
    auto item = static_cast<Item*>(destroyButton->getUserData());//��ȡ��Ӧ��Ʒ

    int itemcount = item->getCount();
    if (item->getitemCategory() != ItemCategory::Tool) {//�����Ʒ�����ڹ����ࣨ���ɱ�������
        if (this->getParent() != nullptr) {
            auto itemCoin = ItemManager::getInstance()->getItem("Coin");
            int money = (item->getsellingPrice()) * itemcount;
            itemCoin->increaseCount(money);
            if (itemCoin->getCount() > 0) {
                BackpackManager::getInstance()->addItem(itemCoin, 0);
            }
        }

        item->clearItem();//�Ƴ���Ʒ

        destroyResultLabel->setString("Sell Success!");

    }
    else {
        destroyResultLabel->setString("You Can't Sell This Item!");
    }

    this->renewPosition();//������Ʒλ��

    //��ʾ�����ǩ
    destroyResultLabel->setVisible(true);
    this->scheduleOnce([this](float dt) {
        destroyResultLabel->setVisible(false);
        }, 1.0f, "hide_use_result");

    //�˳���ӦUI��ȡ������
    determineUI->setVisible(false);
    yesButton->setVisible(false);
    noButton->setVisible(false);
    getCoinCount->setVisible(false);
    yesButton->setEnabled(true);
    noButton->setEnabled(true);
}

//���no��ť�Ļص�����
void BackpackLayer::onNoButtonClicked(Ref* sender)
{

    //�˳���ӦUI��ȡ������
    determineUI->setVisible(false);
    yesButton->setVisible(false);
    noButton->setVisible(false);
    getCoinCount->setVisible(false);
    yesButton->setEnabled(true);
    noButton->setEnabled(true);

}

//���������ť�Ļص�����
void BackpackLayer::onDestroyButtonClicked(Ref* sender)
{

    useResultLabel->setVisible(false);

    // ���ض�Ӧ����Ʒ��ʾ��Ϣ�������������¼�����
    useResultLabel->setVisible(false);
    destroyResultLabel->setVisible(false);
    destroyButton->setEnabled(false);
    useButton->setEnabled(false);

    auto item = static_cast<Item*>(destroyButton->getUserData());//��ȡ��Ӧ��Ʒ

    std::string getCoinCountStr = std::to_string(item->getsellingPrice());
    getCoinCount->setString(getCoinCountStr);

    //��ʾ��ӦUI�������������¼�����
    determineUI->setVisible(true);
    getCoinCount->setVisible(true);
    yesButton->setVisible(true);
    noButton->setVisible(true);
    yesButton->setEnabled(true);
    noButton->setEnabled(true);


}

//�������¼��뱳����Ԫ�صĽ���
void BackpackLayer::setupCombinedMouseListener()
{
    // �Ƴ�֮ǰ�󶨵��¼�������
    _eventDispatcher->removeEventListenersForTarget(this);

    //���±�������Ʒλ��
    this->renewPosition();

    auto mouseListener = EventListenerMouse::create();

    // ����ƶ��¼�
    mouseListener->onMouseMove = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // ��ȡ����ͷ��ƫ����
        Vec2 cameraOffset = this->getParent()->getPosition();

        // ���������ת��Ϊ����ڳ���������
        mousePosition -= cameraOffset;

        // ����������Ʒͼ�꣬�������Ƿ���ͣ��ĳ����Ʒ��
        for (auto itemSprite : itemSprites)
        {
            // ��ȡ��Ʒ����ĵ�ǰ����
            Vec2 itemPosition = itemSprite->getPosition();
            //��ȡ��Ʒ����ߴ�
            Vec2 itemSize = itemSprite->getContentSize();
            // ������Ʒ����ı߽��
            Rect itemBoundingBox = Rect(itemPosition.x, itemPosition.y - gridHeight, gridWidth, gridHeight);

            if (itemBoundingBox.containsPoint(mousePosition))
            {
                // ��ȡ��Ʒ����
                Item* item = static_cast<Item*>(itemSprite->getUserData());
                if (item)
                {
                    // ��ʾ��Ʒ����
                    itemNameLabel->setString(item->getName());
                    itemNameLabel->setPosition(itemPosition + Vec2(itemSize.x/2, 25)); // ����Ʒλ���Ϸ���ʾ
                    itemNameLabel->setVisible(true);
                }
                return;
            }
        }

        // �����겻���κ���Ʒ�ϣ�������Ʒ����
        itemNameLabel->setVisible(false);
        };

    // ������¼�
    mouseListener->onMouseDown = [this](Event* event) {

        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // ��ȡ��������ͼ�ߴ缰����
        auto backpackSize = backpackBgSprite->getContentSize();
        auto backpackPos = backpackBgSprite->getPosition();

        // ��ȡ����ͷ��ƫ����
        Vec2 cameraOffset = this->getParent()->getPosition();

        // ���������ת��Ϊ����ڳ���������
        mousePosition -= cameraOffset;

        // ����Ƿ����� hideButton
        Vec2 hideButtonPosition = hideButton->getPosition();
        Size hideButtonSize = hideButton->getContentSize();
        Rect hideButtonBoundingBox = Rect(hideButtonPosition.x - hideButtonSize.width,
            hideButtonPosition.y,
            hideButtonSize.width, hideButtonSize.height);

        if (hideButtonBoundingBox.containsPoint(mousePosition))
        {
            // �������� hideButton���л�������״̬��ͼƬ
            hideButton->setNormalImage(Sprite::create("ui/close_pressed.png"));
            return;
        }


        //  ����Ƿ����� useButton
        if (useButton->isVisible()) {
            Vec2 useButtonPosition = useButton->getPosition();
            Size useButtonSize = useButton->getContentSize();
            Rect useButtonBoundingBox = Rect(useButtonPosition.x - useButtonSize.width,
                useButtonPosition.y - useButtonSize.height,
                useButtonSize.width, useButtonSize.height);

            if (useButtonBoundingBox.containsPoint(mousePosition))
            {
                // �������� useButton���л�������״̬��ͼƬ
                useButton->setNormalImage(Sprite::create("ui/use_button_pressed.png"));
                return;
            }
        }


        //  ����Ƿ����� destroyButton
        if (destroyButton->isVisible()) {
            Vec2 destroyButtonPosition = destroyButton->getPosition();
            Size destroyButtonSize = destroyButton->getContentSize();
            Rect destroyButtonBoundingBox = Rect(destroyButtonPosition.x - destroyButtonSize.width,
                destroyButtonPosition.y - destroyButtonSize.height,
                destroyButtonSize.width, destroyButtonSize.height);

            if (destroyButtonBoundingBox.containsPoint(mousePosition))
            {
                // �������� destroyButton���л�������״̬��ͼƬ
                destroyButton->setNormalImage(Sprite::create("ui/sell_button_pressed.png"));
                return;
            }
        }

        //  ����Ƿ����� yesButton
        if (yesButton->isVisible()) {
            Vec2 yesButtonPosition = yesButton->getPosition();
            Size yesButtonSize = yesButton->getContentSize();
            Rect yesButtonBoundingBox = Rect(yesButtonPosition.x, yesButtonPosition.y, yesButtonSize.width, yesButtonSize.height);

            if (yesButtonBoundingBox.containsPoint(mousePosition))
            {
                // ��������yesButton���л�������״̬��ͼƬ
                yesButton->setNormalImage(Sprite::create("ui/yes_pressed.png"));
                return;
            }
        }

        //  ����Ƿ����� noButton
        if (noButton->isVisible()) {
            Vec2 noButtonPosition = noButton->getPosition();
            Size noButtonSize = noButton->getContentSize();
            Rect noButtonBoundingBox = Rect(noButtonPosition.x, noButtonPosition.y, noButtonSize.width, noButtonSize.height);

            if (noButtonBoundingBox.containsPoint(mousePosition))
            {
                // ��������yesButton���л�������״̬��ͼƬ
                noButton->setNormalImage(Sprite::create("ui/no_pressed.png"));
                return;
            }
        }

        

        // ����������Ʒͼ�꣬�������Ƿ�����ĳ����Ʒ
        for (auto itemSprite : itemSprites)
        {
            // ��ȡ��Ʒ����ĵ�ǰ����
            Vec2 itemPosition = itemSprite->getPosition();
            // ������Ʒ����ı߽��
            Rect itemBoundingBox = Rect(itemPosition.x, itemPosition.y - gridHeight, gridWidth, gridHeight);

            if (itemBoundingBox.containsPoint(mousePosition))
            {
                // ��ȡ��Ʒ����
                Item* item = static_cast<Item*>(itemSprite->getUserData());
                if (item)
                {

                    //��ʾ��ƷUI
                    itemDetaUI->setVisible(true);
                    itemDetaUI->setPosition(Vec2(backpackPos.x - backpackSize.width / 2 , backpackPos.y + backpackSize.height/2));// �ڱ��������ʾ

                    //��ʾ��Ʒ��Ϣ��ǩ
                    itemDataLabel->setString(item->getName());
                    itemDataLabel->setVisible(true);
                    itemDataLabel->setPosition(Vec2(backpackPos.x - backpackSize.width / 2- itemDetaUI->getContentSize().width+25,
                        backpackPos.y + backpackSize.height / 2-25));// �ڱ��������ʾ

                    // ��ʾʹ�ð�ť
                    useButton->setUserData(item); // ����Ʒ������ʹ�ð�ť����
                    useButton->setVisible(true);
                    useButton->setPosition(Vec2(backpackPos.x - backpackSize.width / 2 - 15, backpackPos.y + 25));// �ڱ��������ʾ
                    useButton->setEnabled(true);// ���� useButton ������¼�����

                    // ��ʾ�ݻٰ�ť
                    destroyButton->setUserData(item); // ����Ʒ������ʹ�ð�ť����
                    destroyButton->setVisible(true);
                    destroyButton->setPosition(Vec2(backpackPos.x - backpackSize.width / 2 - 15, backpackPos.y - 45));// �ڱ��������ʾ
                    destroyButton->setEnabled(true);// ���� destroyButton ������¼�����

                }
                return;
            }
        }

        // �������Ĳ�����Ʒͼ�꣬���ض�Ӧ����ƷUI�������������¼�����
        useResultLabel->setVisible(false);
        destroyResultLabel -> setVisible(false);
        itemDetaUI->setVisible(false);
        itemDataLabel->setVisible(false);
        destroyButton->setVisible(false);
        destroyButton->setEnabled(false);
        useButton->setVisible(false);
        useButton->setEnabled(false);
    };

    // ����ͷ��¼�
    mouseListener->onMouseUp = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // ��ȡ��������ͼ�ߴ缰����
        auto backpackSize = backpackBgSprite->getContentSize();
        auto backpackPos = backpackBgSprite->getPosition();

        // ��ȡ����ͷ��ƫ����
        Vec2 cameraOffset = this->getParent()->getPosition();

        // ���������ת��Ϊ����ڳ���������
        mousePosition -= cameraOffset;

        // ����Ƿ����� hideButton
        Vec2 hideButtonPosition = hideButton->getPosition();
        Size hideButtonSize = hideButton->getContentSize();
        Rect hideButtonBoundingBox = Rect(hideButtonPosition.x - hideButtonSize.width,
            hideButtonPosition.y,
            hideButtonSize.width, hideButtonSize.height);

        if (hideButtonBoundingBox.containsPoint(mousePosition))
        {
            // �������� hideButton���л�������״̬��ͼƬ�����ر�����
            hideButton->setNormalImage(Sprite::create("ui/close_normal.png"));
            hideBackpack(nullptr); // ���ر�����

            //������ƷUI
            itemDetaUI->setVisible(false);
            itemDataLabel->setVisible(false);
            getCoinCount->setVisible(false);
            determineUI->setVisible(false);
            yesButton->setVisible(false);
            noButton->setVisible(false);
            //���ʹ�ð�ť�ʹݻٰ�ť�İ󶨼��ɼ�
            useButton->setUserData(nullptr);
            useButton->setVisible(false);
            destroyButton->setUserData(nullptr);
            destroyButton->setVisible(false);
            
        }
        else
        {
            // �����������ʱ���ڰ�ť�����ڣ�Ҳ�л�������״̬
            hideButton->setNormalImage(Sprite::create("ui/close_normal.png"));
        }


    // ����Ƿ����� destroyButton
        if (destroyButton) {
            Vec2 destroyButtonPosition = destroyButton->getPosition();
            Size destroyButtonSize = destroyButton->getContentSize();
            Rect destroyButtonBoundingBox = Rect(destroyButtonPosition.x - destroyButtonSize.width,
                destroyButtonPosition.y - destroyButtonSize.height,
                destroyButtonSize.width, destroyButtonSize.height);

            if (destroyButtonBoundingBox.containsPoint(mousePosition))
            {
                // �������� destroyButton���л�������״̬��ͼƬ��ִ��ʹ���߼�
                destroyButton->setNormalImage(Sprite::create("ui/sell_button_normal.png"));
                destroyResultLabel->setPosition(backpackPos + Vec2(0, 40));

                determineUI->setVisible(true);
                yesButton->setVisible(true);
                noButton->setVisible(true);
                getCoinCount->setVisible(true);

                destroyButton->activate(); // ִ��ʹ���߼�
            }
            else
            {
                // �����������ʱ���ڰ�ť�����ڣ�Ҳ�л�������״̬
                destroyButton->setNormalImage(Sprite::create("ui/sell_button_normal.png"));
            }
        }

        // ����Ƿ����� useButton
        if (useButton) {
            Vec2 useButtonPosition = useButton->getPosition();
            Size useButtonSize = useButton->getContentSize();
            Rect useButtonBoundingBox = Rect(useButtonPosition.x - useButtonSize.width,
                useButtonPosition.y - useButtonSize.height,
                useButtonSize.width, useButtonSize.height);

            if (useButtonBoundingBox.containsPoint(mousePosition))
            {
                // �������� useButton���л�������״̬��ͼƬ��ִ��ʹ���߼�
                useButton->setNormalImage(Sprite::create("ui/use_button_normal.png"));
                useResultLabel->setPosition(backpackPos + Vec2(0, 40));
                useButton->activate(); // ִ��ʹ���߼�
            }
            else
            {
                // �����������ʱ���ڰ�ť�����ڣ�Ҳ�л�������״̬
                useButton->setNormalImage(Sprite::create("ui/use_button_normal.png"));
            }
        }

        // ����Ƿ����� yesButton
        if (yesButton) {
            Vec2 yesButtonPosition = yesButton->getPosition();
            Size yesButtonSize = yesButton->getContentSize();
            Rect yesButtonBoundingBox = Rect(yesButtonPosition.x, yesButtonPosition.y, yesButtonSize.width, yesButtonSize.height);

            if (yesButtonBoundingBox.containsPoint(mousePosition))
            {
                // �������� yesButton���л�������״̬��ͼƬ��ִ��ʹ���߼�
                yesButton->setNormalImage(Sprite::create("ui/yes_normal.png"));

                yesButton->activate(); // ִ��ʹ���߼�
            }
            else
            {
                // �����������ʱ���ڰ�ť�����ڣ�Ҳ�л�������״̬
                yesButton->setNormalImage(Sprite::create("ui/yes_normal.png"));
            }
        }

        // ����Ƿ����� noButton
        if (noButton) {
            Vec2 noButtonPosition = noButton->getPosition();
            Size noButtonSize = noButton->getContentSize();
            Rect noButtonBoundingBox = Rect(noButtonPosition.x, noButtonPosition.y, noButtonSize.width, noButtonSize.height);

            if (noButtonBoundingBox.containsPoint(mousePosition))
            {
                // �������� noButton���л�������״̬��ͼƬ��ִ��ʹ���߼�
                noButton->setNormalImage(Sprite::create("ui/no_normal.png"));
                noButton->activate(); // ִ��ʹ���߼�
            }
            else
            {
                // �����������ʱ���ڰ�ť�����ڣ�Ҳ�л�������״̬
                noButton->setNormalImage(Sprite::create("ui/no_normal.png"));
            }
        }

   
    };


    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

//��ʾ��ӦUI
void BackpackLayer::getDetermineUI()
{

  
}