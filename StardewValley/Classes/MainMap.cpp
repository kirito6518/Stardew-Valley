#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "MainMap.h"
#include "cocos2d.h"
#include "Player.h"
#include "chipmunk.h"
#include "Item.h"

USING_NS_CC;

Scene* MainMap::createScene()
{
    return MainMap::create();
}

bool MainMap::init()
{
    // 带物理地创建
    if (!Scene::initWithPhysics())
    {
        return false;
    }
    // 原点是窗口左下角
    const auto visibleSize = Director::getInstance()->getVisibleSize();

    // 获取物理世界
    auto physicsWorld = this->getPhysicsWorld();
    physicsWorld->setGravity(Vec2(0, 0));// 设置重力，无

    // 启用调试绘制
    physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // 加载背包
    Bag = BackpackManager::getInstance();

    // 加载地图
    mapSprite = Sprite::create("maps/Farm_Combat.png");// 1920 * 1560的
    mapSprite->setAnchorPoint(Vec2(0.5, 0.5));
    mapSprite->setPosition(visibleSize / 2);
    this->addChild(mapSprite, 0);

    // 载入地图互动点和碰撞箱
    // 上边界
    upBoundary = Sprite::create("maps/upBoundary.png");// 1920 * 96的
    upBoundary->setAnchorPoint(Vec2(0.5, 0.5));
    upBoundary->setPosition(visibleSize / 2 + Size(0, 780 - 48));
    auto upBoundaryBox = PhysicsBody::createBox(upBoundary->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    upBoundaryBox->setDynamic(false);
    upBoundary->setPhysicsBody(upBoundaryBox);
    this->addChild(upBoundary, 0);

    // 右边界
    rightBoundary = Sprite::create("maps/rightBoundary.png");// 72 * 1560的
    rightBoundary->setAnchorPoint(Vec2(0.5, 0.5));
    rightBoundary->setPosition(visibleSize / 2 + Size(960 - 36, 0));
    auto rightBoundaryBox = PhysicsBody::createBox(rightBoundary->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    rightBoundaryBox->setDynamic(false);
    rightBoundary->setPhysicsBody(rightBoundaryBox);
    this->addChild(rightBoundary, 0);

    // 左边界
    leftBoundary = Sprite::create("maps/leftBoundary.png");// 72 * 1560的
    leftBoundary->setAnchorPoint(Vec2(0.5, 0.5));
    leftBoundary->setPosition(visibleSize / 2 - Size(960 - 36, 0));
    auto leftBoundaryBox = PhysicsBody::createBox(leftBoundary->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    leftBoundaryBox->setDynamic(false);
    leftBoundary->setPhysicsBody(leftBoundaryBox);
    this->addChild(leftBoundary, 0);

    // 下边界左半部分
    downBoundary_left = Sprite::create("maps/downBoundary_left.png");// 936 * 96的
    downBoundary_left->setAnchorPoint(Vec2(0.0, 0.0));
    downBoundary_left->setPosition(visibleSize / 2 - Size(960, 780));
    auto downBoundary_leftBox = PhysicsBody::createBox(downBoundary_left->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    downBoundary_leftBox->setDynamic(false);
    downBoundary_left->setPhysicsBody(downBoundary_leftBox);
    this->addChild(downBoundary_left, 0);

    // 下边界右半部分
    downBoundary_right = Sprite::create("maps/downBoundary_right.png");// 936 * 96的
    downBoundary_right->setAnchorPoint(Vec2(1.0, 0.0));
    downBoundary_right->setPosition(visibleSize / 2 + Size(960, -780));
    auto downBoundary_rightBox = PhysicsBody::createBox(downBoundary_right->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    downBoundary_rightBox->setDynamic(false);
    downBoundary_right->setPhysicsBody(downBoundary_rightBox);
    this->addChild(downBoundary_right, 0);

    // 水池上半部分
    upWater = Sprite::create("maps/upWater.png");// 672 * 456的
    upWater->setAnchorPoint(Vec2(0.0, 0.5));// 设置锚点
    upWater->setPosition(visibleSize / 2 + Size(-960, -120));
    auto upWaterBox = PhysicsBody::createBox(upWater->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    upWaterBox->setDynamic(false);
    upWater->setPhysicsBody(upWaterBox);
    this->addChild(upWater, 0);

    // 水池中间部分
    middleWater = Sprite::create("maps/middleWater.png");// 648 * 96的
    middleWater->setAnchorPoint(Vec2(0.0, 0.5));// 设置锚点
    middleWater->setPosition(visibleSize / 2 + Size(-960, -780 + 408));
    auto middleWaterBox = PhysicsBody::createBox(middleWater->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    middleWaterBox->setDynamic(false);
    middleWater->setPhysicsBody(middleWaterBox);
    this->addChild(middleWater, 0);

    // 水池下半部分
    downWater = Sprite::create("maps/downWater.png");// 672 * 378的
    downWater->setAnchorPoint(Vec2(0.0, 0.0));// 设置锚点
    downWater->setPosition(visibleSize / 2 + Size(-960, -780));
    auto downWaterBox = PhysicsBody::createBox(downWater->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    downWaterBox->setDynamic(false);
    downWater->setPhysicsBody(downWaterBox);
    this->addChild(downWater, 0);

    // 房屋
    home = Sprite::create("maps/home.png");// 240 * 336的
    home->setAnchorPoint(Vec2(1.0, 1.0));// 设置锚点
    home->setPosition(visibleSize / 2 + Size(960, 780));
    auto homeBox = PhysicsBody::createBox(home->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    homeBox->setDynamic(false);
    home->setPhysicsBody(homeBox);
    this->addChild(home, 0);

    // 栅栏
    fence = Sprite::create("maps/fence.png");// 24 * 720的
    fence->setAnchorPoint(Vec2(0.0, 1.0));// 设置锚点
    fence->setPosition(visibleSize / 2 + Size(-960 + 24 * 29, 780));
    auto fenceBox = PhysicsBody::createBox(fence->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    fenceBox->setDynamic(false);
    fence->setPhysicsBody(fenceBox);
    this->addChild(fence, 0);

    // 下面的可以互动
    // 钓鱼部分
    fishing = Sprite::create("maps/fishing.png");// 96 * 96的
    fishing->setAnchorPoint(Vec2(0.5, 0.5));// 设置锚点
    fishing->setPosition(visibleSize / 2 + Size(-960 + 624, -780 + 408));
    auto fishingBox = PhysicsBody::createBox(fishing->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    fishingBox->setDynamic(false);
    fishing->setPhysicsBody(fishingBox);
    this->addChild(fishing, 0);

    // 农田左部分
    CropsLeft = Sprite::create("maps/Crops.png");// 192 * 192的
    CropsLeft->setAnchorPoint(Vec2(0.0, 1.0));// 设置锚点
    CropsLeft->setPosition(visibleSize / 2 + Size(-960 + 1224, -780 + 336));
    auto CropsLeftBox = PhysicsBody::createBox(CropsLeft->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    CropsLeftBox->setDynamic(false);
    CropsLeft->setPhysicsBody(CropsLeftBox);
    this->addChild(CropsLeft, 0);

    // 农田右部分
    CropsRight = Sprite::create("maps/Crops.png");// 192 * 192的
    CropsRight->setAnchorPoint(Vec2(0.0, 1.0));// 设置锚点
    CropsRight->setPosition(visibleSize / 2 + Size(-960 + 1464, -780 + 336));
    auto CropsRightBox = PhysicsBody::createBox(CropsRight->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    CropsRightBox->setDynamic(false);
    CropsRight->setPhysicsBody(CropsRightBox);
    this->addChild(CropsRight, 0);

    // 路
    road = Sprite::create("maps/road.png");// 96 * 96的
    road->setAnchorPoint(Vec2(1.0, 0.0));// 设置锚点
    road->setPosition(visibleSize / 2 + Size(48, -780));
    auto roadBox = PhysicsBody::createBox(road->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    roadBox->setDynamic(false);
    road->setPhysicsBody(roadBox);
    this->addChild(road, 0);

    // 牧场
    ranch = Sprite::create("maps/ranch.png");// 96 * 96的
    ranch->setAnchorPoint(Vec2(1.0, 0.0));// 设置锚点
    ranch->setPosition(visibleSize / 2 + Size(-960 + 24 * 30, 60));
    auto ranchBox = PhysicsBody::createBox(ranch->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    ranchBox->setDynamic(false);
    ranch->setPhysicsBody(ranchBox);
    this->addChild(ranch, 0);
    /*
    // 创建物品精灵
    std::string itemName = "Test";
    std::string itemName2 = "Test2";
    std::string itemImagePath = "icons/test.png";
    ItemCategory category = ItemCategory::Food;
    bool success = BackpackManager::getInstance()->addItem(itemImagePath, itemName, category,6);
    Item* item = Bag->getItemByName("Test");
    if (item) {
        // 定义一个自定义的 useItem 逻辑
        auto customUseItemLogic = [item]() -> bool {
            int countUsed = 2; // 假设每次使用 2 个物品
            if (1)
            {
                item->decreaseCount(countUsed);
                return true;
            }
            return false;
            };

        // 设置回调函数
        item->setUseItemCallback(customUseItemLogic);
    }
    else {
        CCLOG("Item 'test' not found in backpack.");
    }
    */
    // 初始放入背包物品
    bool success2 = BackpackManager::getInstance()->addItem("crops/OnionSeed.png", "Onion\nSeed", ItemCategory::Crops);// 洋葱种子

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

    // 为玩家添加物理体
    auto playerBody = PhysicsBody::createBox(player.playerSprite->getContentSize() / 4, PhysicsMaterial(0.1f, 0.0f, 0.0f));// 密度 弹性 摩擦力
    playerBody->setDynamic(true); // 设置为动态物理体
    player.playerSprite->setPhysicsBody(playerBody);// 设置物理体
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

// 每帧更新摄像头和按钮位置，更新碰撞体
void MainMap::updateCameraPosition(float dt) {

    // 获取玩家的位置
    const Vec2 playerPosition = player.playerSprite->getPosition();// 锚点是左下角的一个位置

    //获取屏幕大小和地图大小
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto mapSize = mapSprite->getContentSize();

    // 输出玩家位置
    CCLOG("player position: (%f,%f)", playerPosition.x, playerPosition.y);

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


#if 0
    Item* item = Bag->getItemByName("Test");
    if (item) {
        // 定义一个自定义的 useItem 逻辑
        auto customUseItemLogic = [item]() -> bool {
            int countUsed = 2; // 假设每次使用 2 个物品
            if (1)
            {
                item->decreaseCount(countUsed);
                return true;
            }
            return false;
            };

        // 设置回调函数
        item->setUseItemCallback(customUseItemLogic);
    }
    else {
        CCLOG("Item 'test' not found in backpack.");
    }
#endif

    //更新物品图标的坐标值
   
    int dx, dy;   //物品坐标相对于背包初始坐标的偏移量

    int Spcount = 0;
    int Itemcount = 0;

    const cocos2d::Vector<Sprite*>& Itemsprites = BackpackLayer->getItemSprites();
    for (auto Itemsprite : Itemsprites)
    {
        dx = Spcount % 10 * (BackpackLayer->gridWidth + BackpackLayer->gridSpacing);
        dy = Spcount / 10 * (BackpackLayer->gridHeight + BackpackLayer->gridSpacing);
        Itemsprite->setPosition(targetCameraPosition + Vec2(BackpackLayer->gridStartX + dx, BackpackLayer->gridStartY - dy));
        Spcount++;
    }

    // 重新绑定鼠标事件监听器
    BackpackLayer->setupCombinedMouseListener();

    // 更新背包按钮、Menu按钮和文字的位置，使它们始终保持在屏幕的固定位置
    backpackButton->setPosition(targetCameraPosition + Vec2(visibleSize.width - backpackButton->getContentSize().width / 2, visibleSize.height - backpackButton->getContentSize().height / 2 + 12));

    toHollowWorldButton->setPosition(targetCameraPosition + Vec2(visibleSize.width - toHollowWorldButton->getContentSize().width / 2, toHollowWorldButton->getContentSize().height / 2));

    toHollowWorldWord->setPosition(targetCameraPosition + Vec2(visibleSize.width - toHollowWorldWord->getContentSize().width / 2 - 20, toHollowWorldWord->getContentSize().height / 2 + 5));
}
