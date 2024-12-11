#include "Player.h"
#include "cocos2d.h"
#include "HelloWorldScene.h"

USING_NS_CC;

// 创建函数
Player* Player::create(const std::string& filename)
{
    Player* sprite = new (std::nothrow) Player();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        sprite->init(); // 调用自定义初始化函数
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

// 初始化函数
bool Player::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    // 初始化属性
    isWPressed = isAPressed = isSPressed = isDPressed = false; // 初始化键盘状态

    // 创建动画
    createWalkAnimations();
    createIdleAnimations();



    // 注册每帧更新
    this->scheduleUpdate();

    return true;
}

// 创建六个方向的行走动画
void Player::createWalkAnimations()
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
void Player::createIdleAnimations()
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
int Player::getDirectionIndex(const cocos2d::Vec2& from, const cocos2d::Vec2& to)
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
void Player::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
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
void Player::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
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
void Player::updatePlayerPosition(float dt)
{
    Vec2 direction = Vec2::ZERO;

    if (isWPressed) direction.y += 1;
    if (isAPressed) direction.x -= 1;
    if (isSPressed) direction.y -= 1;
    if (isDPressed) direction.x += 1;

    if (direction != Vec2::ZERO)
    {
        targetPosition = playerSprite->getPosition() + direction * 100 * dt;

        int directionIndex = getDirectionIndex(playerSprite->getPosition(), targetPosition);

        // 播放跑动动画
        playerSprite->runAction(RepeatForever::create(Animate::create(walkAnimations[directionIndex])));

        playerSprite->setPosition(targetPosition);

        lastDirectionIndex = directionIndex;
    }
    else
    {
        // 停止之前的动画
        playerSprite->stopAllActions();

        // 播放待机动画
        playerSprite->runAction(RepeatForever::create(Animate::create(idleAnimations[lastDirectionIndex])));
    }
}

// 每帧更新
void Player::update(float dt)
{
    updatePlayerPosition(dt);
}