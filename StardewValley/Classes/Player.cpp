#include "Player.h"
#include "cocos2d.h"

USING_NS_CC;


#define Seconds 0.025f // 动作每帧间隔多少秒

// 构造函数
Player::Player() {
    init();
}

// 初始化函数
bool Player::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    //添加主角信息
    auto texture = Director::getInstance()->getTextureCache()->addImage("idle.png");
    playerSprite = Sprite::createWithTexture(texture, Rect(0, 0, 72, 96)); // 待机是向下待机的第一帧

    // 初始化属性
    isWPressed = isAPressed = isSPressed = isDPressed = false; // 初始化键盘状态

    // 初始化
    lastDirectionIndex = 0;

    // 初始化目标位置
    targetPosition = playerSprite->getPosition();
    isMoving = false;

    // 创建动画
    createWalkAnimations();
    createIdleAnimations();

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
        walkAnimations[i] = Animation::createWithSpriteFrames(frames, Seconds); // 每帧间隔多少秒
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
        idleAnimations[i] = Animation::createWithSpriteFrames(frames, Seconds); // 每帧间隔多少秒
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

    // 停下
    playerSprite->stopAllActions();

    if (direction != Vec2::ZERO)
    {
        // 移动方向
        Vec2 moveDistance = direction * 120 * dt;
        // 移动
        auto moveAction = MoveBy::create(dt, moveDistance);
        // 判断方向动画
        int directionIndex = getDirectionIndex(this->getPosition(), this->getPosition() + moveDistance);
        // 创建行走的动作
        auto animateAction = Animate::create(walkAnimations[directionIndex]);
        // 播放行走动画
        playerSprite->runAction(RepeatForever::create(animateAction));
        // 播放移动
        playerSprite->runAction(moveAction);
        lastDirectionIndex = directionIndex;
    }
    else
    {
        // 播放待机动画
        playerSprite->runAction(RepeatForever::create(Animate::create(idleAnimations[lastDirectionIndex])));
    }
}

// 每帧更新
void Player::update(float dt)
{
    updatePlayerPosition(dt);
}