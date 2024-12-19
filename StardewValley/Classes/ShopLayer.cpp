#include "ShopLayer.h"
#include "ShopManager.h"
#include "ShopItem.h"  
#include "AppDelegate.h"
#include "MainMap.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

// 创建商店层
ShopLayer* ShopLayer::create(const std::string& shopBgPath, int maxItems)
{
    auto layer = new (std::nothrow) ShopLayer();
    if (layer && layer->init(shopBgPath, maxItems))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

// 初始化商店层
bool ShopLayer::init(const std::string& shopBgPath, int maxItems)
{
    if (!Layer::init())
    {
        return false;
    }

    //获取窗口数据
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 加载商店背景图片
    shopBgSprite = Sprite::create(shopBgPath);
    if (!shopBgSprite)
    {
        //CCLOG("Failed to load shop background image: %s", shopBgPath.c_str());
        return false;
    }

    shopBgSprite->setAnchorPoint(Vec2(0.5, 0.5));
    shopBgSprite->setPosition(visibleSize / 2);
    this->addChild(shopBgSprite, 2);

    // 获取商店背景图尺寸及坐标
    auto shopSize = shopBgSprite->getContentSize();
    auto shopPos = shopBgSprite->getPosition();

    // 加载商店招牌图片
    shopSprite = Sprite::create("ui/shop.png");
    shopSprite->setAnchorPoint(Vec2(0.5, 0.5));
    shopSprite->setAnchorPoint(Vec2(0.5, 0));
    shopSprite->setPosition(Vec2(shopPos.x, shopPos.y + shopSize.height / 2));
    this->addChild(shopSprite, 0);

    //初始化剩余ui
    LeftUI = Sprite::create("ui/leftUI.png");
    LeftUI->setAnchorPoint(Vec2(0, 1));
    LeftUI->setPosition(Vec2(shopPos.x-shopSize.width/2, shopPos.y - shopSize.height / 2));
    this->addChild(LeftUI, 0);

    //初始化剩余金币精灵
    leftCoin = Sprite::create("tool/coin.png");
    leftCoin->setScale(0.6f);
    leftCoin->setAnchorPoint(Vec2(0, 1));
    leftCoin->setPosition(Vec2(shopPos.x, shopPos.y + shopSize.height / 2));
    this->addChild(leftCoin, 2);

    //初始化剩余金币标签（前）
    itemLeftLabel1 = Label::createWithTTF("Your Remaining", "fonts/Gen.ttf", 25);
    itemLeftLabel1->setAnchorPoint(Vec2(0, 1));
    this->addChild(itemLeftLabel1, 2);

    //初始化剩余金币标签（后）
    itemLeftLabel2 = Label::createWithTTF("", "fonts/Gen.ttf", 25);
    itemLeftLabel2->setAnchorPoint(Vec2(0, 1));
    this->addChild(itemLeftLabel2, 2);

    // 创建关闭按钮
    closeButton = MenuItemImage::create(
        "ui/close_normal.png",
        "ui/close_pressed.png",
        CC_CALLBACK_1(ShopLayer::hideShop, this));

    if (!closeButton)
    {
        //CCLOG("Failed to create closeButton!");
        return false;
    }

    closeButton->setAnchorPoint(Vec2(1, 0));
    closeButton->setPosition(Vec2(visibleSize.width / 2 + shopSize.width / 2, visibleSize.height / 2 + shopSize.height / 2));
    this->addChild(closeButton);

    // 初始化商店属性
    this->maxItems = maxItems;
    this->currentItems = 0;

    // 初始化物品名称标签
    itemNameLabel = Label::createWithTTF("", "fonts/Gen.ttf", 20);
    itemNameLabel->setAnchorPoint(Vec2(0, 1));
    itemNameLabel->setVisible(false);
    this->addChild(itemNameLabel, 3);

    //初始化所需金币精灵
    needCoin = Sprite::create("tool/coin.png");
    needCoin->setScale(0.7f);
    needCoin->setAnchorPoint(Vec2(1, 1));
    needCoin->setVisible(false);
    this->addChild(needCoin, 2);

    // 初始化物品价格标签
    itemPriceLabel = Label::createWithTTF("", "fonts/Gen.ttf", 25);
    itemPriceLabel->setAnchorPoint(Vec2(1, 1));
    itemPriceLabel->setVisible(false);
    this->addChild(itemPriceLabel, 3);

    // 初始化购买结果标签
    buyResultLabel = Label::createWithTTF("", "fonts/Gen.ttf", 25);
    buyResultLabel->setAnchorPoint(Vec2(0.5, 0.5));
    buyResultLabel->setVisible(false);
    this->addChild(buyResultLabel, 3);

    // 初始化物品信息UI
    itemDetailUI = Sprite::create("ui/itemDetaUI.png");
    itemDetailUI->setAnchorPoint(Vec2(1, 1));
    itemDetailUI->setVisible(false);
    this->addChild(itemDetailUI, 0);

    // 初始化物品信息标签
    itemDetailLabel = Label::createWithTTF("", "fonts/Gen.ttf", 30);
    itemDetailLabel->setAnchorPoint(Vec2(0, 1));
    itemDetailLabel->setVisible(false);
    this->addChild(itemDetailLabel, 3);
    

    // 加载购买按钮
    buyButton = MenuItemImage::create(
        "ui/buy_button_normal.png",  // 正常状态的图片
        "ui/buy_button_pressed.png", // 按下状态的图片
        CC_CALLBACK_1(ShopLayer::onBuyButtonClicked, this)); // 点击回调函数
    buyButton->setAnchorPoint(Vec2(1, 1));
    buyButton->setPosition(Vec2(shopPos.x - shopSize.width / 2 - 20, shopPos.y - 40));
    this->addChild(buyButton, 3);

    // 默认关闭 buyButton 的鼠标事件监听
    buyButton->setEnabled(false);

    // 添加鼠标事件监听器
    setupCombinedMouseListener();

    // 初始化商店格子布局
    gridWidth = 80;
    gridHeight = 80;
    gridSpacing = 8;
    gridStartX = (visibleSize.width - shopSize.width) / 2 + 8;
    gridStartY = (visibleSize.height + shopSize.height) / 2 - 10;

    return true;
}

// 添加物品到商店
bool ShopLayer::addItem(Sprite* itemSprite)
{
    if (currentItems >= maxItems)
    {
        CCLOG("Shop is full! Cannot add more items.");
        return false;
    }

    auto shopSize = shopBgSprite->getContentSize();
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 物品坐标相对于初始坐标的偏移量
    int dx, dy;
    itemSprite->setAnchorPoint(Vec2(0, 1));

    // 确保 itemSprite 没有父节点
    if (itemSprite->getParent() != nullptr)
    {
        CCLOG("Item sprite already has a parent!");
        return false;
    }

    dx = (currentItems % 10) * (gridWidth + gridSpacing);
    dy = (currentItems / 10) * (gridHeight + gridSpacing);

    itemSprite->setPosition(Vec2(gridStartX + dx, gridStartY - dy));
    // 将物品图标添加到商店层
    this->addChild(itemSprite, 2);
    itemSprites.pushBack(itemSprite);

    // 为物品图标设置用户数据（即 ShopItem 对象）
    ShopItem* item = static_cast<ShopItem*>(itemSprite->getUserData());  
    if (item)
    {
        itemSprite->setUserData(item);
    }

    currentItems++;
    return true;
}

// 移除物品
void ShopLayer::removeItem(Sprite* itemSprite)
{
    // 隐藏物品UI
    itemDetailUI->setVisible(false);
    itemDetailLabel->setVisible(false);

    // 解除购买按钮的绑定及可见
    buyButton->setUserData(nullptr);
    buyButton->setVisible(false);

    itemSprites.eraseObject(itemSprite);
    itemSprite->removeFromParent();
    currentItems--;
}

// 隐藏商店
void ShopLayer::hideShop(Ref* sender)
{
    ShopManager::getInstance()->hideShop();

    // 调用 mainmap 的恢复时间更新的函数
    dynamic_cast<MainMap*>(ShopManager::getInstance()->mainMap)->hideShop(sender);
}

// 点击购买按钮的回调函数
void ShopLayer::onBuyButtonClicked(Ref* sender)
{
    auto item = static_cast<ShopItem*>(buyButton->getUserData());  

    if (item)
    {
        bool success = ShopManager::getInstance()->buyItem(item);

        if (success)
        {
            int leftCoinCount = 0;
            auto coinYouHave = BackpackManager::getInstance()->getItemByName("Coin");
            if (coinYouHave) {
                leftCoinCount = coinYouHave->getCount();
            }
            std::string itemLeftLabel2Str = ":  " + std::to_string(leftCoinCount);
            // 播放音效
            SimpleAudioEngine::getInstance()->playEffect("audio/coins.mp3");
            itemLeftLabel2->setString(itemLeftLabel2Str);
            buyResultLabel->setString("Buy Success!");
        }
        else
        {
            // 播放音效
            SimpleAudioEngine::getInstance()->playEffect("audio/click.mp3");
            buyResultLabel->setString("You Don't Have enough Coins Left!");
        }

        buyResultLabel->setVisible(true);

        this->scheduleOnce([this](float dt) {
            buyResultLabel->setVisible(false);
            }, 1.0f, "hide_buy_result");
    }
}

// 鼠标监听事件与商店内元素的交互
void ShopLayer::setupCombinedMouseListener()
{
    // 移除之前绑定的事件监听器
    _eventDispatcher->removeEventListenersForTarget(this);

    // 加载音效
    SimpleAudioEngine::getInstance()->preloadEffect("audio/click.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("audio/coins.mp3");

    // 获取商店背景图尺寸及坐标
    auto shopSize = shopBgSprite->getContentSize();
    auto shopPos = shopBgSprite->getPosition();

    //更新剩余ui图标位置
    LeftUI->setPosition(Vec2(shopPos.x - shopSize.width / 2, shopPos.y - shopSize.height / 2));

    //获取剩余ui图标最新信息
    auto LeftUIPos = LeftUI->getPosition();
    auto LeftUISize = LeftUI->getContentSize();

    //继续更新剩余ui图标位置
    itemLeftLabel1->setPosition(LeftUIPos+Vec2(20,-14));
    leftCoin->setPosition(LeftUIPos + Vec2(245,-9));
    itemLeftLabel2->setPosition(LeftUIPos + Vec2(300, -14));
    int leftCoinCount=0;
    auto coinYouHave = BackpackManager::getInstance()->getItemByName("Coin");
    if (coinYouHave) {
        leftCoinCount = coinYouHave->getCount();
    }
    std::string itemLeftLabel2Str = ":  " + std::to_string(leftCoinCount);
    itemLeftLabel2->setString(itemLeftLabel2Str);
    
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
                ShopItem* item = static_cast<ShopItem*>(itemSprite->getUserData());  
                if (item)
                {
                    // 显示物品名称
                    itemNameLabel->setString(item->getName());
                    itemNameLabel->setPosition(itemPosition + Vec2(0, 30)); // 在物品位置上方显示
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

        // 获取商店背景图尺寸及坐标
        auto shopSize = shopBgSprite->getContentSize();
        auto shopPos = shopBgSprite->getPosition();

        // 获取摄像头的偏移量
        Vec2 cameraOffset = this->getParent()->getPosition();

        // 将鼠标坐标转换为相对于场景的坐标
        mousePosition -= cameraOffset;

        // 检查是否点击了 closeButton
        Vec2 closeButtonPosition = closeButton->getPosition();
        Size closeButtonSize = closeButton->getContentSize();
        Rect closeButtonBoundingBox = Rect(closeButtonPosition.x - closeButtonSize.width,
            closeButtonPosition.y,
            closeButtonSize.width, closeButtonSize.height);

        if (closeButtonBoundingBox.containsPoint(mousePosition))
        {
            // 如果点击了 closeButton，切换到按下状态的图片
            closeButton->setNormalImage(Sprite::create("ui/close_pressed.png"));
            return;
        }

        // 检查是否点击了 buyButton
        if (buyButton->isVisible()) {
            Vec2 buyButtonPosition = buyButton->getPosition();
            Size buyButtonSize = buyButton->getContentSize();
            Rect buyButtonBoundingBox = Rect(buyButtonPosition.x - buyButtonSize.width,
                buyButtonPosition.y - buyButtonSize.height,
                buyButtonSize.width, buyButtonSize.height);

            if (buyButtonBoundingBox.containsPoint(mousePosition))
            {
                // 如果点击了 buyButton，切换到按下状态的图片
                buyButton->setNormalImage(Sprite::create("ui/buy_button_pressed.png"));
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
                ShopItem* item = static_cast<ShopItem*>(itemSprite->getUserData());
                if (item)
                {
                    // 播放音效
                    SimpleAudioEngine::getInstance()->playEffect("audio/click.mp3");

                    // 显示物品UI
                    itemDetailUI->setVisible(true);
                    itemDetailUI->setPosition(Vec2(shopPos.x - shopSize.width / 2, shopPos.y + shopSize.height / 2)); // 在商店左侧显示

                    // 显示物品信息标签
                    itemDetailLabel->setString(item->getName());
                    itemDetailLabel->setVisible(true);
                    itemDetailLabel->setPosition(Vec2(shopPos.x - shopSize.width / 2 - itemDetailUI->getContentSize().width + 25,
                        shopPos.y + shopSize.height / 2 - 25)); // 在商店左侧显示

                    // 显示物品价格
                    std::string label = " :  "+ std::to_string(item->getBuyingPrice());
                    itemPriceLabel->setString(label);
                    itemPriceLabel->setPosition(Vec2(shopPos.x - shopSize.width /2 -55, shopPos.y +3)); // 在商店左侧显示
                    itemPriceLabel->setVisible(true);

                    //显示所需金币图标
                    needCoin->setPosition(Vec2(shopPos.x - shopSize.width / 2 - 85, shopPos.y +7));// 在商店左侧显示
                    needCoin->setVisible(true);

                    // 显示购买按钮
                    buyButton->setUserData(item); // 将物品对象与购买按钮关联
                    buyButton->setVisible(true);
                    buyButton->setPosition(Vec2(shopPos.x - shopSize.width / 2 - 15, shopPos.y - 40)); // 在商店左侧显示
                    buyButton->setEnabled(true); // 开启 buyButton 的鼠标事件监听
                }
                return;
            }
        }

        // 如果点击的不是物品图标，隐藏对应的物品UI并禁用相关鼠标事件监听
        buyResultLabel->setVisible(false);
        needCoin->setVisible(false);
        itemDetailUI->setVisible(false);
        itemDetailLabel->setVisible(false);
        itemPriceLabel->setVisible(false);
        buyButton->setVisible(false);
        buyButton->setEnabled(false);
        };

    // 鼠标释放事件
    mouseListener->onMouseUp = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // 获取商店背景图尺寸及坐标
        auto shopSize = shopBgSprite->getContentSize();
        auto shopPos = shopBgSprite->getPosition();

        // 获取摄像头的偏移量
        Vec2 cameraOffset = this->getParent()->getPosition();

        // 将鼠标坐标转换为相对于场景的坐标
        mousePosition -= cameraOffset;

        // 检查是否点击了 closeButton
        Vec2 closeButtonPosition = closeButton->getPosition();
        Size closeButtonSize = closeButton->getContentSize();
        Rect closeButtonBoundingBox = Rect(closeButtonPosition.x - closeButtonSize.width,
            closeButtonPosition.y,
            closeButtonSize.width, closeButtonSize.height);

        if (closeButtonBoundingBox.containsPoint(mousePosition))
        {
            // 如果点击了 closeButton，切换回正常状态的图片并隐藏商店层
            closeButton->setNormalImage(Sprite::create("ui/close_normal.png"));
            hideShop(nullptr); // 隐藏商店层

            // 播放音效
            SimpleAudioEngine::getInstance()->playEffect("audio/click.mp3");

            // 隐藏物品UI
            itemDetailUI->setVisible(false);
            itemDetailLabel->setVisible(false);
            needCoin->setVisible(false);
            itemPriceLabel->setVisible(false);
            // 解除购买按钮的绑定及可见
            buyButton->setUserData(nullptr);
            buyButton->setVisible(false);
        }
        else
        {
            // 如果触摸结束时不在按钮区域内，也切换回正常状态
            closeButton->setNormalImage(Sprite::create("ui/close_normal.png"));
        }

        // 检查是否点击了 buyButton
        if (buyButton) {
            Vec2 buyButtonPosition = buyButton->getPosition();
            Size buyButtonSize = buyButton->getContentSize();
            Rect buyButtonBoundingBox = Rect(buyButtonPosition.x - buyButtonSize.width,
                buyButtonPosition.y - buyButtonSize.height,
                buyButtonSize.width, buyButtonSize.height);

            if (buyButtonBoundingBox.containsPoint(mousePosition))
            {
                // 如果点击了 buyButton，切换回正常状态的图片并执行购买逻辑
                buyButton->setNormalImage(Sprite::create("ui/buy_button_normal.png"));
                buyResultLabel->setPosition(shopPos + Vec2(0, 50));
                buyButton->activate(); // 执行购买逻辑
            }
            else
            {
                // 如果触摸结束时不在按钮区域内，也切换回正常状态
                buyButton->setNormalImage(Sprite::create("ui/buy_button_normal.png"));
            }
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}