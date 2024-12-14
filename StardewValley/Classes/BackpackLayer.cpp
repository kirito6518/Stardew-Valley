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

    auto backpackSize = backpackBgSprite->getContentSize();

    // �����رհ�ť
    hideButton = MenuItemImage::create(
        "ui/close_normal.png",
        "ui/close_pressed.png",
        CC_CALLBACK_1(BackpackLayer::hideBackpack, this));

    hideButton->setAnchorPoint(Vec2(1, 0));
    hideButton->setPosition(Vec2(visibleSize.width / 2 + backpackSize.width / 2, visibleSize.height / 2 + backpackSize.height / 2));
    auto menu = Menu::create(hideButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    // ��ʼ����������
    this->maxItems = maxItems;
    this->currentItems = 0;

#if 1
    // ��ʼ����Ʒ��ʾUI
    itemNameLabel = Label::createWithSystemFont("test", "Arial", 24);
    itemNameLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 50);
    itemNameLabel->setVisible(false);
    this->addChild(itemNameLabel);

    itemCountLabel = Label::createWithSystemFont("100", "Arial", 24);
    itemCountLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    itemCountLabel->setVisible(false);
    this->addChild(itemCountLabel);
#endif

    // �������¼�������
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // ����������Ʒͼ�꣬�������Ƿ���ͣ��ĳ����Ʒ��
        for (auto itemSprite : itemSprites)
        {
            if (itemSprite->getBoundingBox().containsPoint(mousePosition))
            {
                // ��ȡ��Ʒ����
                Item* item = static_cast<Item*>(itemSprite->getUserData());
                if (item)
                {
                    // ��ʾ��Ʒ����
                    itemNameLabel->setString(item->getName());
                    itemNameLabel->setPosition(mousePosition + Vec2(0, 20)); // �����λ���Ϸ���ʾ
                    itemNameLabel->setVisible(true);
                }
                return;
            }
        }

        // �����겻���κ���Ʒ�ϣ�������Ʒ����
        itemNameLabel->setVisible(false);
        };

    mouseListener->onMouseDown = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // ����������Ʒͼ�꣬�������Ƿ�����ĳ����Ʒ
        for (auto itemSprite : itemSprites)
        {
            if (itemSprite->getBoundingBox().containsPoint(mousePosition))
            {
                // ��ȡ��Ʒ����
                Item* item = static_cast<Item*>(itemSprite->getUserData());
                if (item)
                {
                    // ��ʾʹ�ð�ť
                    useButton->setUserData(item); // ����Ʒ������ʹ�ð�ť����
                    useButton->setVisible(true);
                    useButton->setPosition(mousePosition + Vec2(0, -50)); // ����Ʒͼ���·���ʾ
                }
                return;
            }
        }

        // �������Ĳ�����Ʒͼ�꣬����ʹ�ð�ť
        useButton->setVisible(false);
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);


    useButton = MenuItemFont::create("Use", [this](Ref* sender) {
        auto item = static_cast<Item*>(sender);
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
        });

    useButton->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 50);
    useButton->setVisible(false);
    auto useMenu = Menu::create(useButton, nullptr);
    useMenu->setPosition(Vec2::ZERO);
    this->addChild(useMenu);

    useResultLabel = Label::createWithSystemFont("", "Arial", 24);
    useResultLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 100);
    useResultLabel->setVisible(false);
    this->addChild(useResultLabel);

    // ��ʼ���������Ӳ���
    gridWidth = 10;
    gridHeight = 3;
    gridSpacing = 20;
    gridStartX = (visibleSize.width - (gridWidth * 80 + (gridWidth - 1) * gridSpacing)) / 2;
    gridStartY = (visibleSize.height + (gridHeight * 80 + (gridHeight - 1) * gridSpacing)) / 2;

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

    float x = gridStartX + (currentItems % gridWidth) * (80 + gridSpacing);
    float y = gridStartY - (currentItems / gridWidth) * (80 + gridSpacing);
    itemSprite->setPosition(Vec2(x, y));

    // ȷ�� itemSprite û�и��ڵ�
    if (itemSprite->getParent() != nullptr)
    {
        CCLOG("Item sprite already has a parent!");
        return false;
    }

    // ����Ʒͼ����ӵ�������
    this->addChild(itemSprite);
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
