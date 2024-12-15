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

    if (!hideButton)
    {
        CCLOG("Failed to create hideButton!");
        return false;
    }

    hideButton->setAnchorPoint(Vec2(1, 0));
    hideButton->setPosition(Vec2(visibleSize.width / 2 + backpackSize.width / 2, visibleSize.height / 2 + backpackSize.height / 2));
    this->addChild(hideButton);


    // 初始化背包属性
    this->maxItems = maxItems;
    this->currentItems = 0;

#if 1
    // 初始化物品显示UI
    itemNameLabel = Label::createWithSystemFont("", "Arial", 24);
    itemNameLabel->setAnchorPoint(Vec2(0, 1));
    itemNameLabel->setVisible(false);
    this->addChild(itemNameLabel,3);

    itemCountLabel = Label::createWithSystemFont("", "Arial", 24);
    itemCountLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    itemCountLabel->setVisible(false);
    this->addChild(itemCountLabel,3);
#endif

    //添加鼠标事件监听器
    setupCombinedMouseListener();

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
    gridWidth = 80;
    gridHeight = 80;
    gridSpacing = 20;
    gridStartX = (visibleSize.width - backpackSize.width) / 2;
    gridStartY = (visibleSize.height + backpackSize.height) / 2;

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

    auto backpackSize = backpackBgSprite->getContentSize();
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //物品坐标相对于初始坐标的偏移量
    int dx, dy;
    itemSprite->setAnchorPoint(Vec2(0, 1));


    // 确保 itemSprite 没有父节点
    if (itemSprite->getParent() != nullptr)
    {
        CCLOG("Item sprite already has a parent!");
        return false;
    }

    dx = currentItems % 10 * (gridWidth + gridSpacing);
    dy = currentItems / 10 * (gridHeight + gridSpacing);

    itemSprite->setPosition(Vec2(gridStartX + dx, gridStartY + dy));
    // 将物品图标添加到背包层
    this->addChild(itemSprite,3);
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

//鼠标监听事件与物品的交互
void BackpackLayer::setupCombinedMouseListener()
{
    // 移除之前绑定的事件监听器
    _eventDispatcher->removeEventListenersForTarget(this);

    auto mouseListener = EventListenerMouse::create();

    // 鼠标移动事件
    mouseListener->onMouseMove = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // 获取摄像头的偏移量
        Vec2 cameraOffset = this->getParent()->getPosition();

        // 将鼠标坐标转换为相对于场景的坐标
        mousePosition -= cameraOffset;

        // 遍历所有物品图标，检查鼠标是否悬停在某个物品上
        for (auto itemSprite : itemSprites)
        {
            // 获取物品精灵的当前坐标
            Vec2 itemPosition = itemSprite->getPosition();
            // 计算物品精灵的边界框
            Rect itemBoundingBox = Rect(itemPosition.x, itemPosition.y - gridHeight, gridWidth, gridHeight);

            if (itemBoundingBox.containsPoint(mousePosition))
            {
                // 获取物品对象
                Item* item = static_cast<Item*>(itemSprite->getUserData());
                if (item)
                {
                    // 显示物品名称
                    itemNameLabel->setString(item->getName());
                    itemNameLabel->setPosition(itemPosition + Vec2(0, 20)); // 在物品位置上方显示
                    itemNameLabel->setVisible(true);
                }
                return;
            }
        }

        // 如果鼠标不在任何物品上，隐藏物品名称
        itemNameLabel->setVisible(false);
        };

    // 鼠标点击事件
    mouseListener->onMouseDown = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // 获取摄像头的偏移量
        Vec2 cameraOffset = this->getParent()->getPosition();

        // 将鼠标坐标转换为相对于场景的坐标
        mousePosition -= cameraOffset;

        // 检查是否点击了 hideButton
        Vec2 hideButtonPosition = hideButton->getPosition();
        Size hideButtonSize = hideButton->getContentSize();
        Rect hideButtonBoundingBox = Rect(hideButtonPosition.x - hideButtonSize.width / 2,
            hideButtonPosition.y - hideButtonSize.height / 2,
            hideButtonSize.width, hideButtonSize.height);

        if (hideButtonBoundingBox.containsPoint(mousePosition))
        {
            // 如果点击了 hideButton，切换到按下状态的图片
            hideButton->setNormalImage(Sprite::create("ui/close_pressed.png"));
            return;
        }

        // 遍历所有物品图标，检查鼠标是否点击了某个物品
        for (auto itemSprite : itemSprites)
        {
            // 获取物品精灵的当前坐标
            Vec2 itemPosition = itemSprite->getPosition();
            // 计算物品精灵的边界框
            Rect itemBoundingBox = Rect(itemPosition.x, itemPosition.y - gridHeight, gridWidth, gridHeight);

            if (itemBoundingBox.containsPoint(mousePosition))
            {
                // 获取物品对象
                Item* item = static_cast<Item*>(itemSprite->getUserData());
                if (item)
                {
                    // 显示使用按钮
                    useButton->setUserData(item); // 将物品对象与使用按钮关联
                    useButton->setVisible(true);
                    useButton->setPosition(itemPosition + Vec2(0, -50)); // 在物品图标下方显示
                }
                return;
            }
        }

        // 如果点击的不是物品图标，隐藏使用按钮
        useButton->setVisible(false);
        };

    // 鼠标释放事件
    mouseListener->onMouseUp = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // 获取摄像头的偏移量
        Vec2 cameraOffset = this->getParent()->getPosition();

        // 将鼠标坐标转换为相对于场景的坐标
        mousePosition -= cameraOffset;

        // 检查是否点击了 hideButton
        Vec2 hideButtonPosition = hideButton->getPosition();
        Size hideButtonSize = hideButton->getContentSize();
        Rect hideButtonBoundingBox = Rect(hideButtonPosition.x - hideButtonSize.width / 2,
            hideButtonPosition.y - hideButtonSize.height / 2,
            hideButtonSize.width, hideButtonSize.height);

        if (hideButtonBoundingBox.containsPoint(mousePosition))
        {
            // 如果点击了 hideButton，切换回正常状态的图片并隐藏背包层
            hideButton->setNormalImage(Sprite::create("ui/close_normal.png"));
            hideBackpack(nullptr); // 隐藏背包层
        }
        else
        {
            // 如果触摸结束时不在按钮区域内，也切换回正常状态
            hideButton->setNormalImage(Sprite::create("ui/close_normal.png"));
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

