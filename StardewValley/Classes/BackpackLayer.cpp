#include "BackpackLayer.h"
#include "BackpackManager.h"
#include "Item.h"
#include "AppDelegate.h"
#include "MainMap.h"

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
    this->addChild(backpackBgSprite, 2);

    //获取背包背景图尺寸及坐标
    auto backpackSize = backpackBgSprite->getContentSize();
    auto backpackPos = backpackBgSprite->getPosition();

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

    // 初始化物品名称标签
    itemNameLabel = Label::createWithTTF("", "fonts/Gen.ttf", 20);
    itemNameLabel->setAnchorPoint(Vec2(0, 1));
    itemNameLabel->setVisible(false);
    this->addChild(itemNameLabel,3);

    //初始化使用结果标签
    useResultLabel = Label::createWithTTF("", "fonts/Gen.ttf", 30);
    useResultLabel->setAnchorPoint(Vec2(0.5, 0.5));
    useResultLabel->setVisible(false);
    this->addChild(useResultLabel, 3);

    //初始化销毁结果标签
    destroyResultLabel = Label::createWithTTF("", "fonts/Gen.ttf", 30);
    destroyResultLabel->setAnchorPoint(Vec2(0.5, 0.5));
    destroyResultLabel->setVisible(false);
    this->addChild(destroyResultLabel, 3);

    //初始化物品信息UI
    itemDetaUI = Sprite::create("ui/itemDetaUI.png");
    itemDetaUI->setAnchorPoint(Vec2(1, 1));
    itemDetaUI->setVisible(false);
    this->addChild(itemDetaUI, 0);

    //初始化物品信息标签
    itemDataLabel = Label::createWithTTF("", "fonts/Gen.ttf", 30);
    itemDataLabel->setAnchorPoint(Vec2(0, 1));
    itemDataLabel->setVisible(false);
    this->addChild(itemDataLabel, 3);


    //加载物品使用按钮
    useButton = MenuItemImage::create(
        "ui/use_button_normal.png",  // 正常状态的图片
        "ui/use_button_pressed.png", // 按下状态的图片
        CC_CALLBACK_1(BackpackLayer::onUseButtonClicked, this)); // 点击回调函数

    useButton->setAnchorPoint(Vec2(1, 1));  
    useButton->setPosition(Vec2(backpackPos.x - backpackSize.width / 2 - 20, backpackPos.y + 20));
    this->addChild(useButton);
    useButton->setVisible(false);
    // 默认关闭 useButton 的鼠标事件监听
    useButton->setEnabled(false);

    //加载物品摧毁按钮
    destroyButton= MenuItemImage::create(
        "ui/destroyBotton_normal.png",  // 正常状态的图片
        "ui/destroyBotton_pressed.png", // 按下状态的图片
        CC_CALLBACK_1(BackpackLayer::onDestroyButtonClicked, this)); // 点击回调函数
    destroyButton->setAnchorPoint(Vec2(1, 1));
    destroyButton->setPosition(Vec2(backpackPos.x - backpackSize.width / 2 - 20, backpackPos.y - 40));
    this->addChild(destroyButton);
    destroyButton->setVisible(false);
    // 默认关闭 destroyButton 的鼠标事件监听
    destroyButton->setEnabled(false);

    //添加鼠标事件监听器
    setupCombinedMouseListener();

    // 初始化背包格子布局
    gridWidth = 80;
    gridHeight = 80;
    gridSpacing = 10;
    gridStartX = (visibleSize.width - backpackSize.width) / 2+10;
    gridStartY = (visibleSize.height + backpackSize.height) / 2-10;

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

    dx = (currentItems % 10 )* (gridWidth + gridSpacing);
    dy = (currentItems / 10) * (gridHeight + gridSpacing);

    itemSprite->setPosition(Vec2(gridStartX +dx, gridStartY -dy));
    // 将物品图标添加到背包层
    this->addChild(itemSprite,2);
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
    //隐藏物品UI
    itemDetaUI->setVisible(false);
    itemDataLabel->setVisible(false);

    //解除使用按钮和摧毁按钮的绑定及可见
    useButton->setUserData(nullptr);
    useButton->setVisible(false);
    destroyButton->setUserData(nullptr);
    destroyButton->setVisible(false);

    itemSprites.eraseObject(itemSprite);
    itemSprite->removeFromParent();
    currentItems--;
}

