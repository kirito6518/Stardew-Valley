#include "HelloWorldScene.h"
#include "MainMap.h"
#include "cocos2d.h"

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
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    {
        // 加载地图
        mapSprite = Sprite::create("Farm_Combat.png");
        mapSprite->setAnchorPoint(Vec2(0.5, 0.5));
        mapSprite->setPosition(visibleSize / 2);
        this->addChild(mapSprite, 0);
        mapSprite->setScale(1.2f); // 将 sprite 放大到原来的 1.2倍
    }


    //添加一个按钮，左键点击后切回主屏幕
    {
        {
            auto toHollowWorld = MenuItemImage::create(
                "CloseNormal.png", 
                "CloseSelected.png",
                CC_CALLBACK_1(MainMap::toMenu, this));
            //设置坐标
            const float x = visibleSize.width - toHollowWorld->getContentSize().width / 2;
            const float y = toHollowWorld->getContentSize().height / 2;
            toHollowWorld->setPosition(Vec2(x, y));
            // 创建菜单，它是一个自动释放对象
            auto menu = Menu::create(toHollowWorld, NULL);
            menu->setPosition(Vec2::ZERO);
            // 添加到图层
            this->addChild(menu, 1);
        }
        {
            // 添加一段文本
            auto toHollowWorld = Label::createWithTTF("Menu", "fonts/Marker Felt.ttf", 35);
            // 将标签放在按钮里
            const float x = visibleSize.width - toHollowWorld->getContentSize().width / 2;
            const float y = toHollowWorld->getContentSize().height / 2;
            toHollowWorld->setPosition(Vec2(x - 20, y + 5));
            // 将标签作为子标签添加到此图层
            this->addChild(toHollowWorld, 2);
        }
    }


    //添加一个按钮，左键点击后打开背包
    {
        // 创建背包按钮
        auto backpackButton = MenuItemImage::create(
            "BagBottom_normal.png",  // 按钮正常状态的图片
            "BagBottom_pressed.png", // 按钮按下状态的图片
            CC_CALLBACK_1(MainMap::onBackpackButtonClicked, this));

        //设置坐标
        const float x = visibleSize.width - backpackButton->getContentSize().width / 2;
        const float y = visibleSize.height - backpackButton->getContentSize().height / 2 + 12;
        backpackButton->setPosition(Vec2(x, y));
        backpackButton->setScale(0.8f);
        // 创建菜单，它是一个自动释放对象
        auto menu = Menu::create(backpackButton, NULL);
        menu->setPosition(Vec2::ZERO);
        // 添加到图层
        this->addChild(menu, 1);
    }

    // 创建主角精灵
    auto texture = Director::getInstance()->getTextureCache()->addImage("idle.png");
    playerSprite = Sprite::createWithTexture(texture, Rect(0, 0, 96.0, 96.0)); // 待机是向下待机的第一帧
    playerSprite->setPosition(visibleSize / 2); // 初始位置在屏幕中央
    this->addChild(playerSprite, 1);

    // 创建六个方向的行走动画
    createWalkAnimations();

    // 创建六个方向的待机动画
    createIdleAnimations();

    // 初始化目标位置
    targetPosition = playerSprite->getPosition();
    isMoving = false;

    // 初始化键盘状态
    isWPressed = isAPressed = isSPressed = isDPressed = false;

    // 初始化最后一次行走的方向索引
    lastDirectionIndex = 0; // 默认向下

    // 注册键盘事件
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(MainMap::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(MainMap::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // 每帧更新主角位置
    this->scheduleUpdate();

    return true;
}

// 切换到主菜单
void MainMap::toMenu(Ref* ref)
{
    auto HollowWorldScene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(HollowWorldScene);
}

// 创建六个方向的行走动画
void MainMap::createWalkAnimations()
{
    // 加载 walk.png 图片
    auto texture = Director::getInstance()->getTextureCache()->addImage("walk.png");

    // walk.png 是一个 6 方向的图片，每帧的宽度为 72 像素，高度为 96 像素
    const int frameWidth = 72;
    const int frameHeight = 96;
    const int framesPerDirection = 8; // 每个方向有 8 帧

    // 定义每个方向的帧范围
    // 方向顺序：下、左、左上、上、右上、右
    const int directionOffsets[6] = { 0, 1, 2, 3, 4, 5 }; // 6 个方向的偏移量

    for (int i = 0; i < 6; ++i)
    {
        Vector<SpriteFrame*> frames;
        for (int j = 0; j < framesPerDirection; ++j)
        {
            // 根据方向偏移量计算帧的坐标
            auto frame = SpriteFrame::createWithTexture(texture, Rect(j * frameWidth, directionOffsets[i] * frameHeight, frameWidth, frameHeight));
            frames.pushBack(frame);
        }

        // 创建动画
        walkAnimations[i] = Animation::createWithSpriteFrames(frames, 0.1f); // 每帧间隔 0.1 秒
        walkAnimations[i]->retain(); // 保留动画，防止被释放
    }
}

// 创建六个方向的待机动画
void MainMap::createIdleAnimations()
{
    // 加载 idle.png 图片
    auto texture = Director::getInstance()->getTextureCache()->addImage("idle.png");

    // idle.png 是一个 6 方向的图片，每帧的宽度为 72 像素，高度为 96 像素
    const int frameWidth = 72;
    const int frameHeight = 96;
    const int framesPerDirection = 8; // 每个方向有 8 帧

    // 定义每个方向的帧范围
    // 方向顺序：下、左、左上、上、右上、右
    const int directionOffsets[6] = { 0, 1, 2, 3, 4, 5 }; // 6 个方向的偏移量

    for (int i = 0; i < 6; ++i)
    {
        Vector<SpriteFrame*> frames;
        for (int j = 0; j < framesPerDirection; ++j)
        {
            // 根据方向偏移量计算帧的坐标
            auto frame = SpriteFrame::createWithTexture(texture, Rect(j * frameWidth, directionOffsets[i] * frameHeight, frameWidth, frameHeight));
            frames.pushBack(frame);
        }

        // 创建动画
        idleAnimations[i] = Animation::createWithSpriteFrames(frames, 0.1f); // 每帧间隔 0.1 秒
        idleAnimations[i]->retain(); // 保留动画，防止被释放
    }
}

// 根据方向选择动画
int MainMap::getDirectionIndex(const cocos2d::Vec2& from, const cocos2d::Vec2& to)
{
    Vec2 direction = to - from;
    float angle = CC_RADIANS_TO_DEGREES(atan2(direction.y, direction.x));

    // 根据角度确定方向
    if (angle >= -22.5f && angle < 22.5f) return 5; // 右
    if (angle >= 22.5f && angle < 67.5f) return 4;  // 右上
    if (angle >= 67.5f && angle < 112.5f) return 3; // 上
    if (angle >= 112.5f && angle < 157.5f) return 2; // 左上
    if (angle >= 157.5f || angle < -157.5f) return 1; // 左
    if (angle >= -157.5f && angle < -112.5f) return 1; // 左下
    if (angle >= -112.5f && angle < -67.5f) return 0; // 下
    if (angle >= -67.5f && angle < -22.5f) return 5; // 右下

    return 5; // 默认右
}

// 键盘按下事件处理
void MainMap::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    CCLOG("Key pressed: %d", keyCode); // 输出按键代码
    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_W:
            isWPressed = true;
            break;
        case EventKeyboard::KeyCode::KEY_A:
            isAPressed = true;
            break;
        case EventKeyboard::KeyCode::KEY_S:
            isSPressed = true;
            break;
        case EventKeyboard::KeyCode::KEY_D:
            isDPressed = true;
            break;
        default:
            break;
    }
}

