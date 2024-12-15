#include "BackpackLayer.h"
#include "BackpackManager.h"
#include "Item.h"
#include "AppDelegate.h"

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
    this->addChild(backpackBgSprite, 3);

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

#if 1
    // ��ʼ����Ʒ��ʾUI
    itemNameLabel = Label::createWithSystemFont("", "Gen.ttf", 24);
    itemNameLabel->setAnchorPoint(Vec2(0, 1));
    itemNameLabel->setVisible(false);
    this->addChild(itemNameLabel,3);

    itemCountLabel = Label::createWithSystemFont("", "Arial", 24);
    itemCountLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    itemCountLabel->setVisible(false);
    this->addChild(itemCountLabel,3);
#endif

    //������Ʒʹ�ð�ť
    useButton = MenuItemImage::create(
        "ui/use_button_normal.png",  // ����״̬��ͼƬ
        "ui/use_button_pressed.png", // ����״̬��ͼƬ
        CC_CALLBACK_1(BackpackLayer::onUseButtonClicked, this)); // ����ص�����

    useButton->setAnchorPoint(Vec2(1, 1));  
    useButton->setPosition(Vec2(backpackPos.x - backpackSize.width / 2 - 20, backpackPos.y + 20));
    this->addChild(useButton);
    useButton->setVisible(false);
    
    //�������¼�������
    setupCombinedMouseListener();

    // ��ʼ���������Ӳ���
    gridWidth = 80;
    gridHeight = 80;
    gridSpacing = 10;
    gridStartX = (visibleSize.width - backpackSize.width) / 2;
    gridStartY = (visibleSize.height + backpackSize.height) / 2;

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

    dx = currentItems % 10 * (gridWidth + gridSpacing);
    dy = currentItems / 10 * (gridHeight + gridSpacing);

    itemSprite->setPosition(Vec2(gridStartX + dx, gridStartY + dy));
    // ����Ʒͼ����ӵ�������
    this->addChild(itemSprite,3);
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
    itemSprites.eraseObject(itemSprite);
    itemSprite->removeFromParent();
    currentItems--;
}

// ���ر���
void BackpackLayer::hideBackpack(Ref* sender)
{
    BackpackManager::getInstance()->hideBackpack();
}

// ��ʾ��Ʒ����
void BackpackLayer::showItemDetails(Item* item)
{
    itemNameLabel->setString(item->getName());
    itemCountLabel->setString("Count: " + std::to_string(item->getCount()));

    itemNameLabel->setVisible(true);
    itemCountLabel->setVisible(true);
    useButton->setVisible(true);
}

// ������Ʒ����
void BackpackLayer::hideItemDetails()
{
    itemNameLabel->setVisible(false);
    itemCountLabel->setVisible(false);
    useButton->setVisible(false);
}

//���ʹ�ð�ť�Ļص�����
void BackpackLayer::onUseButtonClicked(Ref* sender)
{
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
            useResultLabel->setString("Use Failed!");
        }

        useResultLabel->setVisible(true);

        this->scheduleOnce([this](float dt) {
            useResultLabel->setVisible(false);
            }, 2.0f, "hide_use_result");
    }
}

//�������¼��뱳����Ԫ�صĽ���
void BackpackLayer::setupCombinedMouseListener()
{
    // �Ƴ�֮ǰ�󶨵��¼�������
    _eventDispatcher->removeEventListenersForTarget(this);


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
                    itemNameLabel->setPosition(itemPosition + Vec2(0, 20)); // ����Ʒλ���Ϸ���ʾ
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
        // CCLOG("Button!!!!!!!!!!!!!!!!!!!!!");
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
                    // ��ʾʹ�ð�ť
                    useButton->setUserData(item); // ����Ʒ������ʹ�ð�ť����
                    useButton->setVisible(true);
                    useButton->setPosition(Vec2(backpackPos.x - backpackSize.width / 2 - 20, backpackPos.y + 20));// ����Ʒͼ���·���ʾ
                }
                return;
            }
        }

        // �������Ĳ�����Ʒͼ�꣬����ʹ�ð�ť
        useButton->setVisible(false);
        };

    // ����ͷ��¼�
    mouseListener->onMouseUp = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

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
        }
        else
        {
            // �����������ʱ���ڰ�ť�����ڣ�Ҳ�л�������״̬
            hideButton->setNormalImage(Sprite::create("ui/close_normal.png"));
        }


    // ����Ƿ����� useButton
        if (useButton) {
            Vec2 useButtonPosition = useButton->getPosition();
            Size useButtonSize = useButton->getContentSize();
            Rect useButtonBoundingBox = Rect(useButtonPosition.x - useButtonSize.width / 2,
                useButtonPosition.y - useButtonSize.height / 2,
                useButtonSize.width, useButtonSize.height);

            if (useButtonBoundingBox.containsPoint(mousePosition))
            {
                // �������� useButton���л�������״̬��ͼƬ��ִ��ʹ���߼�
                useButton->setNormalImage(Sprite::create("ui/use_button_normal.png"));
                useButton->activate(); // ִ��ʹ���߼�
            }
            else
            {
                // �����������ʱ���ڰ�ť�����ڣ�Ҳ�л�������״̬
                useButton->setNormalImage(Sprite::create("ui/use_button_normal.png"));
            }
        }
   
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

