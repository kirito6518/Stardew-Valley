#include "Player.h"
#include "chipmunk.h"
#include "cocos2d.h"
#include "Cave.h"
#include "BringMine.h"
#include "MainMap.h"

USING_NS_CC;

Scene* Cave::createScene()
{
    return Cave::create();
}

bool Cave::init()
{
    // 带物理地创建
    if (!Scene::initWithPhysics())
    {
        return false;
    }
    // 初始化随机数系统
    srand((unsigned)(time(0)));

    gem = 0;

    // 初始化Layer
    chooseMineLayer = ChooseMineLayer::getInstance();

    // 检查 chooseMineLayer 是否为 nullptr
    if (chooseMineLayer == nullptr) {
        CCLOG("Failed to create ChooseMineLayer instance!");
        return false;
    }

    // 原点是窗口左下角
    const auto visibleSize = Director::getInstance()->getVisibleSize();

    // 获取物理世界
    auto physicsWorld = this->getPhysicsWorld();
    physicsWorld->setGravity(Vec2(0, 0));// 设置重力，无

    // 设置碰撞监听器
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Cave::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    // 启用调试绘制
    // physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // 加载地图
    caveSprite = Sprite::create("maps/Cave.png");// 1152 * 1248的
    caveSprite->setAnchorPoint(Vec2(0.5, 0.5));
    caveSprite->setPosition(visibleSize / 2);
    this->addChild(caveSprite, 0);

    // 加载宝石
    gemSprite1 = Sprite::create("mineral/GemA.png");
    gemSprite1->retain();
    gemSprite2 = Sprite::create("mineral/GemB.png");
    gemSprite2->retain();
    gemSprite3 = Sprite::create("mineral/GemC.png");
    gemSprite3->retain();
    gemSprite4 = Sprite::create("mineral/GemD.png");
    gemSprite4->retain();
    gemSprite5 = Sprite::create("mineral/GemE.png");
    gemSprite5->retain();

    // 载入地图互动点和碰撞箱

    // 上边界
    caveUpBoundary = Sprite::create("maps/caveUpBoundary.png");// 1152 * 168的
    caveUpBoundary->setAnchorPoint(Vec2(0.5, 1.0));
    caveUpBoundary->setPosition(visibleSize / 2 + Size(0, 1248 / 2));
    caveUpBoundaryBox = PhysicsBody::createBox(caveUpBoundary->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    caveUpBoundaryBox->setDynamic(false);
    caveUpBoundary->setPhysicsBody(caveUpBoundaryBox);
    this->addChild(caveUpBoundary, 0);

    // 右边界
    caveRightBoundary = Sprite::create("maps/caveRightBoundary.png");// 120 * 1248的
    caveRightBoundary->setAnchorPoint(Vec2(1.0, 0.5));
    caveRightBoundary->setPosition(visibleSize / 2 + Size(1152 / 2, 0));
    caveRightBoundaryBox = PhysicsBody::createBox(caveRightBoundary->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    caveRightBoundaryBox->setDynamic(false);
    caveRightBoundary->setPhysicsBody(caveRightBoundaryBox);
    this->addChild(caveRightBoundary, 0);

    // 左边界
    caveLeftBoundary = Sprite::create("maps/caveLeftBoundary.png");// 72 * 1248的
    caveLeftBoundary->setAnchorPoint(Vec2(0.0, 0.5));
    caveLeftBoundary->setPosition(visibleSize / 2 + Size(-1152 / 2, 0));
    caveLeftBoundaryBox = PhysicsBody::createBox(caveLeftBoundary->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    caveLeftBoundaryBox->setDynamic(false);
    caveLeftBoundary->setPhysicsBody(caveLeftBoundaryBox);
    this->addChild(caveLeftBoundary, 0);

    // 下边界
    caveDownBoundary = Sprite::create("maps/caveDownBoundary.png");// 1152 * 48的
    caveDownBoundary->setAnchorPoint(Vec2(0.5, 0.0));
    caveDownBoundary->setPosition(visibleSize / 2 + Size(0, -1248 / 2));
    caveDownBoundaryBox = PhysicsBody::createBox(caveDownBoundary->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    caveDownBoundaryBox->setDynamic(false);
    caveDownBoundary->setPhysicsBody(caveDownBoundaryBox);
    this->addChild(caveDownBoundary, 0);

    // 创建梯子
    ladder = Sprite::create("maps/ladder.png"); // 24 * 120的
    ladder->setAnchorPoint(Vec2(0.0f,1.0f)); // 左上角
    ladder->setPosition(visibleSize / 2 + Size(24, 552)); // 初始位置在屏幕上方
    ladderBox = PhysicsBody::createBox(ladder->getContentSize(), PhysicsMaterial(0.1f, 0.0f, 0.0f));// 密度 弹性 摩擦力
    ladderBox->setDynamic(false); // 设置为动态物理体
    ladderBox->setCollisionBitmask(0x01);
    ladderBox->setContactTestBitmask(0x01);
    ladder->setPhysicsBody(ladderBox);// 设置物理体
    this->addChild(ladder, 1);

    // 创建主角精灵
    player.playerSprite->setPosition(visibleSize / 2 + Size(24 + 12, 384)); // 初始位置在屏幕上方

    // 为玩家添加物理体
    playerBox = PhysicsBody::createBox(player.playerSprite->getContentSize() / 4, PhysicsMaterial(0.1f, 0.0f, 0.0f));// 密度 弹性 摩擦力
    playerBox->setDynamic(true); // 设置为动态物理体
    playerBox->setCollisionBitmask(0x01);
    playerBox->setContactTestBitmask(0x01);
    player.playerSprite->setPhysicsBody(playerBox);// 设置物理体
    this->addChild(player.playerSprite, 1);

    ladder->setName("ladder");

    // 创建黑暗背景
    black = Sprite::create("black.png"); // 4000 * 2000的
    black->setAnchorPoint(Vec2(0.5f, 0.5f)); // 中心
    black->setPosition(visibleSize / 2); // 初始位置在屏幕上方
    this->addChild(black, 2);

    // 生成矿物
    CreateMine();

    // 注册键盘事件
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, &player);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, &player);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // 每多少s更新摄像头和按钮位置
    this->schedule(CC_SCHEDULE_SELECTOR(Cave::update), 0);

    return true;
}

// 每帧更新摄像头和按钮位置，更新碰撞体
void Cave::update(float dt) {

    // 更新玩家的位置和动画
    player.update(dt);

    // 获取玩家的位置
    const Vec2 playerPosition = player.playerSprite->getPosition();// 锚点是左下角的一个位置
    black->setPosition(playerPosition); // 同步黑暗

    //获取屏幕大小和地图大小
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto mapSize = caveSprite->getContentSize();

    // 输出玩家位置
    // CCLOG("player position: (%f,%f)", playerPosition.x, playerPosition.y);

    // 计算摄像机左下角的目标位置，使玩家保持在屏幕中心
    Vec2 targetCameraPosition = playerPosition - Vec2(visibleSize.width / 2, visibleSize.height / 2);

    // 限制摄像机的移动范围
    float maxX = 0;
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

    // 更新宝石位置
    Gem(targetCameraPosition);

    chooseMineLayer->chooseLayer->setPosition(targetCameraPosition + visibleSize / 2);
    chooseMineLayer->yesButton->setPosition(targetCameraPosition + visibleSize / 2 + Vec2(-240, -136));
    chooseMineLayer->noButton->setPosition(targetCameraPosition + visibleSize / 2 + Vec2(+240, -136));

}

// 碰撞开始监听器
bool Cave::onContactBegin(PhysicsContact& contact) {
    // 获取碰撞的两个物理体
    auto bodyA = contact.getShapeA()->getBody();
    auto bodyB = contact.getShapeB()->getBody();

    // 获取物理体对应的节点
    auto nodeA = bodyA->getNode();
    auto nodeB = bodyB->getNode();

    // 输出碰撞信息
    // CCLOG("Collision between: %s and %s", nodeA->getName().c_str(), nodeB->getName().c_str());

    // 在这里添加碰撞后的逻辑
    if (nodeB->getName() == "ladder" || nodeA->getName() == "ladder") {
        // CCLOG("Player collided with ladder area!");
        Director::getInstance()->popScene(); // 返回上一个场景
        dynamic_cast<MainMap*>(mainMap)->BackFromCave();
    }
    else if (nodeB->getName() == "ShardE" || nodeA->getName() == "ShardE") {
        OpenLayer();
        chooseMineLayer->chooseMine = 5;
    }
    else if (nodeB->getName() == "ShardD" || nodeA->getName() == "ShardD") {
        OpenLayer();
        chooseMineLayer->chooseMine = 4;
    }
    else if (nodeB->getName() == "ShardC" || nodeA->getName() == "ShardC") {
        OpenLayer();
        chooseMineLayer->chooseMine = 3;
    }
    else if (nodeB->getName() == "ShardB" || nodeA->getName() == "ShardB") {
        OpenLayer();
        chooseMineLayer->chooseMine = 2;
    }
    else if (nodeB->getName() == "ShardA" || nodeA->getName() == "ShardA") {
        OpenLayer();
        chooseMineLayer->chooseMine = 1;
    }
    return true;
}

// 添加一个矿物
void Cave::AddMine(Sprite* mine, PhysicsBody* mineBox, Vec2 position) {

    auto num = rand() % 25 + 1;
    
    if (num == 1) { // 添加水晶E
        mine = Sprite::create("mineral/ShardE.png"); // 60 * 60的
        mine->setName("ShardE");
    }
    else if (num >= 2 && num <= 4) { // 添加水晶D
        mine = Sprite::create("mineral/ShardD.png"); // 60 * 60的
        mine->setName("ShardD");
    }
    else if (num >= 5 && num <= 9) { // 添加水晶C
        mine = Sprite::create("mineral/ShardC.png"); // 60 * 60的
        mine->setName("ShardC");
    }
    else if (num >= 10 && num <= 16) { // 添加水晶B
        mine = Sprite::create("mineral/ShardB.png"); // 60 * 60的
        mine->setName("ShardB");
    }
    else if (num >= 17 && num <= 25) { // 添加水晶A
        mine = Sprite::create("mineral/ShardA.png"); // 60 * 60的
        mine->setName("ShardA");
    }
    mine->setAnchorPoint(Vec2(0.5f, 0.5f)); // 中间
    mine->setPosition(position); // 初始位置
    mineBox = PhysicsBody::createBox(mine->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));// 密度 弹性 摩擦力
    mineBox->setDynamic(false); // 设置为动态物理体
    mineBox->setCollisionBitmask(0x01);
    mineBox->setContactTestBitmask(0x01);
    mine->setPhysicsBody(mineBox);// 设置物理体
    this->addChild(mine, 1);
}

// 随机生成矿物
void Cave::CreateMine() {
    // 获得屏幕尺寸和地图尺寸
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto mapSize = caveSprite->getContentSize();

    // 生成范围
    int minX = 144 + 60;
    int maxX = 1080 - 60;
    int minY = 192 + 60;
    int maxY = 816 - 60 - 72;

    for (int i = minX; i <= maxX; i = i + 168) {
        for (int j = minY; j <= maxY; j = j + 120) {
            auto num = rand() % 5 + 1;
            if (num == 5 && mines.size() <= 10) { // 五分之一的概率生成矿物
                Sprite* mine = Sprite::create();
                PhysicsBody* mineBox = PhysicsBody::create();
                // 生成矿物
                AddMine(mine, mineBox, Vec2(i, j));
                // 存入
                mines.push_back(mine);
                minesBox.push_back(mineBox);
            }
        }
    }
}

// 打开选项
void Cave::OpenLayer() {

    // 检查 chooseMineLayer 是否已经有父节点
    if (chooseMineLayer->getParent() == nullptr) {
        chooseMineLayer->cave = this;
        this->addChild(chooseMineLayer, 3);
    }
    // 禁用 Cave 场景的时间更新
    this->unschedule(CC_SCHEDULE_SELECTOR(Cave::update));
}

//隐藏选项
void Cave::HideLayer(Ref* sender){

    // 重新启用 cave 场景的时间更新
    this->schedule(CC_SCHEDULE_SELECTOR(Cave::update), 0);
    // 移除 chooseMineLayer
    if (chooseMineLayer->getParent()) {
        this->removeChild(chooseMineLayer);
    }
}

// 在屏幕下方显示可以带走的宝石
void Cave::Gem(Vec2 targetCameraPosition) {
    // 移除已经添加的宝石精灵
    if (gemSprite1->getParent()) {
        this->removeChild(gemSprite1);
    }
    if (gemSprite2->getParent()) {
        this->removeChild(gemSprite2);
    }
    if (gemSprite3->getParent()) {
        this->removeChild(gemSprite3);
    }
    if (gemSprite4->getParent()) {
        this->removeChild(gemSprite4);
    }
    if (gemSprite5->getParent()) {
        this->removeChild(gemSprite5);
    }

    // 根据 gem 编号添加对应的宝石精灵
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    switch (gem) {
        case 1:
            gemSprite1->setAnchorPoint(Vec2(0.5, 0.0));
            gemSprite1->setPosition(targetCameraPosition + Vec2(visibleSize.width / 2, 0));
            this->addChild(gemSprite1, 3);
            break;
        case 2:
            gemSprite2->setAnchorPoint(Vec2(0.5, 0.0));
            gemSprite2->setPosition(targetCameraPosition + Vec2(visibleSize.width / 2, 0));
            this->addChild(gemSprite2, 3);
            break;
        case 3:
            gemSprite3->setAnchorPoint(Vec2(0.5, 0.0));
            gemSprite3->setPosition(targetCameraPosition + Vec2(visibleSize.width / 2, 0));
            this->addChild(gemSprite3, 3);
            break;
        case 4:
            gemSprite4->setAnchorPoint(Vec2(0.5, 0.0));
            gemSprite4->setPosition(targetCameraPosition + Vec2(visibleSize.width / 2, 0));
            this->addChild(gemSprite4, 3);
            break;
        case 5:
            gemSprite5->setAnchorPoint(Vec2(0.5, 0.0));
            gemSprite5->setPosition(targetCameraPosition + Vec2(visibleSize.width / 2, 0));
            this->addChild(gemSprite5, 3);
            break;
        default:
            // 如果 gem 为 0，不添加任何宝石
            break;
    }
}