// 键盘释放事件处理
void MainMap::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    CCLOG("Key released: %d", keyCode); // 输出按键代码
    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_W:
            isWPressed = false;
            break;
        case EventKeyboard::KeyCode::KEY_A:
            isAPressed = false;
            break;
        case EventKeyboard::KeyCode::KEY_S:
            isSPressed = false;
            break;
        case EventKeyboard::KeyCode::KEY_D:
            isDPressed = false;
            break;
        default:
            break;
    }
}

// 更新主角位置
void MainMap::updatePlayerPosition(float dt)
{
    Vec2 direction = Vec2::ZERO;

    if (isWPressed) direction.y += 1; // 上
    if (isAPressed) direction.x -= 1; // 左
    if (isSPressed) direction.y -= 1; // 下
    if (isDPressed) direction.x += 1; // 右

    if (direction != Vec2::ZERO)
    {
        // 计算目标位置
        targetPosition = playerSprite->getPosition() + direction * 100 * dt; // 每秒移动 100 像素

        // 根据方向选择动画
        int directionIndex = getDirectionIndex(playerSprite->getPosition(), targetPosition);

        // 播放跑动动画
        playerSprite->runAction(RepeatForever::create(Animate::create(walkAnimations[directionIndex])));

        // 更新主角位置
        playerSprite->setPosition(targetPosition);

        // 记录最后一次行走的方向索引
        lastDirectionIndex = directionIndex;
    }
    else
    {
        // 停止动画
        playerSprite->stopAllActions();

        // 播放待机动画
        playerSprite->runAction(RepeatForever::create(Animate::create(idleAnimations[lastDirectionIndex])));
    }
}

// 每帧更新
void MainMap::update(float dt)
{
    updatePlayerPosition(dt);
}

// 背包按钮的回调函数
void MainMap::onBackpackButtonClicked(Ref* sender)
{
    // 调用单例管理类显示背包层
    BackpackManager::getInstance()->showBackpack(this);
}