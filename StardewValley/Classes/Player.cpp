#include "Player.h"
#include "cocos2d.h"

USING_NS_CC;


#define Seconds 0.025f // ����ÿ֡���������

// ���캯��
Player::Player() {
    init();
}

// ��ʼ������
bool Player::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    //���������Ϣ
    auto texture = Director::getInstance()->getTextureCache()->addImage("idle.png");
    playerSprite = Sprite::createWithTexture(texture, Rect(0, 0, 72, 96)); // ���������´����ĵ�һ֡

    // ��ʼ������
    isWPressed = isAPressed = isSPressed = isDPressed = false; // ��ʼ������״̬

    // ��ʼ��
    lastDirectionIndex = 0;

    // ��ʼ��Ŀ��λ��
    targetPosition = playerSprite->getPosition();
    isMoving = false;

    // ��������
    createWalkAnimations();
    createIdleAnimations();

    return true;
}

// ����������������߶���
void Player::createWalkAnimations()
{
    // ���� walk.png ͼƬ
    auto texture = Director::getInstance()->getTextureCache()->addImage("walk.png");

    // walk.png ��һ�� 6 �����ͼƬ��ÿ֡�Ŀ��Ϊ 72 ���أ��߶�Ϊ 96 ����
    const int frameWidth = 72;
    const int frameHeight = 96;
    const int framesPerDirection = 8; // ÿ�������� 8 ֡

    // ����ÿ�������֡��Χ
    // ����˳���¡������ϡ��ϡ����ϡ���
    const int directionOffsets[6] = { 0, 1, 2, 3, 4, 5 }; // 6 �������ƫ����

    for (int i = 0; i < 6; ++i)
    {
        Vector<SpriteFrame*> frames;
        for (int j = 0; j < framesPerDirection; ++j)
        {
            // ���ݷ���ƫ��������֡������
            auto frame = SpriteFrame::createWithTexture(texture, Rect(j * frameWidth, directionOffsets[i] * frameHeight, frameWidth, frameHeight));
            frames.pushBack(frame);
        }

        // ��������
        walkAnimations[i] = Animation::createWithSpriteFrames(frames, Seconds); // ÿ֡���������
        walkAnimations[i]->retain(); // ������������ֹ���ͷ�
    }
}

// ������������Ĵ�������
void Player::createIdleAnimations()
{
    // ���� idle.png ͼƬ
    auto texture = Director::getInstance()->getTextureCache()->addImage("idle.png");

    // idle.png ��һ�� 6 �����ͼƬ��ÿ֡�Ŀ��Ϊ 72 ���أ��߶�Ϊ 96 ����
    const int frameWidth = 72;
    const int frameHeight = 96;
    const int framesPerDirection = 8; // ÿ�������� 8 ֡

    // ����ÿ�������֡��Χ
    // ����˳���¡������ϡ��ϡ����ϡ���
    const int directionOffsets[6] = { 0, 1, 2, 3, 4, 5 }; // 6 �������ƫ����

    for (int i = 0; i < 6; ++i)
    {
        Vector<SpriteFrame*> frames;
        for (int j = 0; j < framesPerDirection; ++j)
        {
            // ���ݷ���ƫ��������֡������
            auto frame = SpriteFrame::createWithTexture(texture, Rect(j * frameWidth, directionOffsets[i] * frameHeight, frameWidth, frameHeight));
            frames.pushBack(frame);
        }

        // ��������
        idleAnimations[i] = Animation::createWithSpriteFrames(frames, Seconds); // ÿ֡���������
        idleAnimations[i]->retain(); // ������������ֹ���ͷ�
    }
}

// ���ݷ���ѡ�񶯻�
int Player::getDirectionIndex(const cocos2d::Vec2& from, const cocos2d::Vec2& to)
{
    Vec2 direction = to - from;
    float angle = CC_RADIANS_TO_DEGREES(atan2(direction.y, direction.x));

    // ���ݽǶ�ȷ������
    if (angle >= -22.5f && angle < 22.5f) return 5; // ��
    if (angle >= 22.5f && angle < 67.5f) return 4;  // ����
    if (angle >= 67.5f && angle < 112.5f) return 3; // ��
    if (angle >= 112.5f && angle < 157.5f) return 2; // ����
    if (angle >= 157.5f || angle < -157.5f) return 1; // ��
    if (angle >= -157.5f && angle < -112.5f) return 1; // ����
    if (angle >= -112.5f && angle < -67.5f) return 0; // ��
    if (angle >= -67.5f && angle < -22.5f) return 5; // ����

    return 5; // Ĭ����
}

// ���̰����¼�����
void Player::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    CCLOG("Key pressed: %d", keyCode); // �����������
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

// �����ͷ��¼�����
void Player::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    CCLOG("Key released: %d", keyCode); // �����������
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

// ��������λ��
void Player::updatePlayerPosition(float dt)
{

    Vec2 direction = Vec2::ZERO;

    if (isWPressed) direction.y += 1;
    if (isAPressed) direction.x -= 1;
    if (isSPressed) direction.y -= 1;
    if (isDPressed) direction.x += 1;

    // ͣ��
    playerSprite->stopAllActions();

    if (direction != Vec2::ZERO)
    {
        // �ƶ�����
        Vec2 moveDistance = direction * 120 * dt;
        // �ƶ�
        auto moveAction = MoveBy::create(dt, moveDistance);
        // �жϷ��򶯻�
        int directionIndex = getDirectionIndex(this->getPosition(), this->getPosition() + moveDistance);
        // �������ߵĶ���
        auto animateAction = Animate::create(walkAnimations[directionIndex]);
        // �������߶���
        playerSprite->runAction(RepeatForever::create(animateAction));
        // �����ƶ�
        playerSprite->runAction(moveAction);
        lastDirectionIndex = directionIndex;
    }
    else
    {
        // ���Ŵ�������
        playerSprite->runAction(RepeatForever::create(Animate::create(idleAnimations[lastDirectionIndex])));
    }
}

// ÿ֡����
void Player::update(float dt)
{
    updatePlayerPosition(dt);
}