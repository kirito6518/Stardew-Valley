#include "Player.h"
#include "chipmunk.h"
#include "cocos2d.h"
#include "Cave.h"

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
    physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // 加载地图
    caveSprite = Sprite::create("maps/Cave.png");// 1152 * 1248的
    caveSprite->setAnchorPoint(Vec2(0.5, 0.5));
    caveSprite->setPosition(visibleSize / 2);
    this->addChild(caveSprite, 0);

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


    // 注册键盘事件
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, &player);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, &player);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // 每多少s更新主角位置
    this->schedule(CC_SCHEDULE_SELECTOR(Cave::updatePlayerPosition), 0.2f);
    // 每多少s更新摄像头和按钮位置
    this->schedule(CC_SCHEDULE_SELECTOR(Cave::updateCameraPosition), 0);

    return true;
}

// 每0.2s更新玩家位置和动画
void Cave::updatePlayerPosition(float delta)
{
    // 更新玩家的位置和动画
    player.update(delta);

}

// 每帧更新摄像头和按钮位置，更新碰撞体
void Cave::updateCameraPosition(float dt) {

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
    }
    return true;
}