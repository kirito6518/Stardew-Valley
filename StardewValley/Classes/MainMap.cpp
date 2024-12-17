#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "MainMap.h"
#include "cocos2d.h"
#include "Player.h"
#include "chipmunk.h"
#include "Item.h"
#include "BackpackManager.h"
#include "ItemManager.h"


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

    caveScene = nullptr;

    // 原点是窗口左下角
    const auto visibleSize = Director::getInstance()->getVisibleSize();

    // 获取物理世界
    auto physicsWorld = this->getPhysicsWorld();
    physicsWorld->setGravity(Vec2(0, 0));// 设置重力，无

    // 设置碰撞监听器
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(MainMap::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    // 启用调试绘制
    physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // 加载背包
    BackpackManager::getInstance();
    getInitBackpack();
    BackpackManager::getInstance()->mainMap = this;


    // 加载使用逻辑
    SetUseItemInMainMap();


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
    upBoundaryBox = PhysicsBody::createBox(upBoundary->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    upBoundaryBox->setDynamic(false);
    upBoundary->setPhysicsBody(upBoundaryBox);
    this->addChild(upBoundary, 0);

    // 右边界
    rightBoundary = Sprite::create("maps/rightBoundary.png");// 72 * 1560的
    rightBoundary->setAnchorPoint(Vec2(0.5, 0.5));
    rightBoundary->setPosition(visibleSize / 2 + Size(960 - 36, 0));
    rightBoundaryBox = PhysicsBody::createBox(rightBoundary->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    rightBoundaryBox->setDynamic(false);
    rightBoundary->setPhysicsBody(rightBoundaryBox);
    this->addChild(rightBoundary, 0);

    // 左边界
    leftBoundary = Sprite::create("maps/leftBoundary.png");// 72 * 1560的
    leftBoundary->setAnchorPoint(Vec2(0.5, 0.5));
    leftBoundary->setPosition(visibleSize / 2 - Size(960 - 36, 0));
    leftBoundaryBox = PhysicsBody::createBox(leftBoundary->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    leftBoundaryBox->setDynamic(false);
    leftBoundary->setPhysicsBody(leftBoundaryBox);
    this->addChild(leftBoundary, 0);

    // 下边界左半部分
    downBoundary_left = Sprite::create("maps/downBoundary_left.png");// 936 * 96的
    downBoundary_left->setAnchorPoint(Vec2(0.0, 0.0));
    downBoundary_left->setPosition(visibleSize / 2 - Size(960, 780));
    downBoundary_leftBox = PhysicsBody::createBox(downBoundary_left->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    downBoundary_leftBox->setDynamic(false);
    downBoundary_left->setPhysicsBody(downBoundary_leftBox);
    this->addChild(downBoundary_left, 0);

    // 下边界右半部分
    downBoundary_right = Sprite::create("maps/downBoundary_right.png");// 936 * 96的
    downBoundary_right->setAnchorPoint(Vec2(1.0, 0.0));
    downBoundary_right->setPosition(visibleSize / 2 + Size(960, -780));
    downBoundary_rightBox = PhysicsBody::createBox(downBoundary_right->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    downBoundary_rightBox->setDynamic(false);
    downBoundary_right->setPhysicsBody(downBoundary_rightBox);
    this->addChild(downBoundary_right, 0);

    // 水池上半部分
    upWater = Sprite::create("maps/upWater.png");// 672 * 456的
    upWater->setAnchorPoint(Vec2(0.0, 0.5));// 设置锚点
    upWater->setPosition(visibleSize / 2 + Size(-960, -120));
    upWaterBox = PhysicsBody::createBox(upWater->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    upWaterBox->setDynamic(false);
    upWater->setPhysicsBody(upWaterBox);
    this->addChild(upWater, 0);

    // 水池中间部分
    middleWater = Sprite::create("maps/middleWater.png");// 648 * 96的
    middleWater->setAnchorPoint(Vec2(0.0, 0.5));// 设置锚点
    middleWater->setPosition(visibleSize / 2 + Size(-960, -780 + 408));
    middleWaterBox = PhysicsBody::createBox(middleWater->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    middleWaterBox->setDynamic(false);
    middleWater->setPhysicsBody(middleWaterBox);
    this->addChild(middleWater, 0);

    // 水池下半部分
    downWater = Sprite::create("maps/downWater.png");// 672 * 378的
    downWater->setAnchorPoint(Vec2(0.0, 0.0));// 设置锚点
    downWater->setPosition(visibleSize / 2 + Size(-960, -780));
    downWaterBox = PhysicsBody::createBox(downWater->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    downWaterBox->setDynamic(false);
    downWater->setPhysicsBody(downWaterBox);
    this->addChild(downWater, 0);

    // 房屋
    home = Sprite::create("maps/home.png");// 240 * 336的
    home->setAnchorPoint(Vec2(1.0, 1.0));// 设置锚点
    home->setPosition(visibleSize / 2 + Size(960, 780));
    homeBox = PhysicsBody::createBox(home->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
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
    fishingBox = PhysicsBody::createBox(fishing->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    fishingBox->setDynamic(false);
    fishingBox->setCollisionBitmask(0x01);
    fishingBox->setContactTestBitmask(0x01);
    fishing->setPhysicsBody(fishingBox);
    this->addChild(fishing, 0);

    // 农田左部分
    CropsLeft = Sprite::create("maps/Crops.png");// 192 * 192的
    CropsLeft->setAnchorPoint(Vec2(0.0, 1.0));// 设置锚点
    CropsLeft->setPosition(visibleSize / 2 + Size(-960 + 1224, -780 + 336));
    CropsLeftBox = PhysicsBody::createBox(CropsLeft->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    CropsLeftBox->setDynamic(false);
    CropsLeftBox->setCollisionBitmask(0x01);
    CropsLeftBox->setContactTestBitmask(0x01);
    CropsLeft->setPhysicsBody(CropsLeftBox);
    this->addChild(CropsLeft, 0);

    // 农田右部分
    CropsRight = Sprite::create("maps/Crops.png");// 192 * 192的
    CropsRight->setAnchorPoint(Vec2(0.0, 1.0));// 设置锚点
    CropsRight->setPosition(visibleSize / 2 + Size(-960 + 1464, -780 + 336));
    CropsRightBox = PhysicsBody::createBox(CropsRight->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    CropsRightBox->setDynamic(false);
    CropsRightBox->setCollisionBitmask(0x01);
    CropsRightBox->setContactTestBitmask(0x01);
    CropsRight->setPhysicsBody(CropsRightBox);
    this->addChild(CropsRight, 0);

    // 路
    road = Sprite::create("maps/road.png");// 96 * 96的
    road->setAnchorPoint(Vec2(1.0, 0.0));// 设置锚点
    road->setPosition(visibleSize / 2 + Size(48, -780));
    roadBox = PhysicsBody::createBox(road->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    roadBox->setDynamic(false);
    roadBox->setCollisionBitmask(0x01);
    roadBox->setContactTestBitmask(0x01);
    road->setPhysicsBody(roadBox);
    this->addChild(road, 0);

    // 牧场
    ranch = Sprite::create("maps/ranch.png");// 96 * 96的
    ranch->setAnchorPoint(Vec2(1.0, 0.0));// 设置锚点
    ranch->setPosition(visibleSize / 2 + Size(-960 + 24 * 30, 60));
    ranchBox = PhysicsBody::createBox(ranch->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    ranchBox->setDynamic(false);
    ranchBox->setCollisionBitmask(0x01);
    ranchBox->setContactTestBitmask(0x01);
    ranch->setPhysicsBody(ranchBox);
    this->addChild(ranch, 0);

    fishing->setName("fishing");
    CropsLeft->setName("CropsLeft");
    CropsRight->setName("CropsRight");
    road->setName("road");
    ranch->setName("ranch");

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
    auto playerBox = PhysicsBody::createBox(player.playerSprite->getContentSize() / 4, PhysicsMaterial(0.1f, 0.0f, 0.0f));// 密度 弹性 摩擦力
    playerBox->setDynamic(true); // 设置为动态物理体
    playerBox->setCollisionBitmask(0x01);
    playerBox->setContactTestBitmask(0x01);
    player.playerSprite->setPhysicsBody(playerBox);// 设置物理体
    this->addChild(player.playerSprite, 1);

    {
        // 初始化 SeasonManager
        seasonManager = SeasonManager();

        // 创建并添加季节显示的 Label
        seasonLabel = Label::createWithTTF("Spring", "fonts/Marker Felt.ttf", 35);
        seasonLabel->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height - 20));
        this->addChild(seasonLabel, 1);

        // 创建并添加天数显示的 Label
        dayLabel = Label::createWithTTF("Day 1", "fonts/Marker Felt.ttf", 35);
        dayLabel->setPosition(seasonLabel->getPosition() + Vec2(seasonLabel->getContentSize().width + 10, 0)); // 设置在seasonLabel右侧
        this->addChild(dayLabel, 1);

        // 设置定时器，每 3 秒调用一次 addDay 函数
        this->schedule(schedule_selector(MainMap::addDay), 3.0f);
    }

    // 注册键盘事件
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, &player);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, &player);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // 初始化位置
    place = 0;

    // 每多少s更新主角位置
    this->schedule(CC_SCHEDULE_SELECTOR(MainMap::updatePlayerPosition), 0.2f);
    // 每多少s更新摄像头和按钮位置
    this->schedule(CC_SCHEDULE_SELECTOR(MainMap::updateCameraPosition), 0);
    
    {
        // 初始化 NPC
        npcManager.initNPCs();

        // 获取屏幕的中心位置
        const auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 screenCenter = Vec2(visibleSize.width / 2, visibleSize.height / 2);

        // 设置 NPC 的位置为屏幕中心
        npcManager._npcs[0]->setLocation(screenCenter);

        // 确保 NPC 的精灵锚点为 (0.5, 0.5)
        npcManager._npcs[0]->setAnchorPoint(Vec2(0.5, 0.5));

        // 调试输出 NPC 的位置和精灵尺寸
        // CCLOG("NPC position: (%f, %f)", npcManager._npcs[0]->getLocation().x, npcManager._npcs[0]->getLocation().y);
        // CCLOG("NPC sprite size: (%f, %f)", npcManager._npcs[0]->getContentSize().width, npcManager._npcs[0]->getContentSize().height);

        // 将 NPC 添加到场景中
        this->addChild(npcManager._npcs[0], 1);
    }
    // 初始化农田
    farmManager.initFarm();
    this->schedule(schedule_selector(MainMap::updateFarm), 1.0f);

    return true;
}

void MainMap::updateFarm(float dt) {
    farmManager.update(dt);
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
    BackpackManager::getInstance()->showBackpack(this);

    // 禁用 MainMap 场景的时间更新
    this->unschedule(CC_SCHEDULE_SELECTOR(MainMap::updatePlayerPosition));
    this->unschedule(CC_SCHEDULE_SELECTOR(MainMap::updateCameraPosition));

}

// 隐藏背包
void MainMap::hideBackpack(Ref* sender)
{
    // 重新启用 MainMap 场景的时间更新
    this->schedule(CC_SCHEDULE_SELECTOR(MainMap::updatePlayerPosition), 0.2f);
    this->schedule(CC_SCHEDULE_SELECTOR(MainMap::updateCameraPosition), 0);
}

//清空背包物品
void MainMap::clearBackpack()
{
    auto items = BackpackManager::getInstance()->getItems();
    for (auto item : items) {

        item->clearItem();//清空物品数量
    }
}

void MainMap::getInitBackpack() 
{
    clearBackpack();
    Item* initItem;
    initItem = ItemManager::getInstance()->getItem("Coin");
    BackpackManager::getInstance()->addItem(initItem, 3);
    initItem = ItemManager::getInstance()->getItem("Onion\nSeed");
    BackpackManager::getInstance()->addItem(initItem, 3);
}

// 每0.2s更新玩家位置和动画
void MainMap::updatePlayerPosition(float delta)
{
    // 更新玩家的位置和动画
    player.update(delta);
}

// 每帧更新摄像头和按钮位置，更新碰撞体
void MainMap::updateCameraPosition(float dt) {

    // 如果已经触发了洞穴场景且刚刚传送回来
    if (caveScene && place == 4) {
        player.playerSprite->setPosition(Vec2(640, -430 + 96 + 48));
        // 初始化属性
        player.isWPressed = player.isAPressed = player.isSPressed = player.isDPressed = false; // 初始化键盘状态
    }

    // 将 place 置为零
    place = 0;

    // 获取玩家的位置
    const Vec2 playerPosition = player.playerSprite->getPosition();// 锚点是左下角的一个位置

    //获取屏幕大小和地图大小
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto mapSize = mapSprite->getContentSize();

    // 输出玩家位置
    // CCLOG("player position: (%f,%f)", playerPosition.x, playerPosition.y);

    // 检查玩家与 NPC 的交互
    npcManager.checkPlayerInteraction(player.playerSprite->getPosition());

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
    // CCLOG("camera position: (%f,%f)", targetCameraPosition.x, targetCameraPosition.y);

    // 更新摄像机的位置
    this->setPosition(-targetCameraPosition);

    //获取backpackLayer实例
    auto BackpackLayer = BackpackManager::getInstance()->backpackLayer;
 
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
        Itemsprite->setPosition(targetCameraPosition + Vec2(BackpackLayer->gridStartX + dx, BackpackLayer->gridStartY - dy));
        Spcount++;
    }

    // 重新绑定鼠标事件监听器
    BackpackLayer->setupCombinedMouseListener();

    // 更新背包按钮、Menu按钮和文字的位置，使它们始终保持在屏幕的固定位置
    backpackButton->setPosition(targetCameraPosition + Vec2(visibleSize.width - backpackButton->getContentSize().width / 2, visibleSize.height - backpackButton->getContentSize().height / 2 + 12));

    toHollowWorldButton->setPosition(targetCameraPosition + Vec2(visibleSize.width - toHollowWorldButton->getContentSize().width / 2, toHollowWorldButton->getContentSize().height / 2));

    toHollowWorldWord->setPosition(targetCameraPosition + Vec2(visibleSize.width - toHollowWorldWord->getContentSize().width / 2 - 20, toHollowWorldWord->getContentSize().height / 2 + 5));

    seasonLabel->setPosition(targetCameraPosition + Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height - 20));
    dayLabel->setPosition(seasonLabel->getPosition() + Vec2(seasonLabel->getContentSize().width + 10, 0));
}

void MainMap::addDay(float dt)
{
    // 增加一天
    seasonManager.updateSeason(1);

    // 获取当前季节名称并更新 Label
    std::string seasonName = seasonManager.getCurrentSeasonName();
    seasonLabel->setString(seasonName);

    // 获取当前季节的天数并更新 dayLabel
    int day = seasonManager.getDaysInCurrentSeason() + 1; // 天数从1开始
    std::string dayText = "Day " + std::to_string(day);
    dayLabel->setString(dayText);
}

// 设置物品在MainMap的使用逻辑,0是在空地，1是在左农场，2是在右农场
void  MainMap::SetUseItemInMainMap() {
    
    // 设置洋葱种子
    if (ItemManager::getInstance()->getItem("Onion\nSeed")) {
        // 定义一个自定义的 useItem 逻辑
        auto customUseItemLogic = [this]() -> bool {
            auto OnionSeed = ItemManager::getInstance()->getItem("Onion\nSeed");
            Vec2 plantingPosition;
            if (place == 1 || place == 2) {
                int countUsed = 1; // 假设每次使用 1 个物品
                if (place == 1) {// 如果在左边农场
                    plantingPosition = CropsLeft->getPosition() + Vec2(96, -96);
                    if (!farmManager.isPositionOccupied(plantingPosition)) {//判断作物是否是0作物
                        OnionSeed->decreaseCount(countUsed);
                        farmManager.plantCrop("Onion1", "crops/Onion1.png", 100, 7, 10, Vec2(CropsLeft->getPosition()+Vec2(96,-96)));
                        this->addChild(farmManager._crops[0], 1);
                        return true;
                    }
                }
                else if (place == 2) {// 如果在右边农场
                    plantingPosition = CropsRight->getPosition() + Vec2(96, -96);
                    if (!farmManager.isPositionOccupied(plantingPosition)) {//判断作物是否是0作物
                        OnionSeed->decreaseCount(countUsed);
                        farmManager.plantCrop("Onion2", "crops/Onion1.png", 100, 7, 10, Vec2(CropsRight->getPosition() + Vec2(96,-96)));
                        this->addChild(farmManager._crops[1], 1);
                        return true;
                    }
                }
            }
            return false;
            };

        // 设置回调函数
        ItemManager::getInstance()->getItem("Onion\nSeed")->setUseItemCallback(customUseItemLogic);
    }
    else {
        CCLOG("Item 'test' not found in backpack.");
    }
}

// 碰撞开始监听器
bool MainMap::onContactBegin(PhysicsContact& contact) {
    // 获取碰撞的两个物理体
    auto bodyA = contact.getShapeA()->getBody();
    auto bodyB = contact.getShapeB()->getBody();

    // 获取物理体对应的节点
    auto nodeA = bodyA->getNode();
    auto nodeB = bodyB->getNode();

    // 输出碰撞信息
    // CCLOG("Collision between: %s and %s", nodeA->getName().c_str(), nodeB->getName().c_str());

    // 在这里添加碰撞后的逻辑
    // 例如：判断碰撞的物体是否是玩家和某个特定物体
    if (nodeB->getName() == "fishing" || nodeA->getName() == "fishing") {
        // CCLOG("Player collided with fishing area!");
        // 执行钓鱼逻辑
        place = 3; // 设置位置为钓鱼点
    }
    else if (nodeB->getName() == "CropsLeft" || nodeA->getName() == "CropsLeft") {
        // CCLOG("Player collided with left farm!");
        // 执行左农场逻辑
        place = 1; // 设置位置为左农场
        backpackButton->activate(); // 打开背包
    }
    else if (nodeB->getName() == "CropsRight" || nodeA->getName() == "CropsRight") {
        // CCLOG("Player collided with right farm!");
        // 执行右农场逻辑
        place = 2; // 设置位置为右农场
        backpackButton->activate(); // 打开背包
    }
    else if (nodeB->getName() == "road" || nodeA->getName() == "road") {
        // CCLOG("Player collided with road!");
        // 执行路逻辑
        place = 4; // 设置位置为路
        // 创建新场景
        caveScene = Cave::createScene();
        // 将新场景推入场景栈
        Director::getInstance()->pushScene(caveScene);
    }
    else if (nodeB->getName() == "ranch" || nodeA->getName() == "ranch") {
        // CCLOG("Player collided with ranch!");
        // 执行牧场逻辑
        place = 5; // 设置位置为牧场
    }

    // 返回 true 表示允许碰撞继续处理
    return true;
}