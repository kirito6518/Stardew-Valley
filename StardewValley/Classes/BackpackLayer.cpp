#include "BackpackLayer.h"
#include "BackpackManager.h"
#include "Item.h"
#include "AppDelegate.h"

USING_NS_CC;

// 创建背包层
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

// 初始化背包层
bool BackpackLayer::init(const std::string& backpackBgPath, int maxItems)
{
    if (!Layer::init())
    {
        return false;
    }

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 加载背包背景图片
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

    // 创建关闭按钮
    hideButton = MenuItemImage::create(
        "ui/close_normal.png",
        "ui/close_pressed.png",
        CC_CALLBACK_1(BackpackLayer::hideBackpack, this));

    hideButton->setAnchorPoint(Vec2(1, 0));
    hideButton->setPosition(Vec2(visibleSize.width / 2 + backpackSize.width / 2, visibleSize.height / 2 + backpackSize.height / 2));
    auto menu = Menu::create(hideButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    // 初始化背包属性
    this->maxItems = maxItems;
    this->currentItems = 0;

#if 1
    // 初始化物品显示UI
    itemNameLabel = Label::createWithSystemFont("test", "Arial", 24);
    itemNameLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 50);
    itemNameLabel->setVisible(false);
    this->addChild(itemNameLabel);

    itemCountLabel = Label::createWithSystemFont("100", "Arial", 24);
    itemCountLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    itemCountLabel->setVisible(false);
    this->addChild(itemCountLabel);
#endif

    // 添加鼠标事件监听器
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // 遍历所有物品图标，检查鼠标是否悬停在某个物品上
        for (auto itemSprite : itemSprites)
        {
            if (itemSprite->getBoundingBox().containsPoint(mousePosition))
            {
                // 获取物品对象
                Item* item = static_cast<Item*>(itemSprite->getUserData());
                if (item)
                {
                    // 显示物品名称
                    itemNameLabel->setString(item->getName());
                    itemNameLabel->setPosition(mousePosition + Vec2(0, 20)); // 在鼠标位置上方显示
                    itemNameLabel->setVisible(true);
                }
                return;
            }
        }

        // 如果鼠标不在任何物品上，隐藏物品名称
        itemNameLabel->setVisible(false);
        };

    mouseListener->onMouseDown = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // 遍历所有物品图标，检查鼠标是否点击了某个物品
        for (auto itemSprite : itemSprites)
        {
            if (itemSprite->getBoundingBox().containsPoint(mousePosition))
            {
                // 获取物品对象
                Item* item = static_cast<Item*>(itemSprite->getUserData());
                if (item)
                {
                    // 显示使用按钮
                    useButton->setUserData(item); // 将物品对象与使用按钮关联
                    useButton->setVisible(true);
                    useButton->setPosition(mousePosition + Vec2(0, -50)); // 在物品图标下方显示
                }
                return;
            }
        }

        // 如果点击的不是物品图标，隐藏使用按钮
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

    // 初始化背包格子布局
    gridWidth = 10;
    gridHeight = 3;
    gridSpacing = 20;
    gridStartX = (visibleSize.width - (gridWidth * 80 + (gridWidth - 1) * gridSpacing)) / 2;
    gridStartY = (visibleSize.height + (gridHeight * 80 + (gridHeight - 1) * gridSpacing)) / 2;

    return true;
}

// 添加物品到背包
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

    // 确保 itemSprite 没有父节点
    if (itemSprite->getParent() != nullptr)
    {
        CCLOG("Item sprite already has a parent!");
        return false;
    }

    // 将物品图标添加到背包层
    this->addChild(itemSprite);
    itemSprites.pushBack(itemSprite);

    // 为物品图标设置用户数据（即 Item 对象）
    Item* item = static_cast<Item*>(itemSprite->getUserData());
    if (item)
    {
        itemSprite->setUserData(item);
    }

    currentItems++;
    return true;
}

// 移除物品
void BackpackLayer::removeItem(Sprite* itemSprite)
{
    itemSprites.eraseObject(itemSprite);
    itemSprite->removeFromParent();
    currentItems--;
}

// 隐藏背包
void BackpackLayer::hideBackpack(Ref* sender)
{
    BackpackManager::getInstance()->hideBackpack();
}

// 显示物品详情
void BackpackLayer::showItemDetails(Item* item)
{
    itemNameLabel->setString(item->getName());
    itemCountLabel->setString("Count: " + std::to_string(item->getCount()));

    itemNameLabel->setVisible(true);
    itemCountLabel->setVisible(true);
    useButton->setVisible(true);
}

// 隐藏物品详情
void BackpackLayer::hideItemDetails()
{
    itemNameLabel->setVisible(false);
    itemCountLabel->setVisible(false);
    useButton->setVisible(false);
}