// 隐藏背包
void BackpackLayer::hideBackpack(Ref* sender)
{
    BackpackManager::getInstance()->hideBackpack();

    // 调用mainmap的恢复时间更新的函数
    dynamic_cast<MainMap*>(BackpackManager::getInstance()->mainMap)->hideBackpack(sender);
}

//点击使用按钮的回调函数
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
            }, 1.2f, "hide_use_result");
    }
}

//点击摧毁按钮的回调函数
void BackpackLayer::onDestroyButtonClicked(Ref* sender)
{
    //移除物品
    auto item = static_cast<Item*>(destroyButton->getUserData());
    int itemcount = item->getCount();
    item->clearItem();

    destroyResultLabel->setString("Destroy Success!");
    destroyResultLabel->setVisible(true);
    this->scheduleOnce([this](float dt) {
        destroyResultLabel->setVisible(false);
        }, 1.2f, "hide_use_result");
}

//鼠标监听事件与背包内元素的交互
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
                    itemNameLabel->setPosition(itemPosition + Vec2(0, 16)); // 在物品位置上方显示
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

        // 获取背包背景图尺寸及坐标
        auto backpackSize = backpackBgSprite->getContentSize();
        auto backpackPos = backpackBgSprite->getPosition();

        // 获取摄像头的偏移量
        Vec2 cameraOffset = this->getParent()->getPosition();

        // 将鼠标坐标转换为相对于场景的坐标
        mousePosition -= cameraOffset;

        // 检查是否点击了 hideButton
        Vec2 hideButtonPosition = hideButton->getPosition();
        Size hideButtonSize = hideButton->getContentSize();
        Rect hideButtonBoundingBox = Rect(hideButtonPosition.x - hideButtonSize.width,
            hideButtonPosition.y,
            hideButtonSize.width, hideButtonSize.height);

        if (hideButtonBoundingBox.containsPoint(mousePosition))
        {
            // 如果点击了 hideButton，切换到按下状态的图片
            hideButton->setNormalImage(Sprite::create("ui/close_pressed.png"));
            return;
        }


        //  检查是否点击了 useButton
        if (useButton->isVisible()) {
            Vec2 useButtonPosition = useButton->getPosition();
            Size useButtonSize = useButton->getContentSize();
            Rect useButtonBoundingBox = Rect(useButtonPosition.x - useButtonSize.width,
                useButtonPosition.y - useButtonSize.height,
                useButtonSize.width, useButtonSize.height);

            if (useButtonBoundingBox.containsPoint(mousePosition))
            {
                // 如果点击了 useButton，切换到按下状态的图片
                useButton->setNormalImage(Sprite::create("ui/use_button_pressed.png"));
                return;
            }
        }

        //  检查是否点击了 destroyButton
        if (destroyButton->isVisible()) {
            Vec2 destroyButtonPosition = destroyButton->getPosition();
            Size destroyButtonSize = destroyButton->getContentSize();
            Rect destroyButtonBoundingBox = Rect(destroyButtonPosition.x - destroyButtonSize.width,
                destroyButtonPosition.y - destroyButtonSize.height,
                destroyButtonSize.width, destroyButtonSize.height);

            if (destroyButtonBoundingBox.containsPoint(mousePosition))
            {
                // 如果点击了 useButton，切换到按下状态的图片
                useButton->setNormalImage(Sprite::create("ui/destroy_button_pressed.png"));
                return;
            }
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

                    //显示物品UI
                    itemDetaUI->setVisible(true);
                    itemDetaUI->setPosition(Vec2(backpackPos.x - backpackSize.width / 2 , backpackPos.y + backpackSize.height/2));// 在背包左侧显示

                    //显示物品信息标签
                    itemDataLabel->setString(item->getName());
                    itemDataLabel->setVisible(true);
                    itemDataLabel->setPosition(Vec2(backpackPos.x - backpackSize.width / 2- itemDetaUI->getContentSize().width+25,
                        backpackPos.y + backpackSize.height / 2-25));// 在背包左侧显示

                    // 显示使用按钮
                    useButton->setUserData(item); // 将物品对象与使用按钮关联
                    useButton->setVisible(true);
                    useButton->setPosition(Vec2(backpackPos.x - backpackSize.width / 2 - 15, backpackPos.y + 25));// 在背包左侧显示
                    useButton->setEnabled(true);// 开启 useButton 的鼠标事件监听

                    // 显示摧毁按钮
                    destroyButton->setUserData(item); // 将物品对象与使用按钮关联
                    destroyButton->setVisible(true);
                    destroyButton->setPosition(Vec2(backpackPos.x - backpackSize.width / 2 - 15, backpackPos.y - 45));// 在背包左侧显示
                    destroyButton->setEnabled(true);// 开启 destroyButton 的鼠标事件监听

                }
                return;
            }
        }

        // 如果点击的不是物品图标，隐藏对应的物品UI并禁用相关鼠标事件监听
        itemDetaUI->setVisible(false);
        itemDataLabel->setVisible(false);
        destroyButton->setVisible(false);
        destroyButton->setEnabled(false);
        useButton->setVisible(false);
        useButton->setEnabled(false);
        };

    // 鼠标释放事件
    mouseListener->onMouseUp = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // 获取背包背景图尺寸及坐标
        auto backpackSize = backpackBgSprite->getContentSize();
        auto backpackPos = backpackBgSprite->getPosition();

        // 获取摄像头的偏移量
        Vec2 cameraOffset = this->getParent()->getPosition();

        // 将鼠标坐标转换为相对于场景的坐标
        mousePosition -= cameraOffset;

        // 检查是否点击了 hideButton
        Vec2 hideButtonPosition = hideButton->getPosition();
        Size hideButtonSize = hideButton->getContentSize();
        Rect hideButtonBoundingBox = Rect(hideButtonPosition.x - hideButtonSize.width,
            hideButtonPosition.y,
            hideButtonSize.width, hideButtonSize.height);

        if (hideButtonBoundingBox.containsPoint(mousePosition))
        {
            // 如果点击了 hideButton，切换回正常状态的图片并隐藏背包层
            hideButton->setNormalImage(Sprite::create("ui/close_normal.png"));
            hideBackpack(nullptr); // 隐藏背包层

            //隐藏物品UI
            itemDetaUI->setVisible(false);
            itemDataLabel->setVisible(false);
            //解除使用按钮和摧毁按钮的绑定及可见
            useButton->setUserData(nullptr);
            useButton->setVisible(false);
            destroyButton->setUserData(nullptr);
            destroyButton->setVisible(false);
        }
        else
        {
            // 如果触摸结束时不在按钮区域内，也切换回正常状态
            hideButton->setNormalImage(Sprite::create("ui/close_normal.png"));
        }


    // 检查是否点击了 destroyButton
        if (destroyButton) {
            Vec2 destroyButtonPosition = destroyButton->getPosition();
            Size destroyButtonSize = destroyButton->getContentSize();
            Rect destroyButtonBoundingBox = Rect(destroyButtonPosition.x - destroyButtonSize.width,
                destroyButtonPosition.y - destroyButtonSize.height,
                destroyButtonSize.width, destroyButtonSize.height);

            if (destroyButtonBoundingBox.containsPoint(mousePosition))
            {
                // 如果点击了 destroyButton，切换回正常状态的图片并执行使用逻辑
                destroyButton->setNormalImage(Sprite::create("ui/destroyBotton_normal.png"));
                destroyResultLabel->setPosition(backpackPos + Vec2(0, 50));
                destroyButton->activate(); // 执行使用逻辑
            }
            else
            {
                // 如果触摸结束时不在按钮区域内，也切换回正常状态
                destroyButton->setNormalImage(Sprite::create("ui/destroyBotton_normal.png"));
            }
        }

        // 检查是否点击了 useButton
        if (useButton) {
            Vec2 useButtonPosition = useButton->getPosition();
            Size useButtonSize = useButton->getContentSize();
            Rect useButtonBoundingBox = Rect(useButtonPosition.x - useButtonSize.width,
                useButtonPosition.y - useButtonSize.height,
                useButtonSize.width, useButtonSize.height);

            if (useButtonBoundingBox.containsPoint(mousePosition))
            {
                // 如果点击了 useButton，切换回正常状态的图片并执行使用逻辑
                useButton->setNormalImage(Sprite::create("ui/use_button_normal.png"));
                useResultLabel->setPosition(backpackPos + Vec2(0, 50));
                useButton->activate(); // 执行使用逻辑
            }
            else
            {
                // 如果触摸结束时不在按钮区域内，也切换回正常状态
                useButton->setNormalImage(Sprite::create("ui/use_button_normal.png"));
            }
        }

   
    };


    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

