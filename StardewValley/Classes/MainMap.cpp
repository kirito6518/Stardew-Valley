#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "MainMap.h"
#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;

Scene* MainMap::createScene()
{
    return MainMap::create();
}

bool MainMap::init()
{
    if (!Scene::init())
    {
        return false;
    }

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    // 原点是窗口左下角
    // 加载背包
    Bag = BackpackManager::getInstance();
    // 加载地图
    mapSprite = Sprite::create("Farm_Combat.png");
    mapSprite->setAnchorPoint(Vec2(0.5, 0.5));
    mapSprite->setPosition(visibleSize / 2);
    this->addChild(mapSprite, 0);



    /*此处为test*/
#if 1
    // 创建一个物品精灵（假设玩家可以拾取）
    auto itemSprite = Sprite::create("icons/test.png");
    std::string itemName = "Test";
    std::string itemImagePath = "icons/test.png";
    ItemCategory category = ItemCategory::Consumable;
    bool success = BackpackManager::getInstance()->addItem(itemImagePath, itemName, category);

#endif
    /*此处为test*/




    // 添加一个按钮，左键点击后切回主屏幕
    toHollowWorldButton = MenuItemImage::create(
        "ui/CloseNormal.png",
        "ui/CloseSelected.png",
        CC_CALLBACK_1(MainMap::toMenu, this));
    //设置坐标
    float x = visibleSize.width - toHollowWorldButton->getContentSize().width / 2;
    float y = toHollowWorldButton->getContentSize().height / 2;
    toHollowWorldButton->setPosition(Vec2(x, y));

    // 添加点击事件监听器
    auto toHollowWorldListener = EventListenerTouchOneByOne::create();

    // 点击开始
    toHollowWorldListener->onTouchBegan = [this](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        if (rect.containsPoint(locationInNode))
        {
            // 切换到按下状态的图片
            toHollowWorldButton->setNormalImage(Sprite::create("ui/CloseSelected.png"));
            return true;
        }
        return false;
        };

    // 点击结束
    toHollowWorldListener->onTouchEnded = [this](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        if (rect.containsPoint(locationInNode))
        {
            // 切换回正常状态的图片
            toHollowWorldButton->setNormalImage(Sprite::create("ui/CloseNormal.png"));
            toMenu(nullptr);
        }
        else
        {
            // 如果触摸结束时不在按钮区域内，也切换回正常状态
            toHollowWorldButton->setNormalImage(Sprite::create("ui/CloseNormal.png"));
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(toHollowWorldListener, toHollowWorldButton);

    // 添加到图层
    this->addChild(toHollowWorldButton, 2);

    // 添加一段文本
    toHollowWorldWord = Label::createWithTTF("Menu", "fonts/Marker Felt.ttf", 35);
    // 将标签放在按钮里
    x = visibleSize.width - toHollowWorldWord->getContentSize().width / 2;
    y = toHollowWorldWord->getContentSize().height / 2;
    toHollowWorldWord->setPosition(Vec2(x - 20, y + 5));
    // 将标签作为子标签添加到此图层
    this->addChild(toHollowWorldWord, 2);

    // 添加一个按钮，左键点击后打开背包
    // 创建背包按钮
    backpackButton = MenuItemImage::create(
        "ui/BagBottom_normal.png",  // 按钮正常状态的图片
        "ui/BagBottom_pressed.png", // 按钮按下状态的图片
        CC_CALLBACK_1(MainMap::onBackpackButtonClicked, this));
    //设置坐标
    x = visibleSize.width - backpackButton->getContentSize().width / 2;
    y = visibleSize.height - backpackButton->getContentSize().height / 2 + 12;
    backpackButton->setPosition(Vec2(x, y));
    backpackButton->setScale(0.8f);

    // 添加点击事件监听器
    auto backpackListener = EventListenerTouchOneByOne::create();

    // 点击开始
    backpackListener->onTouchBegan = [this](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        if (rect.containsPoint(locationInNode))
        {
            // 切换到按下状态的图片
            backpackButton->setNormalImage(Sprite::create("ui/BagBottom_pressed.png"));
            return true;
        }
        return false;
        };

    // 点击结束
    backpackListener->onTouchEnded = [this](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        if (rect.containsPoint(locationInNode))
        {
            // 切换回正常状态的图片
            backpackButton->setNormalImage(Sprite::create("ui/BagBottom_normal.png"));
            onBackpackButtonClicked(nullptr);
        }
        else
        {
            // 如果触摸结束时不在按钮区域内，也切换回正常状态
            backpackButton->setNormalImage(Sprite::create("ui/BagBottom_normal.png"));
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(backpackListener, backpackButton);

    // 添加到图层
    this->addChild(backpackButton, 2);

    // 创建主角精灵
    player.playerSprite->setPosition(visibleSize / 2); // 初始位置在屏幕中央
    this->addChild(player.playerSprite, 1);

    // 注册键盘事件
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, &player);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, &player);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // 每多少s更新主角位置
    this->schedule(CC_SCHEDULE_SELECTOR(MainMap::updatePlayerPosition), 0.2f);
    // 每多少s更新摄像头和按钮位置
    this->schedule(CC_SCHEDULE_SELECTOR(MainMap::updateCameraPosition), 0);
    return true;
}

// 切换到主菜单
void MainMap::toMenu(Ref* ref)
{
    auto HollowWorldScene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(HollowWorldScene);
}

// 背包按钮的回调函数
void MainMap::onBackpackButtonClicked(Ref* sender)
{
    // 调用单例管理类显示背包层
    Bag->showBackpack(this);
}

// 每0.2s更新玩家位置和动画
void MainMap::updatePlayerPosition(float delta)
{
    // 更新玩家的位置和动画
    player.update(delta);
}

// 每帧更新摄像头和按钮位置
void MainMap::updateCameraPosition(float dt) {

    // 获取玩家的位置
    const Vec2 playerPosition = player.playerSprite->getPosition();// 锚点是左下角的一个位置

    // 输出玩家位置
    CCLOG("player position: (%f,%f)", playerPosition.x, playerPosition.y);

    //获取屏幕大小和地图大小
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto mapSize = mapSprite->getContentSize();

    // 计算摄像机左下角的目标位置，使玩家保持在屏幕中心
    Vec2 targetCameraPosition = playerPosition - Vec2(visibleSize.width / 2, visibleSize.height / 2);

    // 限制摄像机的移动范围
    float maxX = mapSize.width - visibleSize.width;
    float maxY = mapSize.height - visibleSize.height;

    // 确保摄像机的 x 坐标在范围内
    if (targetCameraPosition.x < -maxX / 2) {
        targetCameraPosition.x = -maxX / 2;
    }
    else if (targetCameraPosition.x > maxX / 2) {
        targetCameraPosition.x = maxX / 2;
    }

    // 确保摄像机的 y 坐标在范围内
    if (targetCameraPosition.y < -maxY / 2) {
        targetCameraPosition.y = -maxY / 2;
    }
    else if (targetCameraPosition.y > maxY / 2) {
        targetCameraPosition.y = maxY / 2;
    }

    // 输出摄像机位置
    CCLOG("camera position: (%f,%f)", targetCameraPosition.x, targetCameraPosition.y);

    // 更新摄像机的位置
    this->setPosition(-targetCameraPosition);

    //获取backpackLayer实例
    auto BackpackLayer = Bag->backpackLayer;
 
    // 更新背包位置
    auto backpackSize = BackpackLayer->backpackBgSprite->getContentSize();
    BackpackLayer->hideButton->setPosition(targetCameraPosition + Vec2(visibleSize.width / 2 + backpackSize.width / 2, visibleSize.height / 2 + backpackSize.height / 2));
    BackpackLayer->backpackBgSprite->setPosition(targetCameraPosition + visibleSize / 2);


    //更新物品图标的坐标值
   
    int dx, dy;   //物品坐标相对于背包初始坐标的偏移量

    int Spcount = 0;
    int Itemcount = 0;

    const cocos2d::Vector<Sprite*>& Itemsprites = BackpackLayer->getItemSprites();
    for (auto Itemsprite : Itemsprites)
    {
        dx = Spcount % 10 * (BackpackLayer->gridWidth + BackpackLayer->gridSpacing);
        dy = Spcount / 10 * (BackpackLayer->gridHeight + BackpackLayer->gridSpacing);
        Itemsprite->setPosition(targetCameraPosition+Vec2(BackpackLayer->gridStartX+dx, BackpackLayer->gridStartY+dy));
        Spcount++;
    }

    // 重新绑定鼠标事件监听器
    BackpackLayer->setupCombinedMouseListener();




    // 更新背包按钮、Menu按钮和文字的位置，使它们始终保持在屏幕的固定位置
    backpackButton->setPosition(targetCameraPosition + Vec2(visibleSize.width - backpackButton->getContentSize().width / 2, visibleSize.height - backpackButton->getContentSize().height / 2 + 12));

    toHollowWorldButton->setPosition(targetCameraPosition + Vec2(visibleSize.width - toHollowWorldButton->getContentSize().width / 2, toHollowWorldButton->getContentSize().height / 2));

    toHollowWorldWord->setPosition(targetCameraPosition + Vec2(visibleSize.width - toHollowWorldWord->getContentSize().width / 2 - 20, toHollowWorldWord->getContentSize().height / 2 + 5));
}
